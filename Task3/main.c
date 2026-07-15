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
