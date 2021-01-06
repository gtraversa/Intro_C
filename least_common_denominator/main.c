#include <stdio.h>

int main() {
    int n1, n2,i,lcd;
    printf("Please input two positive integers:\n");
    scanf("%d %d",&n1, &n2);
    for (i=2; i<n1*n2; i++) {
        if (n1%i == 0 && n2%i == 0) {
            lcd = i;
            break;
        }
        else {
            lcd = n1*n2;
        }
    }
    printf("The least common denominator of %d and %d is : %d",n1,n2,lcd);
    return 0;
}