/**********************************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa5
*  List.h
*  Header file for List ADT
***********************************************************************************/
#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_

/***************************** Exported Types *************************************/
typedef struct List * ListRef; 
typedef struct Node * NodeRef;

/************** Constructors-Destructors ******************************************/

/*
*  newList
*  Returns ListRef pointing to new ListStruct which represents an empty List.
*  Initializes front and back fields to NULL, sets length field to 0.  Exported.
*/
ListRef newList(void);

/*
*  freeList
*  Frees all heap memory associated with the ListRef *pQ, including all memory
*  in existing Nodes.  Sets *pQ to NULL.  Exported.
*/
void freeList(ListRef* pL);

void freeNode(NodeRef* pN); 

/***************** Access functions ***********************************************/

/*
*  getLength
*  Returns the length of L
*/
int getLength(ListRef L);

/*
*  isEmpty
*  Returns True if L is empty, otherwise returns false
*/
int isEmpty(ListRef L);

int offEnd(ListRef L); 
int getIndex(ListRef L); 

/*
*  getFront
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getFront(ListRef L);

/*
*  getBack
*  Returns the value in the back of L.
*  Pre: !isEmpty(L)
*/
int getBack(ListRef L);

/*
*  getCurrent
*  Returns the current value at of L.
*  Pre: !isEmpty(L)
*/
int getCurrent(ListRef L);

/*
*  equals
*  returns true if A is identical to B, false otherwise
*/
int equals(ListRef A, ListRef B);  

/****************************** Manipulation procedures ***************************/

void makeEmpty(ListRef L); 
void moveTo(ListRef L, int i); 
void movePrev(ListRef L); 
void moveNext(ListRef L); 

/*
*  insertFront
*  Places new data element in front of L
*  Post: !isEmpty(L)
*/
void insertFront(ListRef L, int data);

/*
*  insertBack
*  Places new data element at the end of L
*  Post: !isEmpty(L)
*/
void insertBack(ListRef L, int data);

void insertBeforeCurrent(ListRef L, int data); 
void insertAfterCurrent(ListRef L, int data); 

/*
*  deleteFront
*  Deletes element at front of L
*  Pre: !isEmpty(L)
*/
void deleteFront(ListRef L);

/*
*  deleteBack         
*  Deletes element in back of L 
*  Pre: !isEmpty(L)
*/
void deleteBack(ListRef L);

/*
*  deleteCurrent         
*  Deletes current element of L 
*  Pre: !isEmpty(L)
*/
void deleteCurrent(ListRef L);

/*************** Other Functions *************************************************/

/*
*  printList
*  Prints data elements in L on a single line to stdout.
*/
void printList(FILE* out, ListRef L);

ListRef copyList(ListRef L);

#endif
