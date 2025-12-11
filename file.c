#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#define MAX_CONTACTS 100

int saveContactsToFile(AddressBook *addressBook) {
    FILE *f = fopen("contacts.csv", "w");
    if (!f) return 1;

    fprintf(f, "%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(f, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(f);
    return 0;
}

int loadContactsFromFile(AddressBook *addressBook) {
    FILE *f = fopen("contacts.csv", "r");
    if (!f) return 1;

    char line[256];
    int count = 0;

    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return 1;
    }

    count = atoi(line);
    if (count < 0) count = 0;
    if (count > MAX_CONTACTS) count = MAX_CONTACTS;

    addressBook->contactCount = 0;

    for (int i = 0; i < count; i++) {
        if (!fgets(line, sizeof(line), f))
            break;

        line[strcspn(line, "\r\n")] = '\0';

        char name[50], phone[20], email[50];

        int matched = sscanf(line, "%49[^,],%19[^,],%49[^\n]", name, phone, email);
        if (matched != 3)
            continue;

        strncpy(addressBook->contacts[addressBook->contactCount].name, name,
                sizeof(addressBook->contacts[0].name) - 1);

        strncpy(addressBook->contacts[addressBook->contactCount].phone, phone,
                sizeof(addressBook->contacts[0].phone) - 1);

        strncpy(addressBook->contacts[addressBook->contactCount].email, email,
                sizeof(addressBook->contacts[0].email) - 1);

        addressBook->contactCount++;

        if (addressBook->contactCount >= MAX_CONTACTS)
            break;
    }

    fclose(f);
    return 0;
}
