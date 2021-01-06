#include <stdio.h>

float averageCalculator(float a1, float a2, float a3) {
    float avg;
    avg = (a1+a2+a3)/3;
    return avg;
}

float piSeries(int n) {
    float piValue= 0;
    float sign;
    float div = 4;
    for (int j = 1; j<n+1; j++) {
        if (j%2==0){
            sign = -1;
        }
        else {
            sign = 1;
        }
        piValue = piValue + ((sign)*(div/((2*j)-1)));
    }
    return piValue;
}

int perfectSquare(int sq) {
    int square,root;
    for (int i = 2; i <= sq/2; i++ ) {
        square = i*i;
        if (square == sq) {
            root = i;
            break;
        }
        else {
            root = -1;
        }
    }
    return root ;
}
int main() {
    int programCode,sq,n;
    float a1,a2,a3;
    printf("Welcome to muy calculator!\nInput 1 for a 3 number average calculator\n"
           "Input 2 for an approximation of PI to the nth degree\n"
           "Input 3 for an integer perfect square calculator\n"
           "Input 0 to exit the program the program.\n");
    scanf("%d",&programCode);
    while (programCode!= 0) {
        switch (programCode) {
            case 1:
                printf("Enter three numbers:\n");
                scanf("%f %f %f", &a1, &a2, &a3);
                printf("The average of %.3f %.3f %.3f to three decimal places is:\n %.3f ", a1, a2, a3,
                       averageCalculator(a1, a2, a3));
                break;
            case 2:
                printf("Enter the degree of the Gregory-Leibniz series you desire:\n");
                scanf("%d",&n);
                printf("The value of pi evaluated to the %dth degree is:\n%.8f",n,piSeries(n));
                break;
            case 3:
                printf("Input a positive integer:\n");
                scanf("%d",&sq);
                if (perfectSquare(sq) == -1) {
                    printf("The square root of %d is not an integer",sq);
                }
                else {
                    printf("The square root of %d is:\n"
                           "%d",sq, perfectSquare(sq));
                }
                break;
            default:
                printf("Your input is invalid, input again:\n");
                scanf("%d", &programCode);

        }
        printf("\nIf you wish to continue, input 1 for a 3 number average calculator\n"
               "input 2 for an approximation of PI to the nth degree\n"
               "input 3 for an integer perfect square calculator.\n"
               "If you wish to exit input 0\n");
        scanf("%d", &programCode);
    }
    if (programCode == 0) {
        printf("Thank you for using my calculator!");
    }
    return 0;
}