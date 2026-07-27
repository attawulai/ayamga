#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void login(FILE* file);
void r_file(char* stored_password,char* stored_username);
void blackJack(void);

int main()
{
    int chances = 3;
    char password[10]={0};
    char stored_password[10]={0};
    char stored_username[10];

    FILE* file = fopen("encryption.txt","w");
    if( file == NULL)
    {
        printf("ERRO opening file\n");
        return 1;
    }
    login(file);
    fclose(file);

    r_file(stored_password, stored_username);


    while(chances > 0)
    {
        printf("\nEnter password to start:\n");
     scanf("%s", password);

     printf("Debug: Stored password = %s entered password = %s",stored_password, password);

     if(strcmp(stored_password,password)==0)
     {
        printf("Access Granted!");

        int choice=0;
        printf("____Welcome,%s___\n",stored_username);
        printf("1. play Black jack\n");
        printf("2. view transaction History\n");
        printf("3. quit\n");
        printf("enter a choice: ");
        scanf("%i",&choice);
        if(choice < 1 || choice > 3)
        {
            printf("INVAILD INPUT!,try again\n");

        }

         switch(choice)
         {
            case 1:blackJack();
            break;
            case 2:
            break;
            case 3:
            break;
            default:
            printf("Invaild input!");
            break;

         }
        return 0;
     }
     else
     {
        chances--;
        if (chances > 0)
        {
            printf("Incorect password, try again you have %i chances left",chances);
        }
        else
        {
            printf("Access denied, No atempts left");
            return 1;
         }
     }

    }





}
void login(FILE* file)
{

    char username[10];
    char password[10];

    while (1)
  {

        printf("enter a username: \n");
        scanf("%s", username);

        printf("enter a 5 letter password: ");
        scanf("%s", password);
        if (strlen(password) != 5)
        {
            printf("letter is greater that 5 try again");
            continue;
        }

            fprintf(file, "username:%s\n", username);
            fprintf(file, "password:%s\n", password);

            printf("Succefully saved!\n");
            break;

    }
}
void r_file(char* stored_password,char* stored_username)
{
    FILE* file = fopen("encryption.txt","r");

    if(file != NULL)
    {
        char line [50];
       while(fgets(line, sizeof(line), file))
       {
        printf("Debug: read line: %s\n",line);
            if(strncmp(line, "password:", 9)==0)
            {
                sscanf(line + 9, "%s", stored_password);
                 strtok(stored_password, "\n");
             printf("Debug: Extracted password: '%s'\n", stored_password);
            }
            else if(strncmp(line, "username:", 9)==0)
            {
                sscanf(line + 9, "%s", stored_username);
                strtok(stored_username, "\n");
               printf("Debug: Extracted username: '%s'\n", stored_username);
            }
       }

    }
    fclose(file);

}
void blackJack(void)
{
    srand(time(0));
    int target = 21;
     int dealer_score = 0, player_score = 0;
     char* choices[]={"hit", "stand"};
     char player_choice[10];
     char answer[5];

     printf("welcome to Black Jack\n Do to want to play? (yes/no): ");
     scanf("%s",answer);

     if(strcmp(answer,"yes")!= 0)
     {
        printf("GoodBye!\n");
        return;
     }
     player_score = rand() % 10 + 1;
     dealer_score = rand() % 10 + 1;

     printf("dealer's first card: %d\n", dealer_score);
     printf("player's first card: %d\n",player_score);

     while(1)
     {
        printf("Do you want to (hit/stand)?: ");
        scanf("%s",player_choice);

        if(strcmp(player_choice,choices[0])== 0)
        {
            int card = rand() % 10 + 1;
            player_score += card;
            printf("you drew %d. your total is now %d\n",card, player_score );

            if(player_score > target)
            {
                printf("Bust! you lost. you scored %d\n",player_score);
                return;
            }
        }
        else if(strcmp(player_choice,choices[1])==0)
        {
            printf("you chose to stand, your final score is %d\n",player_score);

            while(dealer_score < 17)
            {
                int card = rand() % 10 + 1;
                dealer_score += card;
                printf("dealer drew %d. dealers total is now %d\n",card, dealer_score);

            }

            if(dealer_score > target || player_score > dealer_score )
            {
                printf("you win! Dealer score: %d. your score: %d\n",dealer_score, player_score);
            }

            else if(player_score < dealer_score)
            {
                printf("Dealer win! Dealer score: %d. your score: %d\n",dealer_score, player_score);
            }
            else
            {
                printf("It's a Tie! Dealer score: %d. your score: %d\n",dealer_score, player_score);
            }
            return;
            
        }
        else
        {
            printf("INVAILD choice. please type 'hit' or 'stand'.\n");
        }

     }
    }

