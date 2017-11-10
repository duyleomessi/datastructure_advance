#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "duy.h"

Entry makePhoneBook(void *phone, void *name)
{
    Entry res;
    res.key = malloc(sizeof(int));
    memcpy(res.key, phone, sizeof(int)); // copy character from phone to res.key
    res.value = strdup((char *)name);    // return pointer to new string
    return res;
}

int comparePhone(void *key1, void *key2)
{
    int num1 = *((int *)key1);
    int num2 = *((int *)key2);
    if (num1 == num2)
    {
        return 0;
    }
    else if (num1 < num2)
        return -1;
    else
        return 1;
}

char getMenu()
{
    char choice;
    printf("\n");
    printf("1. Add new entry\n");
    printf("2. List all entry\n");
    printf("3. Search by phone\n");
    printf("0. Quit\n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%c", &choice);
    myfflush();
    return choice;
}

int searchPhone(int phone, SymbolTable book) {
    Entry *entry = book.entries;
    int current = book.current;
    int i;
    int found = 0;
    for(i = 0; i < current; i++) {
        if (phone == *((int *)entry[i].key)) {
            found = 1;
            return i;
        }
    }
    return -1;
};

int main(int argc, char *argv[])
{
    SymbolTable phoneBook = createSymbolTable(&makePhoneBook, &comparePhone);
    Entry *newEntry;
    Entry *currentEntry = phoneBook.entries;
    int i;
    int phone;
    char name[30];
    char choice;
    do
    {
        choice = getMenu();
        switch (choice)
        {
        case '1':
            printf("Enter the phone you wanna insert: ");
            scanf("%d", &phone);
            myfflush();
            printf("Enter the name: ");
            scanf("%[^\n]", name);
            myfflush();
            addEntry(&phone, &name, &phoneBook);
            printf("Current phone: %d\n", phoneBook.current);
            break;
        case '2':
            for(i = 0; i < phoneBook.current; i++) {
                printf("%-30d%-30s\n",* ((int *) phoneBook.entries[i].key),((char *)phoneBook.entries[i].value));
            }
            break;
        case '3':
            printf("Enter the phone you wanna search: ");
            scanf("%d", &phone);
            myfflush();

            int position = searchPhone(phone, phoneBook);
            if (position == -1) {
                printf("Not found!!!!\n");
            } else {
                printf("%-30d%-30s\n",* ((int *) phoneBook.entries[position].key),((char *)phoneBook.entries[position].value));
            }
            break;
        case '0':
            //dropSymbolTable(&phoneBook);
            return 0;
        default:
            printf("Invalid choice!! Choose again!!!");
        }
    } while (choice != '0');
}
