// Name: rao_patched.c
// Compile: gcc -o rao_patched rao_patched.c -fno-stack-protector -no-pie

#include <stdio.h>
#include <unistd.h>

void get_shell() {
	char *cmd;
	char *args[] = {cmd, NULL};

	execve(cmd, args, NULL);
}

int main() {
	char buf[0x28];

	printf("Input: ");

	scanf("%39s", buf);

	return 0;
}
