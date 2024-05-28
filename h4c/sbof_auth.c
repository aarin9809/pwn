#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_auth(char *password) {
	int auth = 0;
	char temp[16];

	strncpy(temp, password, strlen(password));

	if(!strcmp(temp, "secret_password"))
		auth = 1;

	return auth;
}
int main(int argc, char *argv[1]) {
	if(argc !=2) {
		printf("usage: ./sbof_auth admin_password\n");
		exit(-1);
	}

	if (check_auth(argv[1]))
		printf("hello admin!\n");
	else
		printf("access denied!\n");
}

