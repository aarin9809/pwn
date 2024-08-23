#include <stdio.h>

int main() {
	int arr[10];

	printf("IN Bound: \n");
	printf("arr: %p\n", arr);
	printf("arr[0]: %p\n\n", &arr[0]);


	printf("Out Bound: \n");
	printf("arr[-1]: %p\n", arr[-1]);
	printf("arr[100]: %p\n\n", &arr[100]);

	return 0;
}
