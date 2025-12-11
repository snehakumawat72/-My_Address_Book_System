#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    printf("\n================= CONTACT LIST =================\n");
    printf("-------------------------------------------------\n");
    printf(" %-5s | %-20s | %-15s | %-25s\n", "No.", "Name", "Phone", "Email");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf(" %-5d | %-20s | %-15s | %-25s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-------------------------------------------------\n");
    printf("Total Contacts: %d\n", addressBook->contactCount);
    printf("=================================================\n\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    int rc = saveContactsToFile(addressBook);
    if (rc == 0) {
        printf("Contacts saved successfully.\n");
    } else {
        printf("Failed to save contacts (error %d).\n", rc);
    }
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full.\n");
        return;
    }

    Contact newContact;
    printf("Creating new contact\n");
    printf("Enter name: ");
    scanf(" %49[^\n]", newContact.name);

    int ret;
    do
    {
        printf("Enter phone number: ");
        scanf("%19s", newContact.phone);
        ret = valid_phone(newContact.phone, addressBook);
        if (ret == 0)
            printf("Invalid number!\n");
    } while (ret == 0);

    do
    {
        printf("Enter email id: ");
        scanf("%49s", newContact.email);
        ret = valid_email(newContact.email, addressBook);
        if (ret == 0)
            printf("Invalid email id!\n");
    } while (ret == 0);

    strcpy(addressBook->contacts[addressBook->contactCount].name, newContact.name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, newContact.phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, newContact.email);

    addressBook->contactCount++;
    printf("Contact added successfully\n");
}

int valid_phone(char *phone, AddressBook *addressBook)
{
    if (strlen(phone) != 10)
        return 0;
    for (int i = 0; phone[i]; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            printf("Number should contain only digits\n");
            return 0;
        }
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            return 0;
    }
    return 1;
}

int valid_email(char *email, AddressBook *addressBook)
{
    if (strchr(email, '@') == NULL) return 0;
    if (strstr(email, ".com") == NULL) return 0;
    for (int i = 0; email[i]; i++)
    {
        if (email[i] >= 'A' && email[i] <= 'Z')
            return 0;
    }
    char *ptr = strchr(email, '@');
    if (!ptr) return 0;
    if (!isalnum((unsigned char)email[0]) || !isalnum((unsigned char)*(ptr + 1)))
        return 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0)
            return 0;
    }
    return 1;
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    char Searchterm[50];
    do
    {
        printf("\nSearching Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email\n");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }
        getchar();

        switch (choice)
        {
            case 1: Search_name(Searchterm, addressBook); break;
            case 2: Search_phone(Searchterm, addressBook); break;
            case 3: Search_email(Searchterm, addressBook); break;
            default: if (choice != 0) printf("Invalid Choice. Please Try again.\n"); break;
        }
    } while (choice > 0 && choice <= 3);
}

void Search_name(char *Searchterm, AddressBook *addressBook)
{
    printf("Enter the name: ");
    scanf(" %49[^\n]", Searchterm);
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Searchterm, addressBook->contacts[i].name) == 0)
        {
            printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            flag = 1;
            break;
        }
    }
    if (!flag) printf("Contact not found\n");
}

int Search_phone(char *Searchterm, AddressBook *addressBook)
{
    printf("Enter the phone number: ");
    scanf("%19s", Searchterm);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Searchterm, addressBook->contacts[i].phone) == 0)
        {
            printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contact not found\n");
    return -1;
}

