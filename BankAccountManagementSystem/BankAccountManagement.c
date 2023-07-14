#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

struct User 
{
    char name[50];
    int accountNumber;
    float balance;
};

struct User users[MAX_USERS];
int numUsers = 0;

void saveDataToFile() 
{
    FILE* file;

    if (fopen_s(&file, "users.txt", "w") != 0) 
    {
        printf("Failed to create the file.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) 
    {
        fprintf(file, "%s %d %.2f\n", users[i].name, users[i].accountNumber, users[i].balance);
    }

    fclose(file);
}

void loadDataFromFile() 
{
    FILE* file;

    if (fopen_s(&file, "users.txt", "r") != 0) 
    {
        printf("File not found.\n");
        return;
    }

    numUsers = 0;

    while (fscanf_s(file, "%s %d %f", users[numUsers].name, sizeof(users[numUsers].name),
        &users[numUsers].accountNumber, &users[numUsers].balance) == 3) 
    {
        numUsers++;
    }

    fclose(file);
}

void addUser() 
{
    if (numUsers >= MAX_USERS) 
    {
        printf("Maximum number of users reached.\n");
        return;
    }

    struct User newUser;

    printf("Name: ");
    scanf_s("%s", newUser.name, sizeof(newUser.name));
    printf("Account Number: ");
    scanf_s("%d", &newUser.accountNumber);
    printf("Initial Balance: ");
    scanf_s("%f", &newUser.balance);

    users[numUsers] = newUser;
    numUsers++;

    printf("User successfully added.\n");
}

void updateUser() 
{
    int accountNumber;

    printf("Enter the account number of the user to update: ");
    scanf_s("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++) 
    {
        if (users[i].accountNumber == accountNumber) 
        {
            printf("New Name: ");
            scanf_s("%s", users[i].name, sizeof(users[i].name));
            printf("New Account Number: ");
            scanf_s("%d", &users[i].accountNumber);
            printf("New Balance: ");
            scanf_s("%f", &users[i].balance);

            printf("User successfully updated.\n");
            return;
        }
    }

    printf("User not found.\n");
}

void deleteUser() 
{
    int accountNumber;
    printf("Enter the account number of the user to delete: ");
    scanf_s("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++) 
    {
        if (users[i].accountNumber == accountNumber) 
        {
            for (int j = i; j < numUsers - 1; j++) 
            {
                users[j] = users[j + 1];
            }
            numUsers--;

            printf("User successfully deleted.\n");
            return;
        }
    }

    printf("User not found.\n");
}

void deposit() 
{
    int accountNumber;

    printf("Enter the account number to deposit money into: ");
    scanf_s("%d", &accountNumber);

    float amount;

    printf("Enter the amount to deposit: ");
    scanf_s("%f", &amount);

    for (int i = 0; i < numUsers; i++) 
    {
        if (users[i].accountNumber == accountNumber) 
        {
            users[i].balance += amount;

            printf("Money successfully deposited.\n");
            return;
        }
    }

    printf("User not found.\n");
}

void withdraw() 
{
    int accountNumber;

    printf("Enter the account number to withdraw money from: ");
    scanf_s("%d", &accountNumber);

    float amount;

    printf("Enter the amount to withdraw: ");
    scanf_s("%f", &amount);

    for (int i = 0; i < numUsers; i++) 
    {
        if (users[i].accountNumber == accountNumber) 
        {
            if (users[i].balance >= amount) 
            {
                users[i].balance -= amount;
                printf("Money successfully withdrawn.\n");
            }
            else 
            {
                printf("Insufficient balance.\n");
            }
            return;
        }
    }

    printf("User not found.\n");
}

void displayBalance() 
{
    int accountNumber;

    printf("Enter the account number to display the balance: ");
    scanf_s("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++) 
    {
        if (users[i].accountNumber == accountNumber) 
        {
            printf("Balance: %.2f\n", users[i].balance);
            return;
        }
    }

    printf("User not found.\n");
}

void printMenu() 
{
    printf("\n--- Bank Account Management ---\n");
    printf("1. Add User\n");
    printf("2. Update User\n");
    printf("3. Delete User\n");
    printf("4. Deposit\n");
    printf("5. Withdraw\n");
    printf("6. Display Balance\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() 
{
    loadDataFromFile();

    int choice;

    do 
    {
        printMenu();
        scanf_s("%d", &choice);

        switch (choice) 
        {
        case 1:
            addUser();
            break;
        case 2:
            updateUser();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            deposit();
            break;
        case 5:
            withdraw();
            break;
        case 6:
            displayBalance();
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    saveDataToFile();

    return 0;
}