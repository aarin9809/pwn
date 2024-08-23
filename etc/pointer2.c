#include <stdio.h>

int main() {
    int i = 10;
    int *p;
    p = &i;
    printf("i = %d", i);
    *p = 20;
    printf("i = %d", i);

    return 0;
}