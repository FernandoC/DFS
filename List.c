/**********************************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa5
*  List.c
*  Implementation file for List ADT
***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

/************** Private Structs: not exported *************************************/

typedef struct Node{
   int data;
   struct Node* next;
   struct Node* prev;
} Node;

typedef struct List{
   NodeRef front;
   NodeRef back;
   NodeRef current;
   int length;
} List;


/************** Constructors-Destructors ******************************************/

/*
*  newList
*  Returns pointer to new Node struct. Initializes next field to NULL, and sets
*  data field to input parameter node_data. Private.
*/
ListRef newList(void){
   ListRef L = malloc(sizeof(List));
   L->front = L->back = L->current = NULL;
   L->length = 0;
   return(L);
}

/*
*  freeList
*  Frees all heap memory associated with the ListRef *pL, including all memory
*  in existing Nodes.  Sets *pL to NULL.  Exported.
*/
void freeList(ListRef* pL){
   if(pL==NULL || *pL==NULL) { return; }
   while( !isEmpty(*pL) ) { deleteBack(*pL); }
   free(*pL);
   *pL = NULL;
}

/*
*  newNode
*  Returns pointer to new Node struct. Initializes next field to NULL, and sets
*  data field to input parameter node_data. Private.
*/
NodeRef newNode(int data){
   NodeRef N = malloc(sizeof(Node));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

/*
*  freeNode
*  Frees heap memory pointed to by pN. Private.
*/
void freeNode(NodeRef* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


/***************** Access functions ***********************************************/

/*
*  getLength
*  Returns the length of L
*/
int getLength(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getLength() on NULL ListRef\n");
      exit(1);
   }
   return(L->length);
}
   
/*
*  isEmpty 
*  Returns True if L is empty, otherwise returns 0
*/
int isEmpty(ListRef L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL ListRef\n");
      exit(1);
   }
   return(L->length==0);
}

/*
* offEnd
* Returns True if current is NULL, otherwise returns 0
*/
int offEnd(ListRef L){
    if (L == NULL){
        printf("List Error calling offEnd() on NULL ListRef\n");
        exit(1);
    }
    return(L->current==NULL);
}

/*
* getIndex
* Returns position of current index in respect to the List
*/
int getIndex(ListRef L){
    if (L->current == NULL){ return -1;}
    int index = 1;
    Node* N = NULL;
    for (N = L->front; N != L->current ; N = N->next){
        index ++;
    } 
    return index;
}

/*
*  getFront
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getFront(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL ListRef\n");
      exit(1);
   }
   return(L->front->data);
}

/*
*  getBack
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getBack(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getBack() on NULL ListRef\n");  
      exit(1);
   }
   return(L->back->data);
}

/*   
*  getCurrent
*  Returns the current value of L.
*  Pre: !isEmpty(L)
*/
int getCurrent(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getCurrent() on NULL ListRef\n");
      exit(1);
   }
   return(L->current->data); 
}

/*
*  equals
*  returns 1 if A is identical to B, 0 otherwise
*/
int equals(ListRef A, ListRef B){
   int flag = 1;  
   Node* N = NULL;
   Node* M = NULL;  
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL ListRef\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}

/**************** Manipulation procedures ****************************************/

/*
*  makeEmpty
*  Sets List to the empty state.
*  Post: isEmpty();
*/
void makeEmpty(ListRef L){
   if(!isEmpty(L)){
      while( !isEmpty(L)){ deleteBack(L); }
   }
} 

/* 
*  moveTo
*  If 0 <= i <= getLength()-1, moves current element marker to 
*  position i in this List. Otherwise current is undefined.
*/
void moveTo(ListRef L, int i){
   int j;
   L->current = L->front;
   for (j = 0; j < i; j++){
      moveNext(L);
   }
} 

/* 
*  movePrev
*  Moves current one step toward the front element
*  Pre: !isEmpty(), !offEnd().
*/
void movePrev(ListRef L){
   if (isEmpty(L)){printf("List Error: calling movePrev() on NULL ListRef\n");}
   else if (offEnd(L)){printf("List Error: calling movePrev() on offEnd ListRef\n");}
   else{ L->current = L->current->prev;}
}

