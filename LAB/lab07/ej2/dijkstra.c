#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"

cost_t *dijkstra(graph_t graph, vertex_t init) {
    unsigned int maxi_vertex = graph_max_vertexs(graph);

    set C = set_empty();
    for(vertex_t i = 0; i < maxi_vertex; i++){
        if(i != init){
            C = set_add(C,i);
        }
    }

    cost_t *D = calloc(maxi_vertex,sizeof(cost_t));
    for(vertex_t i = 0; i < maxi_vertex; i++){
        D[i] = graph_get_cost(graph,init,i);
    }

    while(!set_is_empty(C)){
        vertex_t c = set_get(C);
        for(vertex_t i = 0; i < maxi_vertex; i++){
            if(set_member(i,C) && cost_lt(D[i],D[c])){
                c = i;
            }
        }

        C = set_elim(C,c);
        for(vertex_t i = 0; i < maxi_vertex; i++){
            if(set_member(i,C) && cost_lt(cost_sum(D[c],graph_get_cost(graph,c,i)),D[i])){
                D[i] = cost_sum(D[c],graph_get_cost(graph,c,i));
            }
        }
    }


    C = set_destroy(C);
    return D;
}
