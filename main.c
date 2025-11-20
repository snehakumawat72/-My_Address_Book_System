#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
       printf("\n📒 Address Book Menu 📒\n");
       printf("1️⃣  Create contact ➕\n");
       printf("2️⃣  Search contact 🔍\n");
       printf("3️⃣  Edit contact ✏\n");
       printf("4️⃣  Delete contact ❌\n");
       printf("5️⃣  List all contacts 📋\n");
       printf("6️⃣  Save contacts 💾\n");
       printf("7️⃣  Exit 🚪\n");

       printf("\n👉 Enter your choice: ");
       choice = 0;
       scanf("%d", &choice);
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
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
