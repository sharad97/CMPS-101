//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Patrick Tantalo            //
//Programming Assignment 4   //
//---------------------------//


#include<stdio.h>
#include<stdlib.h>
#include "List.h"


//-----------------------------structs----------------------------------//


// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* previous;
}
NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorindex;
}
ListObj;


//------------------------Constructors-Destructors-------------------------//


// newNode()
// returns reference to new Node object. Initializes next and data fields.
// private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}

// freeNode()
// frees heap memory pointed to by *pN, sets *pN to NULL.
// private.
void freeNode(Node* pN) {
    if(pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// returns reference to new empty List object.
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorindex = -1;
    return(L);
}

// freeList()
// frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL) {
    if(pL != NULL && *pL != NULL) {
        while(length(*pL) > 0) {
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


//----------------------------Access functions-----------------------------//


// length()
// returns the number of elements in this list
int length(List L){
    if(L==NULL){
        printf("List Error: Length() called on NULL List reference\n");
        exit(1);
    }
    return(L->length);
}

// index()
// returns the index of the cursor element when cursor is defined returns -1 if cursor is not defined
int index(List L){
    if(L==NULL){
        printf("List Error: Index() called on NULL List reference\n");
        exit(1);
    }
    return(L->cursorindex);
}

// front()
// returns front element. Pre: length()>0
int front(List L){
    if(L==NULL){
        printf("List Error: Front() called on NULL List reference\n");
        exit(1);
    }else if(L->length <=0){
        printf("List Error: Front() called on an empty List\n");
        exit(1);
    }else{
        return(L->front->data);
    }
}

// back()
// returns back element. Pre: length()>0
int back(List L){
    if(L==NULL){
        printf("List Error: Back() called on NULL List reference\n");
        exit(1);
    }else if(L->length<=0){
        printf("List Error: Back() called on an empty List\n");
        exit(1);
    }else{
        return(L->back->data);
    }
}

// get()
// returns cursor element. Pre: length()>0, index()>=0
int get(List L){
    if(L==NULL){
        printf("List Error: Get() called on NULL List reference\n");
        exit(1);
    }else if(L->length <=0){
        printf("List Error: Get() called on an empty List\n");
        exit(1);
    }else if(L->length == 0){
        printf("List Error: Get() called on List reference with Undefined Index\n");
        exit(1);
    }else{
        return(L->cursor->data);
    }
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
    int eq = 1;
    Node N = A->front;
    Node M = B->front;
    if(A==NULL || B==NULL){
        printf("List Error: equals() called on NULL List reference\n");
        exit(1);
    }
    if (A->length != B->length){
        return 0;
    }
    while(eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


//---------------------------Manipulation procedures ------------------------//


// clear()
// resets this List to its original empty state.
void clear(List L){
    if(L==NULL){
        printf("List Error: calling clear() on NULL List reference");
        exit(1);
    }
    while(L->front!=NULL){
        deleteFront(L);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->cursorindex  = -1;
    L->length = 0;
}

// moveFront()
// if List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if(L==NULL){
        printf("List Error: moveFront() called on NULL List reference\n");
        exit(1);
    }else if(L->length > 0){
        L->cursorindex = 0;
        L->cursor = L->front;
    }
}

// moveBack()
// if List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if(L==NULL){
        printf("List Error: moveFront() called on NULL List reference\n");
        exit(1);
    }else if(L->length > 0){
        L->cursorindex = L->length - 1;
        L->cursor = L->back;
    }
}

// movePrev()
// if cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
    if (L == NULL){
        printf("List Error: movePrev() called on NULL List reference\n");
        exit (1);
    }else if(L->cursorindex < L->length && L->cursorindex >= 0){
        if(L->cursorindex != 0){ // If cursor not at front, moves cursor to previous node
            L->cursorindex--;
            L->cursor = L->cursor->previous;
        }else{
            L->cursorindex = -1;
            L->cursor = NULL;
        }
    }
}

// moveNext()
// if cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L){
    if (L == NULL){
        printf("List Error: moveNext() called on NULL List reference\n");
        exit (1);
    }else if(L->cursorindex < L->length && L->cursorindex >= 0){
        if(L->cursorindex != L->length -1){
            L->cursor = L->cursor->next;
            L->cursorindex++;
        }else{
            L->cursorindex = -1;
            L->cursor = NULL;
        }
    }
}

// prepend()
// insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: prepend() called on NULL List reference\n");
        exit(1);
    }else{
        Node N = newNode(data);
        if (L->front == NULL) {
            L->front = N;
            L->back = N;
        }
        else {
            L->front->previous = N;
            N->next = L->front;
            L->front = N;
            if (L->cursorindex >= 0) {
                L->cursorindex++;
            }
        }
        L->length++;
    }
}

