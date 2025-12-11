#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int valid_phone(char *, AddressBook *addressBook);
int valid_email(char *, AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void Search_name(char *, AddressBook *addressBook);
int Search_phone(char *, AddressBook *addressBook);
int Search_email(char *, AddressBook *addressBook);
void editContact(AddressBook *addressBook);
int Searchname_edit(char *, AddressBook *addressBook, int *);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
int saveContactsToFile(AddressBook *addressBook);
int loadContactsFromFile(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

#endif