/* 
*  moveNext
*  Moves current one step toward the end of the list
*  Pre: !isEmpty(), !offEnd().
*/
void moveNext(ListRef L){
   if (isEmpty(L)){printf("List Error: calling moveNext() on NULL ListRef\n");}
   else if (offEnd(L)){printf("List Error: calling moveNext() on offEnd ListRef\n");}
   else{ L->current = L->current->next;}
}

/*
* insertFront
* Places new data element in the front of L
* Post: !isEmpty(L)
*/
void insertFront(ListRef L, int data){
   NodeRef N = newNode(data);
   if( L == NULL){
      printf("List Error: calling insertFront() on NULL ListRef\n");
      exit(1); 
   }
   if ( isEmpty(L) ) {L->front = L->back = N; }
   else { N->next = L->front; L->front->prev = N; L->front = N; }
   L->length++;
}

/*
*  insertBack
*  Places new data element at the end of L
*  Post: !isEmpty(L)
*/
void insertBack(ListRef L, int data){
   NodeRef N = newNode(data);
   if( L==NULL ){
       printf("List Error: calling insertBack() on NULL ListRef\n");
       exit(1);
   }
   if( isEmpty(L) ) { L->front = L->back = N; }
   else { L->back->next = N; N->prev = L->back; L->back = N; }
   L->length++;
}

/*
*  insertBeforeCurrent
*  Inserts new element before current element on the List
*  Pre: !isEmpty(L) !offEnd(L)
*/
void insertBeforeCurrent(ListRef L, int data){
   if ( !isEmpty(L) && !offEnd(L) ){
      if (getIndex(L) == 1){
         insertFront(L, data);
         return;
      }
      else{
         NodeRef N = newNode(data);
         L->current->prev->next = N;
         N->prev = L->current->prev;
         N->next = L->current;
         L->current->prev = N;
      }
      L->length++;
   }
} 


/*
*  insertAfterCurrent
*  Inserts new element after current element on the List
*  Pre: !isEmpty(L) !offEnd(L)
*/

void insertAfterCurrent(ListRef L, int data){
 if ( !isEmpty(L) && !offEnd(L) ){
      if (getIndex(L) == getLength(L)){
         insertBack(L, data);
         return;
      }
      else{
         NodeRef N = newNode(data);
         L->current->next->prev = N;
         N->next = L->current->next;
         L->current->next = N;
         N->prev = L->current;
      }
      L->length++;
   }
}


/*
*  deleteFront
*  Deletes element in the Front of L
*  Pre: !isEmpty(L)
*/
void deleteFront(ListRef L){
   NodeRef N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFont() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->front;
   if( getLength(L)>1 ) { L->front = L->front->next; L->front->prev = NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
}
  


/*
*  deleteBack
*  Deletes element in the back of L
*  Pre: !isEmpty(L)
*/
void deleteBack(ListRef L){
   NodeRef N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( getLength(L)>1 ) { L->back = L->back->prev; L->back->next = NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
}

/*
*  deleteCurrent
*  Deletes current element in L
*  Pre: !isEmpty(L)
*/
void deleteCurrent(ListRef L){
   NodeRef N = NULL;
    
   if( L==NULL ){
      printf("List Error: calling deleteCurrent() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteCurrent on an empty List\n");
      exit(1);
   }
   N = L->current;
   if( getLength(L)>1 ) { 
       L->current->prev = L->current->next;
       L->current->next->prev = L->current->prev;
       L->current->next = L->current->prev = NULL;
   }
   else { L->front = L->back = L->current = NULL; }
   L->length--;
   freeNode(&N);   
} 


/*************** Other Functions *************************************************/

/*
*  printList
*  Prints data elements in L on a single line to stdout.
*/
void printList(FILE* out, ListRef L){
   Node* N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL ListRef\n");
      exit(1);
   }
   if(isEmpty(L)) fprintf(out, "\n");
   for(N = L->front; N != NULL; N = N->next){
      if(N->next == NULL){fprintf(out, " %d\n", N->data);}
      else if (N->prev == NULL){fprintf(out, " %d", N->data);}
      else {fprintf(out, " %d", N->data);}
   }
}

/*
*  copyList
*  Returns a new List Identical to the one passed in. 
*/
ListRef copyList(ListRef L){
   ListRef copy = newList();
   NodeRef temp = L->front;

   while( temp!=NULL){
      insertBack(copy , temp->data);
      temp = temp->next;
   }
   return copy;
}



