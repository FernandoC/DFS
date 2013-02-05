/*********************************************************************
* Fernando Carrillo (fcarril1)
* CMPS 101 Pa5 
* Filename GraphTest.c
* Description: A program to test the functionality of the Graph ADT 
**********************************************************************/
  
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
    if( argc != 2 ){
        printf("Usage: %s output\n", argv[0]);
        exit(1);
    }

    FILE *out;
    out = fopen(argv[1], "w");

    GraphRef G = newGraph(10);
    GraphRef T;
    ListRef S = newList();
    int i;
    for( i = 1; i<= 9; i++){
        addArc(G, i, i+1);
    }

    addArc(G, 1, 2);

    for(i = 1; i<= getOrder(G); i++){insertBack(S, i);}

    fprintf(out, "\nThe adjacency list of G is:\n");

    printGraph(out, G);
    DFS(G, S); 

    T = transpose(G);
    fprintf(out, "\nTranspose of G is:\n");
    printGraph(out, T);

    fprintf(out, "Order of G is %d\n", getOrder(G));

    fprintf(out, "Size of G is %d.\n", getSize(G));

    fprintf(out, "Parent of 10 is %d.\n", getParent(G, 10));

    fprintf(out, "Parent of 3 is %d.\n", getParent(G, 3));

    fprintf(out, "Discover time of 1 is %d.\n",getDiscover(G, 1));
    fprintf(out, "Finish time of 1 is %d.\n", getFinish(G, 1));

    fprintf(out, "Discover time of 9 is %d.\n",getDiscover(G, 9));
    fprintf(out, "Finish time of 9 is %d.\n", getFinish(G, 9));

    fclose(out);
    return(0);
}
