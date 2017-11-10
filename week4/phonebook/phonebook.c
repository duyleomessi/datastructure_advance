#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "duy.h"

char getMenu();
void loadPhoneBook(JRB phoneBook, FILE *fout, int numLine);
void insertNewNode(JRB phoneBook, char *key, char *value);
void traverse_tree(JRB phoneBook);
int main(int argc, char *argv[])
{
    char filename[30] = "contact.txt";
    FILE *f = myfopen(filename, "rw");
    JRB phoneBook = make_jrb();
    int numLine = countLine(f);
    char name[30];
    char number[30];
    rewind(f);

    JRB deleteNumber;
    //printf("numLine %d\n", numLine);
    char choice;
    do
    {
        choice = getMenu();
        switch (choice)
        {
        case '1':
            loadPhoneBook(phoneBook, f, numLine);
            fclose(f);
            traverse_tree(phoneBook);
            break;
        case '2':
            printf("Enter the name you wanna insert: ");
            scanf("%[^\n]", name);
            myfflush();
            printf("Enter the number you wanna insert: ");
            scanf("%[^\n]", number);
            myfflush();
            insertNewNode(phoneBook, number, name);
            traverse_tree(phoneBook);
            break;
        case '3':
            printf("Enter the number you wanna delete: ");
            scanf("%[^\n]", number);
            myfflush();
            deleteNumber = jrb_find_str(phoneBook, number);
            if (deleteNumber == NULL)
            {
                printf("Not found");
            }
            else
            {
                printf("Delete successfully!!!!");
                jrb_delete_node(deleteNumber);
                traverse_tree(phoneBook);
            }
            break;
        case '0':
            return 0;
        default:
            printf("Invalid input!!!");
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

void loadPhoneBook(JRB phoneBook, FILE *fout, int numLine)
{
    int i;
    char buffer[500];
    char tokens[2][200];
    for (i = 0; i < numLine; i++)
    {
        fgets(buffer, 500, fout);
        getTokens(buffer, tokens, '-');
        //printf("token[1]: %s \n", tokens[1]);
        insertNewNode(phoneBook, tokens[1], tokens[0]);
    }
}

void insertNewNode(JRB phoneBook, char *key, char *value)
{
    char *skey = (char *)malloc(sizeof(char) * sizeof(key));
    char *sname = (char *)malloc(sizeof(char) * sizeof(value));

    strcpy(skey, key);
    strcpy(sname, value);

    //printf("skey: %s\n", skey);
    Jval jname = new_jval_s(sname);
    jrb_insert_str(phoneBook, skey, jname);
}

void traverse_tree(JRB phoneBook)
{
    JRB tmp;
    jrb_traverse(tmp, phoneBook)
    {
        char *key = jval_s(tmp->key);
        char *name = jval_s(tmp->val);
        printf("%s %s\n", name, key);
    }
}