#include "adjgraph.h"

int main()
{
	Graph g = createGraph();
	int i, num;
	char adjlist[100][MAX_LEN];

	addEdgeS(g, "s1", "s2");
	addEdgeS(g, "s1", "s3");
	addEdgeS(g, "s1", "s4");
	addEdgeS(g, "s2", "s1");
	addEdgeS(g, "s2", "s3");
	addEdgeS(g, "s2", "s4");
	addEdgeS(g, "s3", "s4");
	addEdgeS(g, "s2", "s1");
	addEdgeS(g, "s3", "s1");

	num = getAdjVerticesS(g, "s1", adjlist);

	printf("Adjacent list of s1 is:\n");
	for(i = 0; i < num; i++){
		printf("%-5s", adjlist[i]);
	}

	freeGraphS(g);

	return 0;

}