int Search_email(char *Searchterm, AddressBook *addressBook)
{
    printf("Enter email id: ");
    scanf("%49s", Searchterm);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Searchterm, addressBook->contacts[i].email) == 0)
        {
            printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contact not found\n");
    return -1;
}

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to edit.\n");
        return;
    }

    int Search_choice;
    char Searchterm[50];
    int contactIndex = -1;
    int matching_index[MAX_CONTACTS];

    printf("\nEdit Contact - Search by:\n");
    printf("1.name\n2.phone\n3.email\n");
    printf("Enter choice: ");
    if (scanf("%d", &Search_choice) != 1) { while (getchar() != '\n'); return; }
    getchar();

    switch (Search_choice)
    {
        case 1: contactIndex = Searchname_edit(Searchterm, addressBook, matching_index); break;
        case 2: contactIndex = Search_phone(Searchterm, addressBook); break;
        case 3: contactIndex = Search_email(Searchterm, addressBook); break;
        default: printf("Invalid choice!\n"); return;
    }
    if (contactIndex == -1) return;

    int edit_choice;
    do
    {
        printf("Current Contact Information:\n");
        printf("Name: %s\n", addressBook->contacts[contactIndex].name);
        printf("Phone: %s\n", addressBook->contacts[contactIndex].phone);
        printf("Email: %s\n", addressBook->contacts[contactIndex].email);

        printf("Which field do you want to edit\n1.Name\n2.Phone\n3.Email\n4.Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &edit_choice) != 1) { while (getchar() != '\n'); edit_choice = 4; }
        getchar();

        switch (edit_choice)
        {
            case 1:
                printf("Enter new name: ");
                scanf(" %49[^\n]", addressBook->contacts[contactIndex].name);
                printf("Name updated successfully!\n");
                break;

            case 2:
            {
                char newPhone[20];
                int valid;
                do
                {
                    printf("Enter new phone number: ");
                    scanf("%19s", newPhone);
                    valid = valid_phone(newPhone, addressBook);
                    if (!valid) printf("Invalid phone number, please try again.\n");
                } while (!valid);

                strcpy(addressBook->contacts[contactIndex].phone, newPhone);
                printf("Phone updated successfully!\n");
                break;
            }

            case 3:
            {
                char newEmail[50];
                int valid;
                do
                {
                    printf("Enter new Email: ");
                    scanf("%49s", newEmail);
                    valid = valid_email(newEmail, addressBook);
                    if (!valid) printf("Invalid email, Please try again.\n");
                } while (!valid);

                strcpy(addressBook->contacts[contactIndex].email, newEmail);
                printf("Email updated successfully!\n");
                break;
            }

            case 4:
                printf("Exiting edit menu.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (edit_choice != 4);
}

int Searchname_edit(char *Searchterm, AddressBook *addressBook, int *index_arr)
{
    printf("Enter the old name: ");
    scanf(" %49[^\n]", Searchterm);

    int flag = 0, j = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Searchterm, addressBook->contacts[i].name) == 0)
        {
            flag = 1;
            printf("%d. %s %s %s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            index_arr[j] = i;
            j++;
        }
    }
    if (!flag)
    {
        printf("Contact not found\n");
        return -1;
    }
    int contact;
    printf("Choose the contact to be edited: ");
    if (scanf("%d", &contact) != 1) { while (getchar() != '\n'); return -1; }

    if (contact < 1 || contact > j)
    {
        printf("Invalid selection\n");
        return -1;
    }
    return index_arr[contact - 1];
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contact to delete.\n");
        return;
    }

    int Searchchoice;
    char Searchterm[50];
    int contactIndex = -1;
    int matching_index[MAX_CONTACTS];

    printf("\nDelete contact - Search by:\n1.Name\n2.Phone\n3.Email\n");
    printf("Enter choice: ");
    if (scanf("%d", &Searchchoice) != 1) { while (getchar() != '\n'); return; }
    getchar();

    switch (Searchchoice)
    {
        case 1:
            contactIndex = Searchname_edit(Searchterm, addressBook, matching_index);
            break;
        case 2:
            contactIndex = Search_phone(Searchterm, addressBook);
            break;
        case 3:
            contactIndex = Search_email(Searchterm, addressBook);
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }
    if (contactIndex == -1) return;

    printf("Are you sure to delete this Contact? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    if (confirm == 'y' || confirm == 'Y')
    {
        for (int i = contactIndex; i < addressBook->contactCount - 1; i++)
            addressBook->contacts[i] = addressBook->contacts[i + 1];

        addressBook->contactCount--;
        printf("Contact deleted successfully\n");
    }
    else
    {
        printf("Deletion cancelled.\n");
    }
}
