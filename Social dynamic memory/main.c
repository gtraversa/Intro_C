#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct user {                                         // Declare my struct globally with the contained information
    char name[40];
    char surname[40];
    int userNumber;
    int userID;
    int numberOfFriends;
    int friends [50];                                 //Create an array of integers which will contain the user numbers of the friends
    struct user *next;                                // Create a pointer stored in the struck which will point to the next element in the list
};

typedef struct user *node;                            //Define node as pointer of data type struct user

node head = NULL;                                     //Declare the head of the list as a global variable
                                                      //The head will start by being null before being populated
node createNode() {
    node temp;                                       // declare a node
    temp = (node)malloc(sizeof(struct user));        // allocate memory using malloc()
    temp->next = NULL;                               // make next point to NULL
    return temp;                                     //return the new node
}

int my_strcmp(char a[], char b[]) {                   //The inputs to this function are two strings
    int check = 1;
    int lengthA = 0;
    int lengthB = 0;
    for (int i=0; a[i]!='\0'; i++) {                //This for loops finds the length of string a
        lengthA++;
    }

    for (int i=0; b[i]!='\0'; i++) {                //This for loops finds the length of string b
        lengthB++;
    }

    if (lengthA!=lengthB) {                         //If the strings are not the same length then the function returns 0
        check = 0;
        return check;
    }
    else  {
        for (int i = 0; i < lengthA; i++) {         //If they are the same length a for loop checks each element and compares them
            if (a[i]!=b[i]) {
                check = 0;                          //If it finds a different character the function outputs 0 else the strings are equal
                break;
            }
        }
    }
    return check;
}

node addUser(node head, int userCounter){
    node temp,ptr,ptr1;                               //Declare the nodes I will be using in this function
    char init1;
    char init2;
    int initNumber1,initNumber2,i,l;                  // declare two nodes temp and p
    int flag = 0;                                     //Flag will be used to signal invalid inputs with different codes
    temp = createNode();                              //createNode will return a new node with next pointing to NULL.
    printf("Enter user name: ");                      //Prompt the user for the name and surname of the new user
    scanf("%s", temp->name);
    printf("Enter user surname: ");
    scanf("%s", temp->surname);
    init1 = toupper(temp->name[0]);                   //toupper() used  to keep ASCII range constant
    initNumber1 = (int)init1;                         //Find the ASCII value of the initial of the name inputted
    temp->userNumber = userCounter + 1;               //This will vary depending on the order of the users
    temp->userID = userCounter + 1;                   //This will be permanent for each user and will not change when a user is remived
    temp->numberOfFriends = 0;
    if(head == NULL){
        head = temp;                                  //when linked list is empty
    }
    else{
        ptr  = head;                                  //assign head to ptr to begin from the start of the list
        i = 0;
        while(ptr != NULL){                           // Condition to traverse the list
            init2 = toupper(ptr->name[0]);
            initNumber2 = (int)init2;                 //Find the ASCII value of the initial of each user traversed in the lits
            if (initNumber2 > initNumber1) {          //Condition meaning the current user being added should be inserted just before the one being checked
                                                      //(ASCII increases in alphabetical order)
              flag = 2;
              ptr1 = ptr;                             //Storing the pointer pointing to the desired user
              if (i ==  0) {                          //This is the case where the user being added comes before the first user in the current database
                temp->next = head;                    // Setting the "next" pointer fot the new user
                head = temp;
                temp->userNumber = 1;                 //Updating user number and changing the head of the list
              }
              else {
                ptr = head;                           //Reset pointer to head to traverse the list
                while ( ptr->next != ptr1) {          //Traversing the list until we reach the user before the user we want to insert
                  ptr = ptr->next;
                }
                ptr->next = temp;                     //List insertion of the new user
                temp->next = ptr1;                    //Pointing the new user to the one we had stored before
                temp->userNumber = i+1;               //Find the new user's user number
              }
              ptr = ptr1;
              while (ptr != NULL) {                   //Traverse the list and update all the user numbers to reflect the new user inserted
                ptr->userNumber += 1;
                ptr = ptr->next;
              }
              break;
            }
            i++;
            ptr = ptr->next;                          //Traverse the list until ptr is the last node.The last node always points to NULL.
        }
        if (flag == 0) {                              //Condition indicating the new user is to be inserted last alphabetically
          ptr = head;
          while (ptr->next != NULL) {                 //Traverse the list until ptr is equal to the last user pointer
            ptr = ptr->next;
          }
          ptr->next = temp;                           //Point the last user to the new user
          temp->next = NULL;                          //Next user pointer set to NULL as it is at the end of the list
        }
    }
    return head;                                      //Update head for new user
}

