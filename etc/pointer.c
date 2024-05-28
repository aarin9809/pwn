#include <stdio.h>

int main() {
	int a[5] = {1,2,3,4,5};	// 배열 a 선언 및 초기화
	int *b = a;			// pointer b가 배열 a를 가리킴(배열 a의 주소값을 가리키기 때문에 같은 값을 가짐. 카피닌자?)
	printf("%d\n", b[2]);	//카카시 사륜안 해버렸으므로 b도 이제 배열 a와 같은 존재가 되어버렸음 3 리턴.
	return 0;
}