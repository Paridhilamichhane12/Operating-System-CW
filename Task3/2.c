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
