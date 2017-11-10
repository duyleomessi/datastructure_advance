#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>

SymbolTable createSymbolTable(Entry(*makeNode)(void *, void *), int(*compare)(void *, void *))
{
    SymbolTable sbt;
    sbt.entries = (Entry *)malloc(sizeof(Entry) * INITIAL_SIZE);
    sbt.current = 0;
    sbt.total = INITIAL_SIZE;
    sbt.makeNode = makeNode;
    sbt.compare = compare;
    return sbt;
};

int getEntryValue(void *key, const SymbolTable *book)
{
    int i;
    int current = book->current;
    Entry *entry = book->entries;
    for (i = 0; i < current; i++)
    {
        int cmp = (*(book->compare))(entry[i].key, key);
        if (cmp == 0)
        {
            return i;
        }
    }
    return -1;
}

void addEntry(void *key, void *value, SymbolTable *book)
{
    int exist = getEntryValue(key, book);
    if (exist)
    { // if the phone/key is exist overwrite the value
        Entry *entry = book->entries;
        entry[exist] = (*(book->makeNode)) (key, value);
    }
    else
    {
        if (isFull(book)) // book is full extend book then add
            extendPhoneBook(book);
    }
    Entry newEntry = (*(book->makeNode))(key, value);
    int current = book->current;
    book->entries[current] = newEntry;
    book->current += 1;
}

void dropSymbolTable(SymbolTable *sbt)
{
    free(sbt->entries);
}

void extendPhoneBook(SymbolTable *book)
{
    int extendQuantity;
    printf("Enter the number of phone you wanna extend: ");
    scanf("%d", &extendQuantity);

    int original_size = book->total;
    Entry *p = book->entries;
    p = (Entry *)realloc(p, (original_size + extendQuantity) * sizeof(Entry));
    if (p == NULL)
    {
        printf("Allocated failed\n");
        exit(1);
    }

    book->total += original_size + extendQuantity;
}

int isFull(SymbolTable *book)
{
    return (book->current == book->total);
}