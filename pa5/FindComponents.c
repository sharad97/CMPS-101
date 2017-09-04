//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Patrick Tantalo            //
//Programming Assignment 5   //
//---------------------------//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 160

// inner function of main.
void printScc(FILE* out, Graph G){
	// stack used by DFS.
	List L = newList();
	
	// list equal length of order of graph.
	for(int i=1; i<=getOrder(G); i++){
		append(L, i);
	}
	
	// Runs DFS on graph G and transpose.
	// creates transpose of origina graph.
	DFS(G, L);
	Graph T = transpose(G);
	DFS(T, L);
	
	// Finds number of strongly connected component in graph.
	int c1 = 0;	
	for(moveFront(L); index(L) >= 0; moveNext(L)){
		if(getParent(T, get(L)) == NIL){
			c1++;
		}
	}
	
	fprintf(out, "G contains %d strongly connected components:\n", c1);
	
	int c2 = 0;
	int c3 = c1+1;	
	List* cc = calloc(c3, sizeof(List));
	for(moveFront(L); index(L) >= 0; moveNext(L)){
		if(getParent(T, get(L)) == NIL){
			c2++;
			cc[c2] = newList();
		}
		append(cc[c2], get(L));
	}
	
	// prints component number and scc.
	for(int i = 1; i <= c1; i++){
		fprintf(out, "Component %d: ", i);
		printList(out, cc[(c3)-i]);
		fprintf(out, "\n");
	}
	
	// free memory.
	free(cc);
	freeList(&L);
	freeGraph(&T);
}

// main.
int main(int argc, char* argv[]){
	if( argc != 3 ){
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
		printf("Unable to open file %s for reading\n", argv[2]);
		exit(1);
	}
	
	char line[MAX_LEN]; 
	fgets(line, MAX_LEN, in);
	
	int numV = 0;	
	sscanf(line, "%d", &numV);
	Graph G = newGraph(numV);
	
	
	int x, y;
	while(fgets(line, MAX_LEN, in)){
		sscanf(line, "%d %d", &x, &y);
		if(x == 0 && y == 0){
			break;
		}
		addArc(G, x, y);
	}
	
	// prints adjacency list.
	// runs the printScc function.
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	printScc(out, G);
	
	// free memory.
	freeGraph(&G);
	
	// close files.
	fclose(in);
	fclose(out);
	
	return(0);
}