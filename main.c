#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include "file.h"

void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

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

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        getchar();

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
                    printf("Failed to save contacts (error %d).\n", rc);
                break;
            }

            case 7:
                saveAndExit(&addressBook);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
