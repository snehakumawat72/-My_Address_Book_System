#include <stdio.h>
#include "file.h"
#include<stdlib.h>

void saveContactsToFile(AddressBook *addressBook) {
    FILE * fptr = fopen("contacts.csv","w");
    fprintf(fptr,"%d\n",addressBook -> contactCount);
    for(int i = 0; i< addressBook -> contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
        }
        fclose(fptr);
        printf("✅Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE * fptr = fopen("contacts.csv","r");
    if(fptr == NULL)
    {
        printf("❌❌ Error: Could not open contacts file. ❌❌\n");
        return;
    }
    char str[100];
    fscanf(fptr,"%s\n",str);
    int count = atoi(str);
   // addressBook->contactCount = count;
    for(int i=0; i<count; i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);

            addressBook->contactCount++;
    }
    fclose(fptr);

    
}
