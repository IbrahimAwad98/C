#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAMELENGTH 40
#define MAXGAMES 20
#define MAXUSERS 30
#define BUFFERSIZE 500

typedef struct
{
    char gameName[NAMELENGTH + 1];
    int rate;
} Game;

typedef struct
{
    Game list[MAXGAMES];
    char userName[NAMELENGTH + 1];
    int nrOfGames;
} User;

void readFromFile(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void administration(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void loginsAlternativs(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void boardGames(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void writeToFile(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void registerUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void removeUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void printUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);
void printUserAndRates(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName);

int main(void)
{
    User users[MAXUSERS];
    int nrOfUsers = 0;
    char fileName[NAMELENGTH + 1];
    printf("Welcome to boardgame ratings.\n");
    printf("Which file do you want to use: ");
    if (fgets(fileName, sizeof(fileName), stdin) == NULL)
    {
        printf("Error reading file name.\n");
        return 1;
    }
    fileName[strcspn(fileName, "\n")] = 0;
    readFromFile(users, &nrOfUsers, fileName);
    loginsAlternativs(users, &nrOfUsers, fileName);
    return 0;
}
void readFromFile(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    FILE *pFile = fopen(pFileName, "r");
    if (pFile == NULL)
    {
        printf("Error opening file: %s\n", pFileName);
        return;
    }
    char Buffer[BUFFERSIZE];
    *pNrOfUsers = 0;
    while (fgets(Buffer, sizeof(Buffer), pFile))
    {
        char *pToken = strtok(Buffer, "\n");
        strcpy(users[*pNrOfUsers].userName, pToken);
        users[*pNrOfUsers].nrOfGames = 0;
        pToken = strtok(NULL, "\n");
        while (pToken)
        {
            users[*pNrOfUsers].list[users[*pNrOfUsers].nrOfGames].rate = atoi(pToken);
            users[*pNrOfUsers].nrOfGames++;
            pToken = strtok(NULL, "\n");
        }
    }
    if (*pNrOfUsers == MAXUSERS)
    {
        printf("Maximum number of users (%d) reached.\n", MAXUSERS);
    }
    fclose(pFile);
}
void writeToFile(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    FILE *pFile = fopen(pFileName, "w");
    if (pFile == NULL)
    {
        printf("Failed to save due to unsuccessful file opening");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *pNrOfUsers; i++)
    {
        fprintf(pFile, "%s\n", users[i].userName);
    }
    fclose(pFile);
    printf("Saving all data to %s\n", pFileName);
}
void administration(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    printf("Administartion\n");
    int choice;
    bool isRunning = true;
    while (isRunning)
    {
        printf("          1) Add user\n");
        printf("          2) Remove user\n");
        printf("          3) Print all users\n");
        printf("          4) Print all user and their ratings\n");
        printf("          5) Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            registerUser(users, pNrOfUsers, pFileName);
            break;
        case 2:
            removeUser(users, pNrOfUsers, pFileName);
            break;
        case 3:
            printUser(users, pNrOfUsers, pFileName);
            break;
        case 4:
            printUserAndRates(users, pNrOfUsers, pFileName);
            break;
        case 5:
            loginsAlternativs(users, pNrOfUsers, pFileName);
            break;
        default:
            printf("Unknown command. Try again.\n");
        }
    }
}
void loginsAlternativs(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    char choice[NAMELENGTH + 1];
    bool userFound;
    while (1)
    {
        printf("Please enter user name, admin or quit: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        if (strcmp(choice, "admin") == 0)
        {
            administration(users, pNrOfUsers, pFileName);
        }
        else if (strcmp(choice, "quit") == 0)
        {
            writeToFile(users, pNrOfUsers, pFileName);
            printf("Goodbye!\n");
            exit(0);
        }
        else
        {
            userFound = false;
            for (int i = 0; i < *pNrOfUsers; i++)
            {
                if (strcmp(choice, users[i].userName) == 0)
                {
                    userFound = true;
                    printf("%s's boardgames\n", users[i].userName);
                    boardGames(users, pNrOfUsers, pFileName);
                    break;
                }
            }
            if (!userFound)
            {
                printf("User does not exist\n");
            }
        }
    }
}
void boardGames(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    int choice;
    bool isRunning = true;
    while (isRunning)
    {
        printf("          1) Print games\n");
        printf("          2) Add game\n");
        printf("          3) Search games\n");
        printf("          4) Remove game\n");
        printf("          5) Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            loginsAlternativs(users, pNrOfUsers, pFileName);
            break;
        default:
            printf("Unknown command. Try again.\n");
        }
    }
}
void registerUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    char user[NAMELENGTH + 1];
    bool foundUser;
    while (1)
    {
        printf("Register new user (q to quit): ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0';

        if (strcmp(user, "q") == 0)
        {
            return;
        }

        if (*pNrOfUsers >= MAXUSERS)
        {
            printf("The register is full!\n");
        }

        if (*pNrOfUsers < MAXUSERS)
        {
            foundUser = false;
            for (int i = 0; i < *pNrOfUsers; i++)
            {
                if (strcmp(user, users[i].userName) == 0)
                {
                    foundUser = true;
                    printf("User name exist! Please choose another.\n");
                }
            }
            if (!foundUser)
            {
                strcpy(users[*pNrOfUsers].userName, user);
                (*pNrOfUsers)++;
            }
        }
    }
}
void removeUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    char name[NAMELENGTH + 1], choice;
    bool foundUser;
    while (1)
    {
        printf("Remove user (q to quit): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "q") == 0)
        {
            break;
        }
        foundUser = false;
        for (int i = 0; i < *pNrOfUsers; i++)
        {
            if (strcmp(name, users[i].userName) == 0)
            {
                foundUser = true;
                if (users[i].list->rate > 0)
                {
                    printf("Warning: User has rated games.\n");
                    printf("Do you still want to remove %s (y/n)? ", name);
                    scanf("%c", &choice);
                    if (choice == 'n')
                    {
                        break;
                    }
                }
                for (int j = i; j < *pNrOfUsers - 1; j++)
                {
                    users[j] = users[j + 1];
                }

                (*pNrOfUsers)--;
                printf("Removed.\n");
            }
        }
        if (!foundUser)
        {
            printf("User do not exist! Please choose another.\n");
        }
    }
}
void printUser(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    if (*pNrOfUsers == 0)
    {
        printf("No users registrerad\n");
        return;
    }
    printf("Users:\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < *pNrOfUsers; i++)
    {
        printf("%s\n", users[i].userName);
    }
    printf("\n");
}
void printUserAndRates(User users[MAXUSERS], int *pNrOfUsers, const char *pFileName)
{
    printf("Users and boardgames:\n");
    printf("-----------------------------------------------------------\n");
    if (*pNrOfUsers == 0)
    {
        printf("No users registrerad\n");
        return;
    }
    for (int i = 0; i < *pNrOfUsers; i++)
    {
        printf("%s\n", users[i].userName);
        if (users[i].nrOfGames == 0)
        {
            printf("No games registrered\n");
        }
        for (int j = 0; j < users[i].nrOfGames; j++)
        {
            printf("    %-15s %d\n", users[i].list[j].gameName, users[i].list[j].rate);
        }
    }
    printf("\n");
}
