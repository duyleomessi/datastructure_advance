#include "libfdr/jrb.h"


typedef JRB Graph;

Graph createGraph();
void addEdge(Graph grath, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjanceVertices(Graph graph, int v, int *output);
void dropGraph(Graph graph);