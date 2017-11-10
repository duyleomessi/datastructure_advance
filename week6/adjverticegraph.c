#include "adjverticegraph.h"

Graph createGraph() {
    return make_jrb;
}

void addEdge(Graph grath, Jval v1, Jval v2, int (*cmp) (Jval, Jval)) {
    JRB tmp = jrb_find_gen(graph, v1, cmp);

    if(tmp == NULL) {
        grap = jrb_insert_gen(graph, v1, v2, cmp);
    }

}