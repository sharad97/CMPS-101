//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Patrick Tantalo            //
//Programming Assignment 5   //
//---------------------------//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


//----------------------------Exported type-------------------------------//

// private GraphObj type
// creats graph struct
typedef struct GraphObj{
    List *adj;
    int *color;
    int *discover;
	int *finish;
	int *parent;
    int order;
    int size;
	int time;
}GraphObj;


//--------------------------Constructors-Destructors-----------------------//

// newGraph()
// returns a Graph reference to new empty Graph object.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    for(int i=1; i<=n; i++){
        G->color[i] = 0; // white
        G->discover[i] = INF;
		G->finish[i] = INF;
		G->parent[i] = NIL;
        G->adj[i] = newList();
    }
    return G;
}

// freeGraph()
// frees all dynamic heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
    for(int i=1; i<=(*pG)->order; i++){
        freeList(&(*pG)->adj[i]);
    }
    if(pG != NULL && *pG !=NULL){
        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->parent);
		free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}


//---------------------------------Access functions------------------------//

// getOrder()
// returns order.
int getOrder(Graph G){
    if(G == NULL) {
        printf("Graph Error: getOrder() called on NULL Graph reference\n");
        exit(1);
    }else{
        return (G->order);
    }
}

// getSize()
// returns size.
int getSize(Graph G){
    if(G == NULL) {
        printf("Graph Error: getSize() called on NULL Graph reference\n");
        exit(1);
    }else{
        return (G->size);
    }
}

// getParent()
// returns parent of the vertex u in BFS.
int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: getParent() called on NULL Graph reference\n");
        exit(1);
    } else if(u<1 || u>getOrder(G)){
        printf("Graph Error: getParent() called without of bounds value'u'\n");
        exit(1);
    }else{
        return (G->parent[u]);
    }
}

// getDiscover()
// returns Discover time of u.
int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: getDiscover() called on NULL Graph reference\n");
        exit(1);
    } else if(u<1 || u>getOrder(G)){
        printf("Graph Error: getDiscover() called without of bounds value 'u'\n");
        exit(1);
    }else{
        return (G->discover[u]);	
    }
}


// getFinish()
// returns finish time of u.
int getFinish(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: getFinish() called on NULL Graph reference\n");
        exit(1);
    } else if(u<1 || u>getOrder(G)){
        printf("Graph Error: getFinish() called without of bounds value 'u'\n");
        exit(1);
    }else{
        return (G->finish[u]);	
    }
}



//---------------------------Manipulation procedures-----------------------//


// addEdge()
// inserts new edge to graph G joining u to v and v to u.
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph Error: addEdge() called on NULL Graph reference\n");
        exit(1);
    }else if(u<1 || u>getOrder(G)){
        printf("Graph Error: addEdge() called without of bounds value 'u'\n");
        exit(1);
    }else if(v<1 || v>getOrder(G)){
        printf("Graph Error: addEdge() called without of bounds value 'v'\n");
        exit(1);
    }else{
        addArc(G, u, v);
        addArc(G, v, u);
    }
    G->size--;
}

// addArc()
// inserts directed edge to graph G from u to v
void addArc(Graph G, int u, int v){
    int x;
    List L = G->adj[u];
    if(G == NULL){
        printf("Graph Error: addArc() called on NULL Graph reference\n");
        exit(1);
    }else if(u<1 || u>getOrder(G)){
        printf("Graph Error: addArc() called without of bounds value 'u'\n");
        exit(1);
    }else if(v<1 || v>getOrder(G)){
        printf("Graph Error: addArc() called without of bounds value 'v'\n");
        exit(1);
    }else if(length(L) == 0){
        append(L, v);
    }else{
       for(moveFront(L); index(L) >= 0; moveNext(L)){
            x = get(L);
            if(v < x){
                insertBefore(L, v);
				return;
            }
		}
		append(L, v);	
    }
	G->size++;
}


// visit()
// inner function for DFS()
void visit(Graph G, List S, int x){
	G->color[x] = 1; // gray 
	G->discover[x] = ++G->time;
	List L = G->adj[x];
	if(G == NULL){
        printf("Graph Error: Visit() called on NULL Graph reference\n");
        exit(1);
	}else if(S == NULL){
		printf("Graph Error: Visit() called with Null List reference\n");
		exit (1);
	}else if(length(L)!=0){
		for(moveFront(L); index(L) >= 0; moveNext(L)){
			int y = get(L);
			if(G->color[y] == 0){ //white
				G->parent[y] = x;
				visit(G, S, y);
			}
		}
	}
	G->color[x] = 2; // black
	G->finish[x] = ++G->time;
	prepend(S, x);
}


// DFS()
// runs DFS algorithm on graph G.
// Discovers strongly connected components.
void DFS(Graph G, List S){
	if(G == NULL){
        printf("Graph Error: DFS() called on NULL Graph reference\n");
        exit(1);
	}else if(S == NULL){
		printf("Graph Error: DFS() called with Null List reference\n");
		exit (1);
    }else if(length(S)!= G->order){
		printf("Graph Error: DFS() called on size not equal to G\n");
		exit(EXIT_FAILURE);
	}else{
		List L = copyList(S);
		clear(S);
		for(int i = 1; i <= G->order; i++){
			G->color[i] 	= 0; // white
			G->parent[i] 	= NIL;
		}
		for(moveFront(L); index(L) >= 0; moveNext(L)){
			int x = get(L);
			if(G->color[x] == 0){ //white
				visit(G, S, x);
			}
		}
		freeList(&L);		
	}
}


//------------------------------Other operations----------------------------//


// transpose()
// returns transpose of G to a new graph.
Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: transpose() called on NULL Graph reference\n");
		exit(1);
	}else{
		Graph trans = newGraph(G->order);
		for(int i = 1; i <= G->order; i++){
			List L = G->adj[i];
			for(moveFront(L); index(L) >= 0; moveNext(L)){
				addArc(trans, get(L), i);
			}
		}
		return trans;
	}
}

// copyGraph()
// returns a copy of G to a new graph.
Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Graph Error: copyGraph() called on NULL Graph reference\n");
		exit(1);
	}else{
		Graph copy = newGraph(G->order);
		for(int i = 1; i <= G->order; i++){
			List L = G->adj[i];
			for(moveFront(L); index(L) >= 0; moveNext(L)){
				addArc(copy, i, get(L));
			}
		}
		return copy;
	}
}

// printGraph()
// prints the graph adjacency list.
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		printf("Graph Error: pringGraph() called on NULL Graph reference\n");
		exit(1);
	}else if(out == NULL){
		printf("Graph Error: pringGraph() called on NULL file reference\n");
		exit(1);
    }else{
        for(int i = 1; i <= G->order; i++){
            fprintf(out,"%d:",i);
            printList(out,G->adj[i]);
            fprintf(out,"\n");
        }
    }
}