node removeUser(node head) {
    node ptr,temp;                                    //Declare the nodes I will be using in this function
    char delUser[20];
    int delUserNumber, comp,flag,delUserID;           //Flag will be used to signal invalid inputs with different codes
    ptr = head;                                       //Point to head
    printf("Which user would you remove? Input the user name.\n");
    while (ptr != NULL) {                             //Traverse and print all user numbers associated with the names
        printf("User %d name: %s %s\n", ptr->userNumber, ptr->name, ptr->surname);
        printf("\n");
        ptr = ptr->next;
    }
    scanf("%s", delUser);                              //Save the user name to be removed
    ptr = head;
    while (ptr != NULL) {
      comp = my_strcmp(delUser,ptr->name);
      if (comp == 1) {                                 //Traverse list and compoare each name with the desired username to be removed
        delUserNumber = ptr->userNumber;               //Save all the ID information of the user to be removed
        delUserID = ptr->userID;
        temp = ptr->next;
        break;
      }
      ptr = ptr->next;
    }
    ptr = head;
    if (delUserNumber == 1) {                           //Condition where the first user in alphabetical order is to be removed
      flag = 2;
      head = ptr->next;
      free(ptr);                                        //Free the allocated space
      ptr = head;
      while (ptr != NULL) {
        ptr->userNumber -=1;
        ptr = ptr->next;
      }
      ptr = head;
      return head;                                       //Return the new head
    }
    while (ptr != NULL && flag != 2) {
      if (ptr->userNumber == delUserNumber - 1) {
        ptr->next = temp;                                //Store the pointer which will be used to reconnect the list later
      }
      else if (ptr->userNumber == delUserNumber) {
        free(ptr);                                       //Free the memory associated with the user to be removed
      }
      else if (ptr->userNumber > delUserNumber) {
        ptr->userNumber -=1;                             //Update all the next user numbers
      }
      ptr = ptr->next;
    }
    ptr = head;
    while (ptr != NULL) {
      for(int i = 0; i<ptr->numberOfFriends; i++) {
        if (ptr->friends[i] == delUserID) {              //Update all the friend numbers of people who were friends with the deleted user
          ptr->numberOfFriends -= 1;
        }
      }
      ptr = ptr->next;
    }
    return head;
}

void userReport(node head) {
    node ptr,temp;                                    //Declare the head of the list as a global variable
    ptr = head;
    while(ptr != NULL){                               //Traversa the list and print each user's information
        printf("\n");
        printf("User %d\n", ptr->userNumber);
        printf("UserID: %d\n", ptr->userID);
        printf("Name: %s %s\n",ptr->name, ptr->surname);
        printf("Number of friends: %d\n",ptr->numberOfFriends);
        printf("Friends with:\n");
        for (int j=0; j<=ptr->numberOfFriends;j++) {
            temp = head;
            while (temp != NULL) {                     //This nested loop finds all of the friends' user numbers and uses that to index the names
              if (ptr->friends[j] == temp->userID) {   //Correlates user ID's with user names and prints them
                printf("%s %s \n",temp->name,temp->surname);
              }
              temp = temp->next;
            }
        }
        printf("\n");
        ptr = ptr->next;
    }
}

