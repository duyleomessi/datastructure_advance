#include "adjgraph.h"


Graph createGraph()
{
	return make_jrb();
}


int insertEdge(Graph g, Jval v1, Jval v2,
				int (*cmp)(Jval, Jval))
{
	Graph found;
	Jval j_adj_list;
	Jval j = new_jval_v(NULL);
	found = jrb_find_gen(g, v1, cmp);

	if(found == NULL){
		/* if not found
		 create a new adjacent list which v2 is added to
		 then insert the adjacent list to the tree
		 with the key is v1
		*/

		 // create a new adj_list
		JRB adj_list = make_jrb();
		jrb_insert_gen(adj_list, v2, j, cmp);
		j_adj_list = new_jval_v(adj_list);

		// add adjacent list to the tree
		jrb_insert_gen(g, v1, j_adj_list, cmp);

		return 0;

	}else{
		/*
		if found
		check if v2 is in the adj_list of v1
				if not, add v2 to adj_list of v1
				else return status code 1
		*/

		JRB adj_list = (JRB) jval_v(found->val);
		found = jrb_find_gen(adj_list, v2, cmp);
		if(found == NULL){
			jrb_insert_gen(adj_list, v2, j, cmp);
			return 0;
		}else return 1;
	}
}


int addEdge(Graph g, Jval v1, Jval v2,
			int (*cmp)(Jval, Jval))
{
	/* find key v1 in graph
	if found, add v2 to the adjacent list of v1
	if not, create key v1 and add v2 to v1
	similar to v2
	*/
	int error_code1 = 0; // returned if error_code != 0
	int error_code2 = 0;

	error_code1 = insertEdge(g, v1, v2, cmp);
	error_code2 = insertEdge(g, v2, v1, cmp);
	
	return error_code1 + error_code2;

}


int adjacent(Graph g, Jval v1, Jval v2,
				int (*cmp)(Jval, Jval))
{
	JRB found = jrb_find_gen(g, v1, cmp);

	if(found == NULL){
		return 0;
	}else{
		found = jrb_find_gen((JRB) jval_v(found->val), v2, cmp);
		if(found == NULL) return 0;
		else return 1;
	}

}


JRB getAdjVertices(Graph g, Jval v1,
							int (*cmp)(Jval, Jval))
{
	JRB tmp, found;
	found = jrb_find_gen(g, v1, cmp);

	if(found == NULL) return NULL;
	else return (JRB) jval_v(found->val);
}


int cmpInt(Jval a, Jval b)
{
	return jval_i(a) - jval_i(b);
}


int cmpStr(Jval s1, Jval s2)
{
	return strcmp(jval_s(s1), jval_s(s2));
}



/**************************************************
* STRING API
**************************************************/

Jval createJvalString(char *s)
{
	char* allocated_s = (char *) malloc(sizeof(char)*strlen(s));
	strcpy(allocated_s, s);
	Jval val = new_jval_s(allocated_s);

	return val;
}


int addEdgeS(Graph g, char* v1, char* v2)
{

	Jval jval_v1 = createJvalString(v1);
	Jval jval_v2 = createJvalString(v2);

	int result = addEdge(g, jval_v1, jval_v2, &cmpStr);

	return result;
}


int adjacentS(Graph g, char* v1, char* v2)
{
	Jval jval_v1 = createJvalString(v1);
	Jval jval_v2 = createJvalString(v2);

	int result = adjacent(g, jval_v1, jval_v2, &cmpStr);

	//free memory
	free(jval_s(jval_v1));
	free(jval_s(jval_v2));

	return result;
}


int getAdjVerticesS(Graph g, char* key, char output[][MAX_LEN])
{
	Jval jval_key = createJvalString(key);
	JRB root = getAdjVertices(g, jval_key, &cmpStr);
	JRB tmp;
	int len = 0;

	if(root == NULL){
		printf("ERROR: node %s does not exist\n", key);
	}else{
		jrb_traverse(tmp, root){
			strcpy(output[len], jval_s(tmp->key));
			len++;
		}
	}
	
	free(jval_key.s);

	return len;
}


void freeGraphS(Graph g)
{
	//JRB adj_list_root;
	JRB graph_node;
	//JRB adj_node;

	jrb_traverse(graph_node, g){
		//if(strcmp(jval_s(graph_node->val), ""))
			free(jval_s(graph_node->key));
		//if(strcmp(jval_s(graph_node->key), ""))
			free(jval_s(graph_node->val));
	}
}

/**************************************************
* INT API
**************************************************/

int getAdjVerticesI(Graph g, int v, int* output)
{
	// find note v
    JRB found = jrb_find_gen(g, ji(v), &cmpInt);
	JRB adj_list;
	JRB tmp;
	int count = 0;

	if(found == NULL){
		printf("ERROR: Node %d does not exist\n", v);
		return 0;
	}else{
		adj_list = (JRB) jval_v(found->val);
		jrb_traverse(tmp, adj_list){
			output[count] = jval_i(tmp->key);
			count++;
		}
		return count;
	}
}


int addEdgeI(Graph g, int v1, int v2)
{
	return addEdge(g, ji(v1), ji(v2), &cmpInt);
}


int adjacentI(Graph g, int v1, int v2)
{
	return adjacent(g, ji(v1), ji(v2), &cmpInt);
}


Jval dequeue(Dllist queue)
{
  Jval fnode = dll_first(queue)->val;
  dll_delete_node(dll_first(queue));
  return fnode;
}


int printI(int a)
{
  printf("%-4d", a);
  return 0;
}


void BFS(Graph g, int start, int (*visit)(int))
{
  //Dllist as queue
  Dllist queue;
  int adj[RANGE];
  int num_adj, i;
  //mark all vertices as unvisited
  int visited[RANGE] = {0};
  
  //visit the first vertex
  (*visit)(start);
  visited[start] = 1;

  //initialize the queue
  queue = new_dllist();
  dll_append(queue, ji(start));

  while(!dll_empty(queue)){
    int u = jval_i(dequeue(queue));
    num_adj = getAdjVerticesI(g, u, adj);

    for(i = 0; i < num_adj; i++){
      if(!visited[adj[i]]){
		(*visit)(adj[i]);
		visited[adj[i]] = 1;
		dll_append(queue, ji(adj[i]));
      } //end if
    } // end for

  }// end while
}//end function


void DFS(Graph g, int s, int (*visit)(int))
{
	Dllist stack = new_dllist();
	int adj[RANGE];
  	int num_adj, i;
  	//mark all vertices as unvisited
  	int visited[RANGE] = {0};

  	(*visit)(s);
  	visited[s] = 1;

  	// put s into the stack
  	dll_prepend(stack, ji(s));

  	while(!dll_empty(stack)){
  		int u = jval_i(pop(stack));
  		num_adj = getAdjVerticesI(g, u, adj);

  		for(i = 0; i < num_adj; i++){
  			if(!visited[adj[i]]){
  				(*visit)(adj[i]);
  				visited[adj[i]] = 1;
  				dll_prepend(stack, ji(adj[i]));
  			}//end if
  		}//end for
  		
  	}//end while

}