#include "graph.h"
#include "duy.h"

typedef struct
{
    graph graph;
} Product;

char getMenu();
void loadDataFromFileProduct(Product product);

int main()
{
    char choice;
    Product product;
    product.graph = create_graph();
    JRB tmp;
    do
    {
        choice = getMenu();
        switch (choice)
        {
        case '1':
            loadDataFromFileProduct(product);
            break;
        case '2':
            loadDataFromFileOrder(product);

            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            return 0;
        default:
            printf("invalid choice!! \n");
            break;
        }

    } while (choice != '6');
    return 0;
}

char getMenu()
{
    printf("1. In danh sach san pham\n");
    printf("2. In danh sach giao dich\n");
    printf("3. Hien thi muc do lien quan 2 san pham\n");
    printf("4. In danh sach cac san pham lien quan\n");
    printf("5. Hien thi moi lien he giua hai san pham\n");
    printf("6. Thoat\n");

    char choice;
    printf("You choice: ");
    scanf("%c", &choice);
    myfflush();
    return choice;
}

void loadDataFromFileProduct(Product product)
{
    char filename[] = "products.txt";
    FILE *f = myfopen(filename, "r");

    int totalLine = countLine(filename);
    printf("totalLine %d \n", totalLine);
    int i;

    int id;
    char name[30];
    printf("\n");
    for (i = 0; i < totalLine; i++)
    {
        fscanf(f, "%d %[^\n]", &id, name);
        //printf("%d %s \n", id, name);
        add_vertex(product.graph, id, name);
        printf("Ma san pham: %d\n", id);
        printf("Ten san pham: %s \n\n", get_vertex(product.graph, id));
    };

    fclose(f);
};

void loadDataFromFileOrder(Product product)
{
    char filename[] = "orderhistory.txt";
    FILE *f = myfopen(filename, "r");

    int totalLine = countLine(filename);
    //printf("totalLine %d \n", totalLine);
    int i;

    int id;
    char name[30];
    printf("\n");
    char buffer[81];
    for (i = 0; i < totalLine; i++)
    {
        fgets(buffer, 81, f);
        buffer[strlen(buffer) - 1] = '\0';

        char *token = strtok(buffer, " ");
        char from[15];
        strcpy(from, token);

        char to[15];
        token = strtok(NULL, " ");

        while(token != NULL) {
            strcpy(to, token);
            add_edge(data.graph, from, to, 1);
        }
    };
    fclose(f);
};