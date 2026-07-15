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
