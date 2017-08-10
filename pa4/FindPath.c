//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Patrick Tantalo            //
//Programming Assignment 4   //
//---------------------------//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
	
    // read input and write to output with fopen "r" and "w"
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if(in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    
    if(out == NULL){
        printf("Unable to open file %s for reading \n", argv[2]);
        exit(1);
    }
    
    char line[MAX_LEN];
    fgets(line, MAX_LEN, in);
    
    int V; 
    sscanf(line, "%d", &V);
    Graph G = newGraph(V);
	
	// fills graph
    int x, y;
    while(fgets(line, MAX_LEN, in) != NULL){
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0) break;
        addEdge(G, x, y);
    }
    
	// prints graph
    printGraph(out, G);
    
	// prints paths
	List L = newList();
    while(fgets(line, MAX_LEN, in) != NULL){
        int s, d;
        sscanf(line, "%d %d", &s, &d);
        if(s == 0 && d == 0) break;
        BFS(G, s);
        getPath(L, G, d);
        if (getDist(G, d) == -1){
            fprintf(out, "The distance from %d to %d is infinity \n", s, d);
            fprintf(out, "No %d-%d path exists\n", s, d);
        }else{
            fprintf(out, "The distance from %d to %d is %d \n", s, d, getDist(G, d));
            fprintf(out, "A shortest %d-%d path is: ", s, d);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
    }
	
	// free memory
    freeGraph(&G);
	freeList(&L);
    
	// close file
    fclose(in);
    fclose(out);
    
    return(0);	
}