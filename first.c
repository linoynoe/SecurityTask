#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define FILENAME "credentials.txt"

void dump_credentials() {
    FILE *file = fopen(FILENAME, "r");
    char line[MAX_LEN];

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void authenticate() {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char file_username[MAX_LEN];
    char file_password[MAX_LEN];
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    gets(username); // Vulnerable function

    printf("Enter password: ");
    gets(password); // Vulnerable function

    int authenticated = 0;
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            authenticated = 1;
            break;
        }
    }

    fclose(file);

    if (authenticated) {
        printf("Access granted!\n");
    } else {
        printf("Access denied!\n");
    }
}

void register_user() {
    char username[MAX_LEN];
    char password[MAX_LEN];
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter new username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    printf("Enter new password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;  // Remove newline character

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("User registered successfully!\n");
}

int main() {
    int choice;
    printf("1. Register\n2. Authenticate\n3. Dump Credentials (Admin Only)\nChoose an option: ");
    scanf("%d", &choice);
    getchar();  // Consume newline character left by scanf

    switch (choice) {
        case 1:
            register_user();
            break;
        case 2:
            authenticate();
            break;
        case 3:
            dump_credentials();
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
