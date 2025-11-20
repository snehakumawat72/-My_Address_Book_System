#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

 
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("📭 No contacts to display.\n");
        return;
    }

    printf("\n📒================= CONTACT LIST =================📒\n");
    printf("----------------------------------------------------\n");
    printf("🧾 %-5s | %-20s | %-15s | %-25s\n", "No.", "Name", "Phone", "Email");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("👉 %-5d | %-20s | %-15s | %-25s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("----------------------------------------------------\n");
    printf("📇 Total Contacts: %d\n", addressBook->contactCount);
    printf("====================================================\n\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    printf("Contacts saved successfully.\n");
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if( addressBook -> contactCount >= MAX_CONTACTS ) 
    {
        printf("Address book is full !!.\n");
        return;
    }  
    Contact newContact;
    printf("Creating new contact\n");
    printf("Enter name : ");
    scanf(" %[^\n]", newContact.name);
    char phone[20];
    char email[30];
    int ret;
    //get the validate phone
    do
    {
        printf("Enter phone number : ");
        scanf("%s",newContact.phone);
        ret = valid_phone(newContact.phone, addressBook);
        if(ret == 0)
        {
            printf("Invlid number!\n");
        }
    }while(ret == 0);
    // get the validate email
    do
    {
        printf("Enter email id : ");
        scanf("%s",newContact.email);
        ret = valid_email(newContact.email, addressBook);
        if(ret == 0)
        {
            printf("Invalid Email ID\n!");
        }
    }while(ret == 0);
    
    strcpy(addressBook->contacts[addressBook->contactCount].name, newContact.name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, newContact.phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, newContact.email);

    addressBook->contactCount++;
    printf("Contact added succesfully\n");
}
int valid_phone(char *phone,AddressBook *addressBook)
{
    // number only digit
    if(strlen(phone) != 10)
        return 0;
    int i = 0;
    while(phone[i])
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            printf("Number should contain only digits\n");
            return 0;
        }
        i++;
    }
    // check duplicate
    for(i = 0; i < addressBook->contactCount; i++)
    {
        int cmp = strcmp(phone,addressBook->contacts[i].phone);
        if(cmp == 0)
            return 0;
    }
    return 1;
}

