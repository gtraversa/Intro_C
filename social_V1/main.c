#include <stdio.h>


struct user {                                      // Declare my struct globally with the contained information
    char name[40];
    char surname[40];
    int userNumber;
    int numberOfFriends;
    int friends[19];                               //Create an array of integers which will contain the user numbers of the friends
                                                    // The max number of friends is one less than the number of users as you cant be friends with yourself
};
struct user database[20];                         //Create an array of 20 structs ie. 20 users

int my_strcmp(char a[], char b[]) {        //The inputs to this function are two strings
    int check = 1;
    int lengthA = 0;
    int lengthB = 0;
    for (int i=0; a[i]!='\0'; i++) {       //This for loops finds the length of string a
        lengthA++;
    }

    for (int i=0; b[i]!='\0'; i++) {       //This for loops finds the length of string b
        lengthB++;
    }

    if (lengthA!=lengthB) {                //If the strings are not the same length then the function returns 0
        check = 0;
    }
    else  {
        for (int i = 0; i < lengthA; i++) {//If they are the same length a for loop checks each element and compares them
            if (a[i]!=b[i]) {
                check = 0;                 //If it finds a different character the function outputs 0 else the strings are equal
                break;
            }
        }
    }
    return check;
}

void addUser(int userCounter) {                   //The input to this function is the total number of users
    printf("Input user name: ");
    scanf("%s", database[userCounter-1].name);
    printf("Input user surname: ");
    scanf("%s", database[userCounter-1].surname); //The name and surname are stored in the userCounter-1 location in the array of structs because arrays start at 0
    database[userCounter-1].userNumber = userCounter; //By the same reasoning the user number of user in location n-1 is n
}

void userReport(int userCounter) {       //The input to this function is the total number of users
    for (int i = 0; i<userCounter;i++) { //This loop will loop through all of the existing users and print all of the information contained in their struct
        printf("\n");
        printf("User %d\n", database[i].userNumber);
        printf("Name: %s %s\n",database[i].name, database[i].surname);
        printf("Number of friends: %d\n",database[i].numberOfFriends);
        printf("Friends with:\n");
        for (int j=0; j<database[i].numberOfFriends;j++) { //This nested loop finds all of the friends' user numbers and uses that to index the names
            printf("%s %s \n",database[database[i].friends[j]-1].name,database[database[i].friends[j]-1].surname);
        }
        printf("\n");
    }
}

void addFriend(int userCounter) {                       //The input to this function is the total number of users
    char friendName1[20],friendName2[20];
    int friendNumber1,friendNumber2,search;
    int flag = 0;                                       //Flag will be used to signal invalid inputs with different codes
    printf("Which users would you like to be friends? Input the two user names.\n");
    for (int i = 0; i<userCounter;i++) {                //This loop prints out all the users and their correlated user number
        printf("User %d name: %s %s\n",database[i].userNumber,database[i].name, database[i].surname);
        printf("\n");
    }
    scanf("%s %s", friendName1, friendName2);            //We scan for the two user names that will be related
    for (int i=0; i<userCounter;i++) {                   //These next two loops use my own string compare function to find the user number matching the inputted names
        search = my_strcmp(friendName1,database[i].name);
        if (search == 1) {
            friendNumber1 = i + 1;                       //If the strings are equal the user number is stored and used to add the friendship in the next part
        }
    }
    search = 0;
    for (int i=0; i<userCounter;i++) {
        search = my_strcmp(friendName2,database[i].name);
        if (search == 1) {
            friendNumber2 = i+1;
        }
    }
    for (int i=0; i<database[friendNumber1-1].numberOfFriends;i++) { //This loop searches through one of the users' friends to check if the inputted users are already friends
        if(database[friendNumber1-1].friends[i] == friendNumber2) {
            flag = 1;                                                //Flag == 1 indicates the users are already friends
        }
    }
    if (friendNumber1>userCounter || friendNumber2>userCounter) {     //This loop checks whether the two inputs are valid users
        flag = 2;                                                     //Flag == 2 indicates one of the inputs are not valid users
    }
    if (friendNumber1!=friendNumber2 && flag == 0) {                  //If the two inputs are valid this statement runs
        database[friendNumber1-1].numberOfFriends++;
        database[friendNumber2-1].numberOfFriends++;                  //Each of the friend counters are increased by one as a new friendship is created
        database[friendNumber1-1].friends[database[friendNumber1-1].numberOfFriends-1] = friendNumber2;//By using the friend number as an index the user number of the new
        database[friendNumber2-1].friends[database[friendNumber2-1].numberOfFriends-1] = friendNumber1;//friend is added to the next available position in the friends array
    }
    else if (flag==2) {
        printf("One of the inputted users does not exist \n");
    }
    else if (friendNumber1==friendNumber2) {
        printf("You can't be your own friend\n");
    }
    else if (flag == 1) {
        printf("These users are already friends\n");
    }
}
int main() {
    int userCounter=0;
    int menuNumber;
    printf("Welcome to UCLoners, my brand new social media!\n"
           "To add a new user, press 1.\n"
           "To add a friendship, press 2.\n"
           "To see a user report, press 3.\n"
           "To exit the social, press 0.\n");
    scanf("%d",&menuNumber);                                           //Get menu option
    while (menuNumber != 0) {                                          //Condition to exit the program
        switch(menuNumber) {                                           //Switch statement to chose the action
            case 1 :
                userCounter++;
                addUser(userCounter);
                break;
            case 2:
                addFriend(userCounter);
                break;
            case 3:
                userReport(userCounter);
                break;
            default:
                printf("Your input is invalid, input again:\n");
                scanf("%d", &menuNumber);
                break;
        }
        printf("\n"
               "To add a new user, press 1.\n"
               "To add a friendship, press 2.\n"
               "To see a user report, press 3.\n"
               "To exit the social, press 0.\n");
        scanf("%d",&menuNumber);                                         //Ask for menu option again
    }
    if (menuNumber == 0) {                                               //Quitting the program
        printf("Thank you for using UCLoners!");
    }
    return 0;
}
