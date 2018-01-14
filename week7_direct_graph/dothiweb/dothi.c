#include "digraph.h"
#include "duy.h"

typedef struct
{
    Graph graph;
} site;

int *getNM(FILE *f);
void makeGraph(FILE *f, site mysite);

int main(int argc, char *argv[])
{
    site mysite;
    if (argc < 2)
    {
        printf("Invalid number of argc\n");
        return 0;
    }

    if (strcmp(argv[1], "about") == 0)
    {
        printf("Bai thi lap trinh C nang cao HK2-2014-2015 \n");
        return 0;
    }

    if (strcmp(argv[1], "size") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid number of argc\n");
            return 0;
        }
        else
        {
            char filename[15];
            strcpy(filename, argv[2]);
            FILE *f = myfopen(filename, "r");

            int *nm = getNM(f);
            printf("%d %d\n", nm[0], nm[1]);
            fclose(f);
        }
    }

    if (strcmp(argv[1], "out") == 0)
    {
        if (argc != 4)
        {
            printf("Invalid number of argc\n");
            return 0;
        }
        else
        {
            int id = atoi(argv[3]);
            if (id == 0)
            {
                printf("Invalid argument \n");
            }
            else
            {
                char filename[15];

                strcpy(filename, argv[2]);
                FILE *f = myfopen(filename, "r");
                mysite.graph = createGraph();

                makeGraph(f, mysite);
                char *foundName = getVertex(mysite.graph, id);
                if (foundName == NULL)
                {
                    printf("404 Not found \n");
                    return 0;
                }
                else
                {
                    printf("%s \n", foundName);
                }
                fclose(f);
                dropGraph(mysite.graph);
            }
        }
    }

    if (strcmp(argv[1], "maxin") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid argument \n");
            return 0;
        }
        else
        {
            char filename[15];

            strcpy(filename, argv[2]);
            FILE *f = myfopen(filename, "r");
            mysite.graph = createGraph();

            makeGraph(f, mysite);
            JRB tmp;
            int indegreeVar;
            int maxIndegree = -1;
            int output[100];
            int foundId;

            jrb_traverse(tmp, mysite.graph.vertices) {
                int v = jval_i(tmp->key);
                //printf("%d \n", v);
                indegreeVar = inDegree(mysite.graph, v, output);
                //printf("%d \n", indegreeVar);
                if (indegreeVar >= maxIndegree) {
                    maxIndegree = indegreeVar;
                    foundId = v;
                }
            }

            char *foundVertex = getVertex(mysite.graph, foundId);
            printf("%s \n", foundVertex); 
        }
    }
    return 0;
}

int *getNM(FILE *f)
{
    char buffer[81];
    static int result[2];
    int i;

    fgets(buffer, 81, f);
    buffer[strlen(buffer) - 1] = '\0';
    result[0] = atoi(buffer);

    if (result[0] == 0)
    {
        printf("Wrong format file\n");
        exit(0);
    }

    for (i = 0; i < result[0]; i++)
    {
        fgets(buffer, 81, f);
    }

    fgets(buffer, 81, f);
    buffer[strlen(buffer) - 1] = '\0';

    for (i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == ' ')
        {
            printf("Wrong format file \n");
            exit(0);
        }
    }
    result[1] = atoi(buffer);
    return result;
}

void makeGraph(FILE *f, site mysite)
{
    char buffer[81];
    int i;
    int n, m;

    fgets(buffer, 81, f);
    buffer[strlen(buffer) - 1] = '\0';
    n = atoi(buffer);
    if (n == 0)
    {
        printf("Wrong format file\n");
        exit(0);
    }
    char name[50];
    int id;
    int from, to;
    for (i = 0; i < n; i++)
    {
        fscanf(f, "%s %d\n", name, &id);
        name[strlen(name)] = '\0';
        // printf("%s\n", name);
        // printf("%d\n", id);
        addVertex(mysite.graph, id, name);
    }

    fgets(buffer, 81, f);
    buffer[strlen(buffer) - 1] = '\0';
    m = atoi(buffer);
    //printf("m: %d\n", m);
    for (i = 0; i < m; i++)
    {
        fscanf(f, "%d %d", &from, &to);
        //printf("%d %d \n", from, to);
        insertEdge(mysite.graph, from, to, 1);
    }
}