void indivUserReport(node head) {
    node ptr,temp;                                     //Declare the head of the list as a global variable
    int comp,flag;                                     //Flag will be used to signal invalid inputs with different codes
    char user [20];
    printf("Enter the name of the user for which you would like to see a report for: \n");
    scanf("%s", user);                                 //Prompts user for desired user to be reported on and stores the name
    ptr = head;
    while(ptr != NULL) {
        comp = my_strcmp(user, ptr->name);             //Finds userID corresponding to user name
        if (comp == 1) {                               //Exactly like full user report but without traversing all the list
          flag = 2;
          printf("\n");
          printf("User %d\n", ptr->userNumber);
          printf("UserID: %d\n", ptr->userID);
          printf("Name: %s %s\n",ptr->name, ptr->surname);
          printf("Number of friends: %d\n",ptr->numberOfFriends);
          printf("Friends with:\n");
          for (int j=0; j<=ptr->numberOfFriends;j++) {
              temp = head;
              while (temp != NULL) {
                if (ptr->friends[j] == temp->userID) {
                  printf("%s %s \n",temp->name,temp->surname);
                }
                temp = temp->next;
              }
          }
        }
        ptr = ptr->next;
    }
    if (flag != 2) {
      printf("The user does not exist. \n");
    }
}

void addFriend(node head) {                           //The input to this function is the total number of users
    node ptr;
    ptr = head;
    char friendName1[20],friendName2[20];
    int friendNumber1 = -15;
    int friendNumber2 = -1;
    int search = 0;
    int flag = 0;                                     //Flag will be used to signal invalid inputs with different codes
    printf("Which users would you like to be friends? Input the two user names.\n");
    while (ptr != NULL) {                             //This loop prints out all the users and their correlated user number
        printf("UserID %d name: %s %s\n", ptr->userID, ptr->name, ptr->surname);
        printf("\n");
        ptr = ptr->next;
    }
    ptr = head;                                        //The pointer is reset to the beginning of the list so the next loops can cycle through all the list
    scanf("%s %s", friendName1, friendName2);          //We scan for the two user names that will be related
    while (ptr != NULL) {                              //These next two loops use my own string compare function to find the user number matching the inputted names
        search = my_strcmp(friendName1, ptr->name);
        if (search == 1) {
            friendNumber1 = ptr->userID;               //If the strings are equal the user number is stored and used to add the friendship in the next part
        }
        ptr = ptr->next;
    }
    ptr = head;
    search = 0;
    while (ptr != NULL) {
        search = my_strcmp(friendName2,ptr->name);
        if (search == 1) {
            friendNumber2 = ptr->userID;
        }
        ptr = ptr->next;
    }

    ptr = head;
    while (ptr->next != NULL) {                         //The pointer is set to point at the desired element in the array
      if (ptr->userID == friendNumber1 ) {
        break;
      }
      ptr = ptr->next;
    }
    for (int i=0; i<ptr->numberOfFriends;i++) {         //This loop searches through one of the users' friends to check if the inputted users are already friends
        if(ptr->friends[i] == friendNumber2) {
            flag = 1;                                   //Flag == 1 indicates the users are already friends
        }
    }
    if (friendNumber1 == -1 || friendNumber2 == -1) {   //This loop checks whether the two inputs are valid users
        flag = 2;                                       //Flag == 2 indicates one of the inputs are not valid users
    }
    ptr = head;
    while (ptr != NULL) {                               //The pointer is set to point at the desired element in the array
      if (ptr->userID == friendNumber1) {
        break;
      }
      ptr = ptr->next;
    }
    if (friendNumber1!=friendNumber2 && flag == 0) {    //If the two inputs are valid this statement runs
        ptr->friends[ptr->numberOfFriends] = friendNumber2;
        ptr->numberOfFriends++;
        ptr = head;
        while (ptr != NULL) {
          if (ptr->userID == friendNumber2) {
            break;
          }
          ptr = ptr->next;
        }
                                                                      //Each of the friend counters are increased by one as a new friendship is created
        ptr->friends[ptr->numberOfFriends] = friendNumber1;           //By using the friend number as an index the userID of the new
        ptr->numberOfFriends++;                                       //friend is added to the next available position in the friends array
    }
    else if (flag==2) {
        printf("One of the inputted users does not exist \n");
    }
    else if (friendNumber1==friendNumber2) {
        printf("You can't be your own friend \n");
    }
    else if (flag == 1) {
        printf("These users are already friends \n");
    }
}