// append()
// insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: prepend() called on NULL List reference\n");
        exit(1);
    }else{
        Node N = newNode(data);
        if (L->back == NULL) {
            L->front = N;
            L->back = N;
        }else{
            L->back->next = N;
            N->previous = L->back;
            L->back = N;
        }
        L->length++;
    }
}

// insertBefore()
// insert new element before cursor.
// pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if (L == NULL){
        printf("List Error: insertBefore() is called on NULL List reference\n");
        exit(1);
    }else{
        if (length(L) > 0 && L->cursorindex >= 0){
            if (L->cursor == L->front) {
                prepend(L, data);
            }else{
                Node N = newNode(data);
                N->previous = L->cursor->previous;
                N->next = L->cursor;
                L->cursor->previous->next = N;
                L->cursor->previous = N;
                L->cursorindex++;
                L->length++;
            }
        }else{
            printf("List Error: insertBefore() is called on List reference with Undefined Index\n");
            exit(1);
        }
    }
}

// inserAfter()
// inserts new element after cursor.
// pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: insertAfter() called on NULL List reference\n");
        exit(1);
    }else{
        if (length(L) > 0 && L->cursorindex >= 0) {
            if (L->cursor == L->back) {
                append(L, data);
            }else{
                Node N = newNode(data);
                N->next = L->cursor->next;
                N->previous = L->cursor;
                L->cursor->next->previous = N;
                L->cursor->next = N;
                L->length++;
            }
        }else{
            printf("List Error: insertAfter() is called on List reference with Undefined Index\n");
            exit(1);
        }
    }
}

// deleteFront()
// deletes the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL){
        printf("List Error: deleteFront() called on NULL List reference\n");
        exit (1);
    }else if(L->length <= 0){
        printf("List Error: deleteFront() called on empty List\n");
        exit (1);
    }else if(L->length == 1){
        Node N = L->front;
        L->front = NULL;
        freeNode(&N);
    }else{
        Node N = L->front;
        L->front = L->front->next;
        L->front->previous = NULL;
        freeNode(&N);
        L->length--;
        if (L->cursorindex == 0){ 
            L->cursor = NULL;
            L->cursorindex = -1;
        }else if(L->cursorindex != -1){
            L->cursorindex--;
        }
    }
}

// deleteBack()
// deletes the back element. Pre: length()>0
void deleteBack(List L){
    if (L == NULL){
        printf("List Error: deleteBack() called on NULL List reference\n");
        exit (1);
    }else if(L->length <=0 ){
        printf("List Error: deleteBack() called on empty List\n");
        exit (1);
    }else if(L->cursor == L->back){
        L->cursor = NULL;
        L->cursorindex = -1;
    }
    Node N = L->back;
    if(length(L) > 1){
        L->back = L->back->previous;
		L->back->next = NULL;
    }else{
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&N);
}

// delete()
// deletes cursor element, making cursor undefined.
// pre: length()>0, index()>=0
void delete(List L){
    if (L == NULL){
        printf("List Error: delete() called on NULL List reference\n");
        exit (1);
    }else if(L->length <= 0){
        printf("List Error: delete() called on empty List\n");
        exit (1);
    }else if(L->cursorindex < 0){
        printf("List Error: delete() called on list w/ undefined cursor\n");
        exit (1);
    }else if(L->cursor == L->back){
        deleteBack(L);
    }else if(L->cursor == L->front){
        deleteFront(L);
    }else{
        Node N = L->cursor;
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor = NULL;
        L->length--;
        freeNode(&N);
    }
    L->cursorindex = -1;
}


// Other Functions ------------------------------------------------------------


// printList()
// prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
	if(out==NULL){
        printf("List Error: printList() called on NULL List reference\n");
        exit(1);
    }else if(L==NULL){
        printf("List Error: printList() called on NULL Out File reference\n");
        exit(1);
    }
	Node N = L->front;
	while(N != NULL){
		fprintf(out,"%d ", N->data);
		N = N->next;
	}
}

// copyList()
// copies the contents of the list to a new list and returns it.
List copyList(List L){
    List listCopy = newList();
    Node N = L->front;
    while( N!=NULL ){
        append(listCopy, N->data);
        N = N->next;
    }
    return(listCopy);
}

// concatList()
// adds the contents of a and b to a new list and returns it.
List concatList(List A, List B){
    if(A == NULL || B == NULL){
        printf("List Error: calling concatList() on NULL List reference\n");
        exit(1);
    }else if(A->length < 1 || B->length < 1){
        printf("List Error: calling concatList() on empty List reference\n");
        exit(1);
    }
    List concat = copyList(A);
    Node N = B->front;
    while(N != NULL) {
        append(concat, N->data);
       N = N->next;
    }
    return concat;
}