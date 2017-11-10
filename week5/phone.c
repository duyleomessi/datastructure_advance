#include <stdio.h>
#include <string.h>
#include "duy.h"
#include "bt-5.0.0/inc/btree.h"
char getMenu();
void loadData(BTA *btfile);
void insertNewNode(BTA *btfile, char *name, char *phone, char *email);
void travel_tree(BTA *btfile);
void insertContact(BTA *btfile);
void deleteContact(BTA *btfile);

typedef struct
{
    char name[50];
    char email[50];
} Data;

int main()
{
    btinit();
    BTA *btfile = btcrt("contact.bt", 0, 0);
    char choice;
    do
    {
        choice = getMenu();
        switch (choice)
        {
        case '1':
            loadData(btfile);
            travel_tree(btfile);
            break;
        case '2':
            insertContact(btfile);
            travel_tree(btfile);
            break;
        case '3':
            deleteContact(btfile);
            travel_tree(btfile);
            break;
        case '0':
            return 0;
        default:
            printf("Invalid input!!");
        }
    } while (choice != '0');
    return 0;
}

char getMenu()
{
    char choice;
    printf("\n");
    printf("1. Load phone book \n");
    printf("2. Insert \n");
    printf("3. Delete \n");
    printf("0. Quit\n\n");

    printf("Your choice: ");
    scanf("%c", &choice);
    myfflush();

    return choice;
}

void loadData(BTA *btfile)
{
    char filename[30] = "contact.txt";
    FILE *f = myfopen(filename, "r");
    char buffer[200];
    char tokens[3][200];
    int i;
    int numLine = countLine(filename);
    for (i = 0; i < numLine; i++)
    {
        fgets(buffer, 200, f);
        getTokens(buffer, tokens, '-');
        insertNewNode(btfile, tokens[0], tokens[1], tokens[2]);
    };
}

void insertNewNode(BTA *btfile, char *name, char *phone, char *email)
{
    Data data;
    strcpy(data.name, name);
    strcpy(data.email, email);
    //printf("%s %s %s\n", data.name, phone, data.email);
    btins(btfile, phone, (char *)&data, sizeof(data));
}

void travel_tree(BTA *btfile)
{
    btpos(btfile, ZSTART);
    char phone[30];
    Data data;
    int rsize;
    printf("\n");
    while (btseln(btfile, phone, (char *)&data, sizeof(data), &rsize) != QNOKEY)
    {
        printf("%s %s %s\n", phone, data.name, data.email);
    }
    printf("\n");
}

void insertContact(BTA *btfile)
{
    char phone[15];
    Data data;

    printf("Enter the number you wanna insert: ");
    scanf("%[^\n]", phone);
    myfflush();

    printf("Enter the email you wanna insert: ");
    scanf("%[^\n]", data.email);
    myfflush();

    printf("Enter the name you wanna insert: ");
    scanf("%[^\n]", data.name);
    myfflush();

    insertNewNode(btfile, data.name, phone, data.email);
};

void deleteContact(BTA *btfile) {
    char phone[15];
    printf("Enter the number you wanna delete: ");
    scanf("%[^\n]", phone);
    myfflush();

    if (btdel(btfile, phone) != 0) {
        printf("delete failed\n");
    };
};