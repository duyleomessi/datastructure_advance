#include "adjgraph.h"
#include "duy.h"

typedef struct
{
    char name[30];
    Graph graph;
} map;

void loadDataFromFile(map data);

int main()
{
    map data;
    data.graph = createGraph();
    loadDataFromFile(data);
    return 0;
}

void loadDataFromFile(map data)
{
    char filename[30] = "data.txt";
    FILE *f = fopen(filename, "r");
    int i;
    int total_line = countLine(filename);
    char buffer[100];

    while (1)
    {
        fgets(buffer, 100, f);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(buffer, "[STATIONS]") == 0)
        {
            break;
        }
    }

    // name of station
    while (1)
    {
        fgets(buffer, 100, f);
        if (strcmp(buffer, "[LINES]\n") == 0)
        {
            break;
        }

        if (strcmp(buffer, "\n") == 0)
        {
            printf("new line %s \n", buffer);
            continue;
        }

        char tokens[2][200];
        getTokens(buffer, tokens, '=');
        printf("%s %s\n", tokens[0], tokens[1]);
    }

    // line
    while (1)
    {
        fgets(buffer, 100, f);
        if (feof(f))
        {
            break;
        }

        if (strcmp(buffer, "[LINES]\n") == 0)
        {
            continue;
        }

        if (strcmp(buffer, "\n") == 0)
        {
            printf("new line %s \n", buffer);
            break;
        }

        char tokens[2][200];
        getTokens(buffer, tokens, '=');
        standardName(tokens[1]);
        //printf("%s %s\n", tokens[0], tokens[1]);

        char station_line[30];
        strcpy(station_line, tokens[1]);

        // Returns first token
        char *token = strtok(station_line, " ");
        char station1[30];
        strcpy(station1, token);
        standardName(station1);
        printf("%s \n", station1);
        // Keep printing tokens while one of the
        // delimiters present in str[].
        char station2[30];
        token = strtok(NULL, " ");

        while (token != NULL)
        {
            strcpy(station2, token);
            standardName(station2);
            printf("%s \n", station2);

            addEdgeS(data.graph, station1, station2);

            strcpy(station1, station2);
            token = strtok(NULL, " ");
        }
    }

    fclose(f);
}