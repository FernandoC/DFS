/**********************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa5
*  Graph.h
*  Header file for Graph ADT
**********************************************************************/
#include "List.h"
#if !defined(_GRAPH_H_INCLUDE)
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0

/*** Exported Types *********************/

typedef struct Graph * GraphRef;

/* Constructors-Destructors */ 
GraphRef newGraph(int n); 
void freeGraph(GraphRef* pG);
 
/* Access functions */ 
int getOrder(GraphRef G); 
int getSize(GraphRef G); 
int getParent(GraphRef G, int u); 
int getDiscover(GraphRef G, int u);
int getFinish(GraphRef G, int u);

/* Manipulation procedures */ 
void addArc(GraphRef G, int u, int v);
void DFS(GraphRef G, ListRef S);
 
/* Other Functions */ 
GraphRef transpose(GraphRef G); 
GraphRef copyGraph(GraphRef G); 
void printGraph(FILE* out , GraphRef G); 
#endif
