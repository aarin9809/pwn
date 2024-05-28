#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}


int main() {
    int c = sum(1, 2);
    printf("%d\n", c);
    return 0;
}