#include <stdio.h>
#include <string.h>

int main(void) {
	char origin[] = "BlockDMask";
	char dest1[20];
	char dest2[10];
	char dest3[] = "strcpy_ex";

	//case1 : 빈 배열에 전체를 복사할 때
	strcpy(dest1, origin);

	//case2 : 빈 배열에 전체를 복사할 때
	//strcpy(dest2, origin);
	
	//strcpy(dest2, origin);
	
	
	//case3 : 꽉 차있는 배열에 전체를 복사할때
	strcpy(dest3, origin);

	printf("case1 : %s\n", dest1);
	//printf("case2 : %s\n, dest2);
	
	printf("case3 : %s\n", dest3);
	
	return 0;
}
