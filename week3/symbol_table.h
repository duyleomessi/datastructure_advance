#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct
{
    void *key;
    void *value;
} Entry;

typedef struct
{
    Entry *entries;
    int current, total;
    Entry(*makeNode)(void *, void *);
    int(*compare)(void *, void *);
} SymbolTable;


SymbolTable createSymbolTable(Entry(*makeNode)(void *, void *), int(*compare)(void *, void *));
void addEntry(void *key, void *value, SymbolTable *book);
void dropSymbolTable(SymbolTable *sbt);
int getEntryValue(void *key, const SymbolTable *book);
void extendPhoneBook(SymbolTable *book);
int isFull(SymbolTable *book);
