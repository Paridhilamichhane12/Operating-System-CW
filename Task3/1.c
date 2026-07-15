//======================================================
// PART 1: HEADER FILES, CONSTANTS,
// USER AUTHENTICATION & AUDIT LOGGING
//======================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERS_FILE "users.txt"
#define AUDIT_LOG "audit_log.txt"
#define XOR_KEY 0x5A

//----------------------
// Audit Logging
//----------------------

void audit_log(const char *username,
               const char *action,
               const char *file)
{
    FILE *fp = fopen(AUDIT_LOG, "a");

    if(fp == NULL)
    {
        printf("Unable to open audit log.\n");
        return;
    }

    time_t now = time(NULL);

    char *date = ctime(&now);

    date[strcspn(date,"\n")] = '\0';

    fprintf(fp,
            "[%s] User=%s Action=%s File=%s\n",
            date,
            username,
            action,
            file);

    fclose(fp);
}

//----------------------
// User Authentication
//----------------------

int authenticate(char username[],
                 char password[])
{
    FILE *fp = fopen(USERS_FILE,"r");

    if(fp == NULL)
    {
        printf("Users file not found.\n");
        return 0;
    }

    char line[100];

    while(fgets(line,sizeof(line),fp))
    {
        line[strcspn(line,"\n")] = '\0';

        char *user = strtok(line,":");
        char *pass = strtok(NULL,":");

        if(user != NULL &&
           pass != NULL)
        {
            if(strcmp(user,username)==0 &&
               strcmp(pass,password)==0)
            {
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);

    return 0;
}

//----------------------
// Login
//----------------------

void login(char username[])
{
    char password[50];

    printf("=====================================\n");
    printf(" Secure File Management System\n");
    printf("=====================================\n");

    printf("Username : ");
    scanf("%49s",username);

    printf("Password : ");
    scanf("%49s",password);

    if(authenticate(username,password))
    {
        printf("\nLogin Successful!\n");
        audit_log(username,"LOGIN","SYSTEM");
    }
    else
    {
        printf("\nInvalid Username or Password.\n");
        exit(0);
    }
}
