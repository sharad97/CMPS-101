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
    
    int numV; 
    sscanf(line, "%d", &numV);
    Graph G = newGraph(numV);
	
	// fills graph
    int x, y;
    while(fgets(line, MAX_LEN, in) != NULL){
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0){
			break;
		}else{
			addEdge(G, x, y);
		}
    }
    
	// prints graph
    printGraph(out, G);
    
	// prints paths
	List L = newList();
    while(fgets(line, MAX_LEN, in) != NULL){
        int sc, dc;
        sscanf(line, "%d %d", &sc, &dc);
        if(sc == 0 && dc == 0){
			break;
		}else{
			BFS(G, sc);
			getPath(L, G, dc);
			if(getDist(G, dc) != -1){
				fprintf(out, "The distance from %d to %d is %d \n", sc, dc, getDist(G, dc));
				fprintf(out, "A shortest %d-%d path is: ", sc, dc);
				printList(out, L);
				fprintf(out, "\n");
			}else{
				fprintf(out, "The distance from %d to %d is infinity \n", sc, dc);
				fprintf(out, "No %d-%d path exists \n", sc, dc);
			}
			clear(L);
		}
    }

	
	// free memory
    freeGraph(&G);
	freeList(&L);
    
	// close file
    fclose(in);
    fclose(out);
    
    return(0);	
}