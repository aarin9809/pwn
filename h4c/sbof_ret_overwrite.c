//Name : sbof_ret_overwrite.c
// Compile: gcc -o sbof_ret_overwrite sbof_ret_overwrite.c -fno-stack-protector
// 스택 버퍼 오버플로우를 통한 반환 주소 덮어쓰기

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char buf[8];

	printf("Overwrite return address with 0x4141414141414141: ");

	gets(buf);

	return 0;
}

