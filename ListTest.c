/********************************************************
*  Fernando Carrillo (fcarril1)
*  CMPS 101   pa5
*  Filename: ListTest.c
*  Description: A test client for the List ADT
********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
      int i;
      ListRef A = newList();
      ListRef B = newList();
      ListRef C = NULL;

      for(i = 1; i <= 10; i++){
         insertBack(A, i);
         insertBack(B, 11-i);
      }
      printf("A = ");
      printList(stdout, A);
      printf("\n"); 
      printf("B = ");
      printList(stdout, B );
      printf("\n");

      for(i = 1; i <= 6; i++){
         insertFront(A, getBack(B));
         deleteBack(B);
      }

      printf("A.insertFront() of last 6 elements of B  = ");
      printList(stdout, A);
      printf("\n");

      printf("deleteBack(B) * 6 = ");
      printList(stdout, B);
      printf("\n");

      C = copyList(A);
      printf("C = A.copy() = ");
      printList(stdout, C);
      printf("\n");

      printf("Does A = B? ");
      printf("%s\n", equals(A,B)?"true":"false");

      printf("Does A = C? "); 
      printf("%s\n", equals(A,C)?"true":"false");

      printf("getFront(A) = %d\n", getFront(A));
      printf("getBack(A) = %d\n", getBack(A));

      moveTo(A, 5);
      printf("moveTo(A, 5)+ getCurrent(A) = %d\n", getCurrent(A));
      
      insertBeforeCurrent(A, 9);
      printf("insertBeforeCurrent(A, 9) = ");
      printList(stdout, A);
      printf("\n");
      
      insertAfterCurrent(A, 7);
      printf("insertAfterCurrent(A, 7) = ");
      printList(stdout, A);
      printf("\n");

      printf("getIndex(A) = %d\n", getIndex(A));

      movePrev(A);
      printf("movePrev(A) + getIndex(A) = %d\n", getIndex(A));

      deleteCurrent(A);
      printf("deleteCurrent(A) = ");
      printList(stdout, A);
      printf("\n");

      deleteFront(A);
      printf("deleteFront(A)  = ");
      printList(stdout, A);
      printf("\n");
 
      return(0);

}

