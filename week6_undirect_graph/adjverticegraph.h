#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"
#include "dllist.h"

#define ji(i) (new_jval_i(i))
#define RANGE 10000
#define MAX_LEN 500
#define pop(stack) (dequeue(stack))

typedef JRB Graph;

Graph createGraph(); // create an empty rb tree

int addEdge(Graph, Jval, Jval,
			int (*cmp)(Jval, Jval)); // add an edge to the graph

int adjacent(Graph, Jval, Jval,
				int (*cmp)(Jval, Jval)); // check if two vertices are adjacent

JRB getAdjVertices(Graph, Jval,
						int (*cmp)(Jval, Jval)); // get adjacent vertices


/******** end abstract definition **********************/


int cmpInt(Jval, Jval);  // function to compare two integers

int cmpStr(Jval, Jval); // function to compare two strings

Jval createJvalString(char*); // return a jval of string type

/********************
* API FOR STRING DATA
********************/
int addEdgeS(Graph, char*, char*);
int adjacentS(Graph, char*, char*);
int getAdjVerticesS(Graph, char*, char output[][MAX_LEN]);
void freeGraphS(Graph);

/********************
* API FOR INT DATA
********************/

// return the number
int getAdjVerticesI(Graph, int, int*);

// used for graph with int vertices
int addEdgeI(Graph, int, int);

// check if two verteces are adjacent, if so return true
int adjacentI(Graph, int, int);

// breath first search
void BFS(Graph, int, int (*visit)(int));

// depth first search
void DFS(Graph, int, int (*visit)(int));

int printI(int a);
