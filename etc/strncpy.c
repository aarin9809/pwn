#include <stdio.h>
#include <string.h>

int main(void) {

	char origin[] = "BlockDMask";
	char dest1[20];
	char dest2[] = "abcdefghijklmnop";
	char dest3[] = "strncpy_ex";
	char dest4[10];


	//case1 : 빈 배열에 전체를 복사할 때
	strncpy(dest1, origin, sizeof(origin));
	
	//case2 : 꽉 차있는 배열에 전체를 복사할 때
	strncpy(dest2, origin, sizeof(origin));

	//case3 : 꽉 차잇는 배열에 일부만 복사할 때
	strncpy(dest3, origin, 4);

	//case4 : 빈 배열에 일부만 복사할 때
	strncpy(dest4, origin, 4);


	printf("case1 : %s\n", dest1);
	printf("case2 : %s\n", dest2);
	printf("case3 : %s\n", dest3);
	printf("case4 : %s\n", dest4);

	return 0;
}
