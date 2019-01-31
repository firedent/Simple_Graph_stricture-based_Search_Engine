//
// Created by 张世超 on 2019-01-29.
//

#include "graph.h"

typedef struct GraphRep{
    VNode *vertexes;
    int nV;
} GraphRep;
//init vertex
void initVNode(VNode *, char *);

// init graph without edge
Graph initGraph(char **nodes_name, int nV){
    Graph g = (GraphRep *)malloc(sizeof(GraphRep));
    g->nV = nV;
    g->vertexes = (VNode *)malloc(sizeof(VNode)*nV);
    double init_rank = 1/(double)nV;
    for(int i = 0; i<nV; i++){
        initVNode(&g->vertexes[i], nodes_name[i]);
        g->vertexes[i].rank = init_rank;
    }
    return g;
}

void initVNode(VNode *vertex, char *name){
    vertex->url_name = name;
    vertex->first = NULL;
    vertex->inDegree = 0;
    vertex->outDegree = 0;
    vertex->rank = 0;
}

ArcNode* newArcNode(int adjvex){
    ArcNode *newArcNode = (ArcNode *)malloc(sizeof(ArcNode));
    newArcNode->adjvex = adjvex;
    return newArcNode;
}

VNode* getVNode(Graph g, int index){
    return &g->vertexes[index];
}

int searchVNode(Graph g, char *name){
    int i = 0;
    while(i<g->nV){
        if(strcmp(getVNode(g,i)->url_name, name) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

int existEdge(Graph g, char *sourceName, int destinationId){
    VNode *VNode = getVNode(g, destinationId);
    ArcNode *Edges = VNode->first;
    while(Edges != NULL){
        if(strcmp(getVNode(g, Edges->adjvex)->url_name,sourceName) == 0){
            return 1;
        }
        Edges = Edges->next;
    }
    return 0;
}
void addEdge(Graph g, char *destinationName, int sourceId){
    VNode *S_VNode = getVNode(g, sourceId);
    int destinationId = searchVNode(g, destinationName);
    VNode *D_VNode = getVNode(g, destinationId);
//    if(existEdge(g, sourceName, destinationId) != 1){
//        newArcNode(destinationId)->next = VNode->first;
//        VNode->first = newArcNode(destinationId);
//        VNode->inDegree++;
//    }
    ArcNode *ArcNode = newArcNode(sourceId);
    ArcNode->next = D_VNode->first;
    D_VNode->first = ArcNode;
    D_VNode->inDegree += 1;
    S_VNode->outDegree += 1;
}

int getVertexNum(Graph g){
    return g->nV;
}

void freeGraph(Graph g){
    if (g == NULL) return;
    for(int i = 0; i<g->nV;i++){
        ArcNode *nextFree = g->vertexes[i].first;
        while (nextFree != NULL){
            free(nextFree);
            nextFree = nextFree->next;
        }
    }
    free(g->vertexes);
    free(g);
}