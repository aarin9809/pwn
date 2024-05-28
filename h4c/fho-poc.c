#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *buf = "/bin/sh";

int main() {
	printf("\"__free_hook\" now points at \"system\"\n");
	__free_hook = (void *)system;
	
	printf("call free(\"/bin/sh\")\n");
	free(buf);
	}
