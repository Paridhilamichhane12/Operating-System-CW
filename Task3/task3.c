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
//======================================================
// PART 2: FILE OPERATIONS
//======================================================

//----------------------
// Create File
//----------------------

void create_file(char username[])
{
    char filename[100];
    char content[500];

    printf("Enter File Name: ");
    scanf("%99s", filename);

    getchar();

    printf("Enter File Content:\n");
    fgets(content, sizeof(content), stdin);

    FILE *fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Error creating file.\n");
        return;
    }

    fprintf(fp, "%s", content);

    fclose(fp);

    printf("File '%s' created successfully.\n", filename);

    audit_log(username, "CREATE", filename);
}

//----------------------
// Write File
//----------------------

void write_file(char username[])
{
    char filename[100];
    char content[500];

    printf("Enter File Name: ");
    scanf("%99s", filename);

    getchar();

    printf("Enter Text to Append:\n");
    fgets(content, sizeof(content), stdin);

    FILE *fp = fopen(filename, "a");

    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }

    fprintf(fp, "%s", content);

    fclose(fp);

    printf("Data written successfully.\n");

    audit_log(username, "WRITE", filename);
}

//----------------------
// Read File
//----------------------

void read_file(char username[])
{
    char filename[100];
    char buffer[500];

    printf("Enter File Name: ");
    scanf("%99s", filename);

    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\n========== File Content ==========\n");

    while(fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);
    }

    printf("\n==================================\n");

    fclose(fp);

    audit_log(username, "READ", filename);
}

//----------------------
// Delete File
//----------------------

void delete_file(char username[])
{
    char filename[100];

    printf("Enter File Name: ");
    scanf("%99s", filename);

    if(remove(filename) == 0)
    {
        printf("File deleted successfully.\n");

        audit_log(username, "DELETE", filename);
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}
//======================================================
// PART 3: FILE PERMISSION SYSTEM & ENCRYPTION
//======================================================

//----------------------
// File Permission Structure
//----------------------

typedef struct
{
    char permission[10];

} FilePermission;


//----------------------
// Check Permission
//----------------------

int has_permission(FilePermission fp,
                   int owner,
                   int group,
                   char action)
{
    int index;

    if(owner)
        index = 0;
    else if(group)
        index = 3;
    else
        index = 6;

    if(action == 'r')
        return fp.permission[index] == 'r';

    if(action == 'w')
        return fp.permission[index + 1] == 'w';

    if(action == 'x')
        return fp.permission[index + 2] == 'x';

    return 0;
}


//----------------------
// Display Permissions
//----------------------

void show_permission(FilePermission fp)
{
    printf("\nCurrent Permission : %s\n",
           fp.permission);

    printf("Owner  : %c %c %c\n",
           fp.permission[0],
           fp.permission[1],
           fp.permission[2]);

    printf("Group  : %c %c %c\n",
           fp.permission[3],
           fp.permission[4],
           fp.permission[5]);

    printf("Others : %c %c %c\n",
           fp.permission[6],
           fp.permission[7],
           fp.permission[8]);
}


//----------------------
// Encrypt File
//----------------------

void encrypt_file(char username[])
{
    char input[100];
    char output[100];

    printf("Enter Input File : ");
    scanf("%99s", input);

    printf("Enter Output File : ");
    scanf("%99s", output);

    FILE *in = fopen(input,"rb");
    FILE *out = fopen(output,"wb");

    if(in == NULL || out == NULL)
    {
        printf("Encryption Error.\n");
        return;
    }

    int ch;

    while((ch = fgetc(in)) != EOF)
    {
        fputc(ch ^ XOR_KEY,out);
    }

    fclose(in);
    fclose(out);

    printf("File Encrypted Successfully.\n");

    audit_log(username,
              "ENCRYPT",
              output);
}


//----------------------
// Decrypt File
//----------------------

void decrypt_file(char username[])
{
    char input[100];
    char output[100];

    printf("Enter Encrypted File : ");
    scanf("%99s", input);

    printf("Enter Output File : ");
    scanf("%99s", output);

    FILE *in = fopen(input,"rb");
    FILE *out = fopen(output,"wb");

    if(in == NULL || out == NULL)
    {
        printf("Decryption Error.\n");
        return;
    }

    int ch;

    while((ch = fgetc(in)) != EOF)
    {
        fputc(ch ^ XOR_KEY,out);
    }

    fclose(in);
    fclose(out);

    printf("File Decrypted Successfully.\n");

    audit_log(username,
              "DECRYPT",
              output);
}
//======================================================
// PART 4: MAIN FUNCTION
//======================================================

int main()
{
    FILE *fp = fopen(USERS_FILE, "r");

    // Create default users if users.txt does not exist
    if(fp == NULL)
    {
        fp = fopen(USERS_FILE, "w");

        fprintf(fp, "admin:admin123\n");
        fprintf(fp, "student:pass123\n");

        fclose(fp);
    }
    else
    {
        fclose(fp);
    }

    char username[50];

    login(username);

    FilePermission permission = {"rwxr-xr--"};

    int choice;

    do
    {
        printf("\n=====================================\n");
        printf(" Secure File Management System\n");
        printf("=====================================\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. View File Permission\n");
        printf("6. Encrypt File\n");
        printf("7. Decrypt File\n");
        printf("8. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                if(has_permission(permission,1,0,'w'))
                    create_file(username);
                else
                    printf("Permission Denied.\n");
                break;

            case 2:
                if(has_permission(permission,1,0,'w'))
                    write_file(username);
                else
                    printf("Permission Denied.\n");
                break;

            case 3:
                if(has_permission(permission,1,0,'r'))
                    read_file(username);
                else
                    printf("Permission Denied.\n");
                break;

            case 4:
                if(has_permission(permission,1,0,'w'))
                    delete_file(username);
                else
                    printf("Permission Denied.\n");
                break;

            case 5:
                show_permission(permission);
                break;

            case 6:
                encrypt_file(username);
                break;

            case 7:
                decrypt_file(username);
                break;

            case 8:
                printf("\nExiting Program...\n");
                audit_log(username,"LOGOUT","SYSTEM");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice != 8);

    return 0;
}
