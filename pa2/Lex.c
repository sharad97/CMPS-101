//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Programming Assignment 2   //
//---------------------------//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    
    int count = 0;
    FILE *in, *out;
    char line[MAX_LEN];
    
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing 
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
    
    // counts the number of lines
    while( fgets(line, MAX_LEN, in) != NULL)  {
        count++;
    }
    
    //close file buffer and reopen
    fclose(in);
    in = fopen(argv[1], "r");
    
    char lines[count - 1][MAX_LEN];
    int lineNumber = -1;
    
    // fills the string array with the lines from input file
    while (fgets(line, MAX_LEN, in) != NULL) {
        strcpy(lines[++lineNumber], line);
    }
    
    // sorts a string array 
    List L = newList();
    append(L,0);
    int n;
    
    for (n = 1; n < count; n++) {
        char *c = lines[n];
        int i = n - 1;
        moveBack(L);
        while (i >= 0 && strcmp(c, lines[get(L)]) <= 0) {
            i--;
            movePrev(L);
        }
        if (index(L) >= 0) {
            insertAfter(L, n);
        } else {
            prepend(L, n);
        }
    }
    // Loop through the list and prints out sorted string array
    moveFront(L);
    while (index(L) >= 0) {
        fprintf(out, "%s", lines[get(L)]);
        moveNext(L);
    }

    // close files
    fclose(in);
    fclose(out);
    
    freeList(&L);
 
    return(0);
}