void save(node head) {
  node ptr,temp;                                      //Declare the nodes I will be using in this function
  FILE * fptr;                                        //Create a file pointer
  char fileName[50];
  printf("Input file name with no spaces and .txt: \n");
  scanf("%s", fileName);                              //Prompt for the file name
  fptr = fopen(fileName,"w");                         //Create the .txt file
  ptr = head;
  while(ptr != NULL) {                                //Essentially the same as user report but using fprintf(fptr) to write to the new file
      fprintf(fptr, "User %d\n", ptr->userNumber);
      fprintf(fptr, "UserID: %d\n", ptr->userID);
      fprintf(fptr, "Name: %s %s\n",ptr->name, ptr->surname);
      fprintf(fptr, "Number of friends: %d\n",ptr->numberOfFriends);
      fprintf(fptr, "Friends with:\n");
      for (int j=0; j<=ptr->numberOfFriends;j++) {     //This nested loop finds all of the friends' user numbers and uses that to index the names
          temp = head;
          while (temp != NULL) {
            if (ptr->friends[j] == temp->userID) {
              fprintf(fptr, "%s %s \n",temp->name,temp->surname);
            }
            temp = temp->next;
          }
      }
      fprintf(fptr, "\n \n");                          //Spacing
      ptr = ptr->next;
  }
  fprintf(fptr,"Data for loading \n\n\n\n\n");         //This large space will indicate to my reading program where to start reading from
  ptr = head;
  while(ptr != NULL) {                                 //Next I print the same information but without the wording so when I read the file the value  I'm interested will occupy 1 line
      fprintf(fptr, "%d\n", ptr->userNumber);
      fprintf(fptr, "%d\n", ptr->userID);
      fprintf(fptr, "%s\n%s\n",ptr->name, ptr->surname);
      fprintf(fptr, "%d\n",ptr->numberOfFriends);
      fprintf(fptr, "FI\n");
      for (int i = 0; i < ptr->numberOfFriends; i++) {
        fprintf(fptr, "%d\n", ptr->friends[i]);
      }
      fprintf(fptr,"end\n");
      ptr = ptr->next;
  }
  fclose(fptr);                                         //Close the file
}
/*
int open(int userCounter) {                                            //Not currently working (was not aware of fscanf())
  node temp,ptr,temp1;
  char init1;
  char init2;
  int initNumber1,initNumber2,i,l;
  int flag = 0;
  int k = 0;
  FILE * fptr;
  char singleLine[200];
  char nLine[] = "\n";
  char compar[] = "end\n";
  int space,lineComp,userCounter, userID, numberOfFriends,comp;
  int lineCount = 0;
  char fileName[50];
  printf("Input file name with no spaces and .txt: \n");
  scanf("%s", fileName);                                //Prompt for the file to be loaded
  fptr = fopen(fileName,"r");
  while (!feof(fptr)) {                                 //Traverse the file line per  line
    fgets(singleLine, 150, fptr);
    lineComp = my_strcmp(singleLine ,nLine);
    while (1) {
      userCounter++;
      if (space == 4 && lineCount == 0) {               //When the 4 spaces are found we begin the reading area of the file
        lineCount = 1;
      }
      else if (space != 4){
        break;
      }
      if (lineCount == 1) {
        temp = createNode();                            //Create a new user and set the user number
        temp->userNumber = (int)singleLine[0];
        lineCount++;                                    //Always increase linecount
        break;
      }
      else if (lineCount == 2) {                        //Order of information is known so the content from each line is loaded into the new user
        temp->userID = (int)singleLine[0];
        lineCount++;
        break;
      }
      else if (lineCount == 3) {
        strcpy(temp->name,singleLine);
        lineCount++;
        break;
      }
      else if (lineCount == 4) {
        strcpy(temp->surname,singleLine);
        lineCount++;
        break;
      }
      else if (lineCount == 5) {
        temp->numberOfFriends = (int)singleLine[0];
        lineCount++;
        break;
      }
      else if(lineCount == 6) {                         //Line containing no information just "FI" whuch stands for friend ID
        lineCount++;
        break;
      }
      else if(lineCount > 6) {                          //Friom this point on the numbers read are the friends' ID numebrs
        comp = my_strcmp(compar,singleLine);            //This is because at the end of the friend ID's (of unknown length) i placed a marker "end\n"
        while (comp != 1) {
          temp->friends[k] = (int)singleLine;           //Store all of the friend ID's in the new user's friends array
          k++;
          break;
        }
        if (comp == 1) {                                //Once the end of the friends has been reached space and line are reset
          space = 4;
          lineCount = 1;
          if (userCounter == 1) {                    //This is the part which I'm unsure about, ideally if userCounter is 1 then head is set
            temp = head;                             //And the next pointer will point to the next user added but not really sure how to do this :/
            head->next = temp;
          }
          else {

          }
        }
        break;
      }
    }
    if (lineComp == 1) {                                //Used to find the quadruple empty line indicating the start of the reading section of the file
      space++;
    }
  }
  fclose(fptr);                                         //Close the file
  return userCounter;                                   //Return the upfdated user counter
}
*/
int main() {
  int userCounter=0;
  int menuNumber,confirm;
  printf("Welcome to UCLoners, my brand new social media!\n"
         "-----------------------------------------------\n"
         "To add a new user, press 1.\n"
         "To load an old user file, press 7 (not currently working).\n"
         "To exit the social, press 0.\n");
  scanf("%d",&menuNumber);                                           //Get menu option
  while (menuNumber != 0) {                                          //Condition to exit the program
      switch(menuNumber) {                                           //Switch statement to chose the action
          case 1 :
              printf("To cancel enter 0 else enter 1.\n");
              scanf("%d",&confirm);
              if (confirm == 0) {
                break;
              }
              else if (confirm !=1) {
                printf("Input invalid\n");
                break;
              }
              head = addUser(head, userCounter);
              userCounter++;
              break;
          case 2:
              printf("To cancel enter 0 else enter 1.\n");
              scanf("%d",&confirm);
              if (confirm == 0) {
                  break;
              }
              else if (confirm !=1) {
                printf("Input invalid\n");
                break;
              }
              addFriend(head);
              break;
          case 3:
              userReport(head);
              break;
          case 4:
              printf("To cancel enter 0 else enter 1.\n");
              scanf("%d",&confirm);
              if (confirm == 0) {
                break;
              }
              else if (confirm !=1) {
                printf("Input invalid\n");
                break;
              }
              head = removeUser(head);
              userCounter--;
              break;
          case 5:
              indivUserReport(head);
              break;
          case 6:
              save(head);
              break;
          case 7:
              //userCounter = open(userCounter);
              break;
          default:
              printf("Your input is invalid, input again:\n");
              scanf("%d", &menuNumber);
              break;
      }
      printf("-----------------------------------------------\n"
             "To add a new user, press 1.\n"
             "To add a friendship, press 2.\n"
             "To see a user report, press 3.\n"
             "To remove a user, press 4.\n"
             "To see an individual user report, press 5. \n"\
             "To save the current user info to a file, press 6. \n"
             "To exit the social, press 0.\n");
      scanf("%d",&menuNumber);                                         //Ask for menu option again
  }
  if (menuNumber == 0) {                                               //Quitting the program
      printf("-----------------------------------------------\n"
             "Thank you for using UCLoners!\n");
  }
  return 0;
}
