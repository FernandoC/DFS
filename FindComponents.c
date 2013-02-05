/*************************************************************************
*  Author: Fernando Carrillo (fcarril1)
*  Assignment: pa5
*  Filename: FindComponents.c
*  Class: CMPS 101 Patrick Tantalo
*
*  Description: The FindComponents Program reads in a formatted file
*     and adds vertices to a Graph that uses and adjacency list.
*     FindComponents then calls Depth First Search on the graph and
*     finds all the strongly connected components in the graph.
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){

   int i, n=0, hitZero = 0, source, dest, SCC;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   GraphRef G, Trans;
   ListRef S = newList();

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
   }

   /* open files for reading and writing */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   /* Gets number of vertices in the file via the first line */
   fgets(line, MAX_LEN, in);
   token = strtok(line, " \n");
   n = atoi(&token[0]);

   G = newGraph(n);

   /* Iterates though and reads in ever vertice. */
   do{
      fgets(line, MAX_LEN, in);
      strcat(line, " ");
      token = strtok(line, " \n");
      tokenlist[0] = '\0';

      source = atoi(&token[0]);
      if (source >= 1000) dest = atoi(&token[5]);
      else if (source >= 100) dest = atoi(&token[4]);
      else if (source >= 10) dest = atoi(&token[3]);
      else dest = atoi(&token[2]); 
      hitZero = source + dest;

      if(hitZero != 0)addArc(G, source, dest);
      token = strtok(NULL, " \n");

   }while(hitZero != 0);

   /* Prints out the Adjacency List for Graph G */
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);

   /* Sees if Transpose works */
   Trans = transpose(G);  

   for(i = 1; i<= getOrder(G); i++){insertBack(S, i);}
   DFS(G, S);

   DFS(Trans, S);

   /* Finds how many SCC components there are in the graph */
   SCC = 0;
   for ( i = 1; i <= getOrder(G); i++){
       if( getParent(Trans, i) == NIL) SCC++;
   }
   fprintf(out, "\nG contains %d strongly connected components:\n", SCC);


   ListRef Comp = newList();
   /* Prints out the SCC components */
   for (i = 1; i<= SCC; i++){
       fprintf(out, "Component %d:", i);
       while(getParent(Trans, getBack(S)) != NIL){
           insertFront(Comp, getBack(S));
           deleteBack(S);
       }
       insertFront(Comp, getBack(S));
       deleteBack(S);
       printList(out, Comp);
       makeEmpty(Comp);
   }


   /* free memory */
   makeEmpty(S);
   freeList(&Comp);
   freeList(&S);
   freeGraph(&G);
   freeGraph(&Trans);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
