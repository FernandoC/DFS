/**********************************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa5
*  Graph.c
*  Implementation file for Graph ADT
***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

/********************** Private Structs: not exported ***************************/

typedef struct Graph{
   ListRef * adjacency;
   char * color;
   int * discover;
   int * finish;
   int * parent;
   int order;
   int time;
   int size;
}Graph;

/************************ Constructors-Destructors ******************************/
GraphRef newGraph(int n){
    int i;
    GraphRef G = malloc(sizeof(Graph));
    G->adjacency = calloc(n+1, sizeof(ListRef));
    G->color = calloc(n+1, sizeof(char));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));    
    for ( i = 1; i<= n ; i++){
        G->adjacency[i] = newList();
        G->color[i] = 'w';
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        G->parent[i] = NIL;
    }
    G->order = n;
    G->time = UNDEF;
    G->size = 0;
    return G;
}

void freeGraph(GraphRef* pG){
    if (pG==NULL || *pG==NULL) return;
    int i, n = getOrder(*pG);
    for (i = 1;i <= n; i++){
       freeList(&(*pG)->adjacency[i]);
    }
    free((*pG)->adjacency);
    free((*pG)->color);
    free((*pG)->discover);
    free((*pG)->finish);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
}

/*************************** Access functions ***********************************/ 
int getOrder(GraphRef G){
    return G->order;
}
int getSize(GraphRef G){
    return G->size;
} 

int getParent(GraphRef G, int u){
    if (u < 1 || u > getOrder(G)){
        printf("Called getParent on out of bound u\n");
        exit(1);
    }
    else return G->parent[u];
}

int getDiscover(GraphRef G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getDistance on out of bound u\n");
         exit(1);
     }
     else return G->discover[u];
}

int getFinish(GraphRef G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getFinish on out of bound u\n");
         exit(1);
     }
     else return G->finish[u];
}

/************************** Manipulation procedures *******************************/ 

void addArc(GraphRef G, int u, int v){
    ListRef row = G->adjacency[u];

    /* Inserts vetex v into row u in the adjacency array */
    if (isEmpty(row)){
        insertFront(row, v);
        G->size++;
        return;
    }
    else{
        moveTo(row, 0);
        while (!offEnd(row)){
            if (v == getCurrent(row)) return;
            if (v > getCurrent(row)){
                moveNext(row);
            }else{
                insertBeforeCurrent(row, v);
                G->size++;
                return;
            }
        }
        insertBack(row, v);
        G->size++;
    }

}

void visit(GraphRef G, ListRef S, int u){
    int v;
    G->color[u] = 'g';
    G->time++;
    G->discover[u] = G->time;
    moveTo(G->adjacency[u], 0);
    while (!offEnd(G->adjacency[u]) ){
        v = getCurrent(G->adjacency[u]);
        if(G->color[v] == 'w'){
            G->parent[v] = u;
            visit(G, S, v);
        }
        moveNext(G->adjacency[u]);
    }
    G->color[u] = 'b';
    G->time++;
    G->finish[u] = G->time;
    insertFront(S, u);
}

void DFS(GraphRef G, ListRef S){
    if (getLength(S) != getOrder(G)){
        printf("Called DFS on a Graph whose order != the Stack size\n");
        exit(1);
    }
    ListRef Stack = copyList(S);
    makeEmpty(S);
    int u;
    for(u = 1; u <= getOrder(G); u++){
        G->color[u] = 'w';
        G->parent[u] = NIL;
    }
    G->time = 0;
    moveTo(Stack, 0);
    while(!offEnd(Stack)){ 
        u = getCurrent(Stack);
        if (G->color[u] == 'w') visit(G, S, u);
        moveNext(Stack);
    }
    freeList(&Stack);
}


/***************************** Other operations *******************************/ 

GraphRef transpose(GraphRef G){
    int source, dest;
    GraphRef trans = newGraph(getOrder(G));
    for (source = 1; source <= getOrder(G); source++){
        moveTo(G->adjacency[source], 0);
        while(!offEnd(G->adjacency[source])){
            dest = getCurrent(G->adjacency[source]);
            addArc(trans, dest, source);
            moveNext(G->adjacency[source]);
        }
    }
    return trans;
}

GraphRef copyGraph(GraphRef G){
    int i;
    GraphRef tmp = newGraph(getOrder(G));
    for (i = 1; i <= getOrder(G); i++){
        tmp->adjacency[i] = copyList(G->adjacency[i]);
    }
    return tmp;
}

void printGraph(FILE* out, GraphRef G){
    int i;
    for(i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d:", i);
        printList(out, G->adjacency[i]); 
    }
}
