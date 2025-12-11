#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include "file.h"

// Safe integer input function
int getIntInput() {
    char buffer[32];
    long value;
    char *end;

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return -1; 
    }

    value = strtol(buffer, &end, 10);

    if (end == buffer || (*end != '\n' && *end != '\0')) {
        return -1;  // Invalid number
    }

    return (int)value;
}

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook);  

    do {
        printf("\nAddress Book Menu\n");
        printf("1  Create contact\n");
        printf("2  Search contact\n");
        printf("3  Edit contact\n");
        printf("4  Delete contact\n");
        printf("5  List all contacts\n");
        printf("6  Save contacts\n");
        printf("7  Exit\n");

        printf("\nEnter your choice: ");

        choice = getIntInput();
        if (choice == -1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                break;

            case 5:
                listContacts(&addressBook);
                break;

            case 6: {
                int rc = saveContactsToFile(&addressBook);
                if (rc == 0)
                    printf("Contacts saved successfully.\n");
                else
                    printf("Failed to save contacts.\n");
                break;
            }

            case 7:
                saveAndExit(&addressBook);  // Saves + exits
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
