#include <stdio.h>

int daysCalculator(int mm, int yyyy) {
    int numberOfDays = 0;
    if (yyyy % 4 == 0 && mm == 2) {
        numberOfDays = 29;
    }
    else if(0 <= yyyy && 1 <= mm && mm <= 12 && yyyy%1 == 0 && mm%1 == 0) {
        switch (mm) {
            case 4:
                numberOfDays = 30;
            case 6:
                numberOfDays = 30;
            case 9:
                numberOfDays = 30;
            case 11:
                numberOfDays = 30;
                break;
            case 2:
                numberOfDays = 28;
                break;
            default:
                numberOfDays = 31;
        }
    }
    else {
        printf("The input is invalid \n");
    }
    return numberOfDays;
}

int main () {
    printf("Hellow");
    int mm, yyyy;
    printf ("Enter a month in the form mm:\n");
    scanf ("%d", &mm);
    printf ("Enter a year in the form yyyy:\n");
    scanf ("%d", &yyyy);
    printf ("You entered: %d",mm);
    printf("/%d\n",yyyy);
    int numberOfDays = daysCalculator(mm, yyyy);
    printf("The month has %d days.", numberOfDays);
    return 0;
}