int valid_email(char *email,AddressBook *addressBook)
{
    int i = 0;
    char *ptr1 = strchr(email,'@');
    if(ptr1 == NULL)
        return 0;
    char *dot_ptr = strstr(email,".com");
    if(dot_ptr == NULL)
        return 0;

    while(email[i])
    {
        if(email[i] >= 'A' && email[i] <='Z')
        {
            return 0;
        }
        i++;
    }
    char *ptr = strchr(email,'@');
    if(!isalnum(email[0]) || !isalnum(*(ptr + 1)))
        return 0;
    for(i = 0; i < addressBook->contactCount; i++)
    {
        int cmp = strcmp(email,addressBook->contacts[i].email);
        if( cmp == 0)
            return 0;
    }
    return 1;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char Searchterm[50];
    do
    {
        printf("\nSearching Menu\n1.Search by Name\n2.Search by Phone number\n3.Search by Email\n");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {

            case 1:Search_name(Searchterm, addressBook);
                   break;

            case 2:Search_phone(Searchterm, addressBook);
                   break;

            case 3:Search_email(Searchterm, addressBook);
                   break;

            default:printf("Invalid Choice.Please Try again.\n");
        }
    }while(choice > 0 && choice <= 3);
}
// search name
void Search_name(char *Searchterm, AddressBook *addressBook )
{
    printf("Enter the name: ");
    scanf(" %[^\n]",Searchterm);
    int flag = 0;
    for(int i = 0; i<addressBook->contactCount; i++)
    {
       // int cmp = strcmp(name,addressbook->contact[i],Name)
       if(!strcmp(Searchterm,addressBook->contacts[i].name))
       {
        printf("%s %s %s", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        flag = 1;
        break;
       }
    }
    if(flag == 0)
        printf("Contact not found\n");
}
//search phone
int Search_phone(char *Searchterm, AddressBook *addressBook)
{
   // int flag = 0;
    printf("Enter the phone number: ");
    scanf("%s",Searchterm);
    for(int i=0; i < addressBook->contactCount; i++)
    {
        if(!strcmp(Searchterm, addressBook->contacts[i].phone))
        {
            printf("%s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contact not found\n");
    return -1;
    
}
//search email

int Search_email(char *Searchterm, AddressBook *addressBook)
{
   // int flag = 0;
    printf("Enter email id: ");
    scanf("%s",Searchterm);
    for(int i=0; i < addressBook->contactCount; i++)
    {
        if(!strcmp(Searchterm, addressBook->contacts[i].email))
        {
            printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contacts not found\n");
    return -1;

}

void editContact(AddressBook *addressBook)
{


	/* Define the logic for Editcontact */
    if(addressBook->contactCount == 0)
    {
        printf("No contacts to edit.\n");
        return;
    }

    int Search_choice;
    char Searchterm[50];
    int contactIndex = -1;
    int matching_index[MAX_CONTACTS]; // for name Search

    //serach menu
    printf("\nEdit Contact - Search by:\n");
    printf("1.name\n");
    printf("2.phone\n");
    printf("3.email\n");

    printf("Enter choice: ");
    scanf("%d",&Search_choice);
    getchar();

    switch(Search_choice)
    {
        case 1:contactIndex = Searchname_edit(Searchterm, addressBook,matching_index);
               break;

        case 2:contactIndex = Search_phone(Searchterm,addressBook);
               break;

        case 3:contactIndex = Search_email(Searchterm,addressBook);
               break;

        default:printf("Invalid choice!\n");    
                return;

    }
   if(contactIndex == -1)
       return;   //contact not found

    // editinf menu
    printf("Contact found - Ready to Edit\n");
    int edit_choice;

    do
    {
        //current contact informations
        printf("Current Contact Information:\n");
        printf("Name: %s\n",addressBook->contacts[contactIndex].name);
        printf("Phone: %s\n",addressBook->contacts[contactIndex].phone);
        printf("Email: %s\n",addressBook->contacts[contactIndex].email);

        //edit menu
        printf("Which field do you want to edit\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.Email\n");
        printf("4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&edit_choice);
        getchar();
        
        switch(edit_choice)
        {
            case 1: printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[contactIndex].name);
                    printf("Name updated successfully!\n");
                    break;

            case 2:{
                char newPhone[20];
                int valid;
                do
                {
                    printf("Enter new phone number: ");
                    scanf("%s",newPhone);
                    valid = valid_phone(newPhone, addressBook);
                    if(!valid)
                        printf("Invalid phone number, please try agein. \n");
                } while (!valid);

                strcpy(addressBook->contacts[contactIndex].phone, newPhone);
                printf("Phone updadted successfully!\n");
                break;
            }

            case 3:{
                char newEmail[30];
                int valid;
                do
                {
                    printf("enter new Email: ");
                    scanf("%s", newEmail);
                    valid = valid_email(newEmail, addressBook );
                    if(!valid)
                        printf("Invalid email, Please try again.\n");
                    } while (!valid);

                    strcpy(addressBook->contacts[contactIndex].email, newEmail);
                    printf("Email updated succesfully!\n");
                    break;   
                }

                case 4: printf("exiting edit menu.\n");
                        break;

                default: printf("Invalid choice! Please try again.\n");
                         break;
            }
        }while(edit_choice != 4);
}
int Searchname_edit(char *Searchterm, AddressBook *addressBook, int *index_arr)
{
    printf("Enter the old name: ");
    scanf(" %[^\n]",Searchterm);

    int flag = 0, j = 0;  
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(Searchterm, addressBook->contacts[i].name) == 0)
        {
            flag = 1;
            printf("%d. %s %s %s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            index_arr[j] = i;
            j++;
        } 
    }
    if(!flag)
    {
        printf("Contact not found\n");
        return -1;
    }
    int contact;
    printf("Choose the contact to be edited: ");
    scanf("%d",&contact);

    if(contact < 1 || contact > j)
    {
        printf("Invalid selection\n");
        return -1;
    }
    return index_arr[contact - 1];
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if(addressBook->contactCount == 0)
    {
        printf("No contact to delet.\n");
        return;
    }

    int Searchchoice;
    char Searchterm[50];
    int contactIndex = -1;
    int matching_index[MAX_CONTACTS];

    //Search Menu
    printf("\nDelete contact - Seach by: \n");
    printf("1.Name: \n");
    printf("2.Phone: \n");
    printf("3.Email: \n");
    printf("Enter choice: ");
    scanf("%d",&Searchchoice);
    getchar();

    switch(Searchchoice)
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
    if(contactIndex == -1)
    {
        return;
    }
    //Confirm deletion
    printf("Are you sure to delete this Contact.\n");
    char confirm;
    scanf(" %c",&confirm);
    if(confirm == 'y' || confirm == 'Y')
    {
        for(int i = contactIndex; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i+1];

        }
        addressBook->contactCount--;
        printf("Contact deleted successfully\n");
    }
    else
    {
        printf("Deletion cancelled.\n");
        return;
    }


}  

