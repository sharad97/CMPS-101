//---------------------------//
//Sharad Shrestha            //
//sshrest3                   //
//CMPS 101                   //
//Patrick Tantalo            //
//Programming Assignment 4   //
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
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
}GraphObj;


//--------------------------Constructors-Destructors-----------------------//

// newGraph()
// returns a Graph reference to new empty Graph object.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for(int i=1; i<=n; i++){
        G->color[i] = 0; // white
        G->distance[i] = INF;
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
        free((*pG)->distance);
        free((*pG)->parent);
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

// getSource()
// returns source that was most recently used in BFS.
int getSource(Graph G){
    if(G == NULL) {
        printf("Graph Error: getSource() called on NULL Graph reference\n");
        exit(1);
    }else{
        return (G->source);
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

// getDist()
// returns the Distance from the source to u.
int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: getDist() called on NULL Graph reference\n");
        exit(1);
    } else if(u<1 || u>getOrder(G)){
        printf("Graph Error: getDist() called without of bounds value 'u'\n");
        exit(1);
    }else{
        return (G->distance[u]);	
    }
}

// getPath()
// returns the path from the source to u.	
void getPath(List L, Graph G, int u){
    if(G->source == NIL){
        printf("Graph Error: getPath() called before BFS\n");
        exit (1);
    }else if (u < 1 || u >getOrder(G)){
        printf("Graph Error: getPath() called without of bounds value 'u'\n");
        exit(1);
    }else if( u == G->source){
        append(L,G->source);
    }else if( G->parent[u] == NIL){
        append(L,NIL);
    }else{
        getPath(L, G, G->parent[u]); 
        append(L, u);
    }
}


//---------------------------Manipulation procedures-----------------------//


// makeNull()
// deletes all edges of graph G.
void makeNull(Graph G){
    if(G == NULL){
        printf("Graph Error: makeNull() called on NULL Graph reference\nou0i8i	");
        exit(1);
    }else{
        for(int i=1; i<=G->order; i++){
            clear(G->adj[i]);
        }
    }
    G->size = 0;
}

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
        moveFront(L);
        while(index(L) >= 0){
            x = get(L);
            if(v < x){
                insertBefore(L, v);
                moveBack(L);
            }
			moveNext(L);
        }
        if(v > x && index(L) == -1){
            append(L, v);
        }
    }
    G->size++;
}

// BFS()
// runs BFS algorithm on graph G.
// Discovers the distance and childs from the parent of each edge.
void BFS(Graph G, int s){
    if(G == NULL){
        printf("Graph Error: BFS() called on NULL Graph reference\n");
        exit(1);
    }else if(s<1 || s>getOrder(G)){
        printf("Graph Error: BFS() called without of bounds value 's'\n");
        exit(1);
    }
    G->source = s;
    for(int i = 1; i <= G->order; i++){
        G->color[i] 	= 0; // white
        G->distance[i] 	= INF;
        G->parent[i] 	= NIL;
    }
    G->source = s; 
    G->color[s] = 1; // gray 
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    moveFront(Q);
    while(index(Q)>=0){
        int x = get(Q);
        List L = G->adj[x];
        moveFront(L);
        while(index(L)>=0){
            int y = get(L);
            if(G->color[y] == 0){ // white
                G->color[y] = 1; // gray
                G->distance[y] = G->distance[x]+1;
                G->parent[y] = x;
                append(Q, y);
            }
            moveNext(L);
        }
        G->color[x] = 2; // black
        moveNext(Q);
    }
    freeList(&Q);
}


//------------------------------Other operations----------------------------//


// printGraph()
// prints the graph adjacency list.
void printGraph(FILE* out, Graph G){
    if(out == NULL){
        printf("Graph Error: cannot print to NULL file pointer");
        return;
    }else if(G == NULL){
        printf("Graph Error: cannot print NULL Graph pointer");
        return;
    }else{
        for(int i = 1; i <= G->order; i++){
            fprintf(out,"%d:",i);
            printList(out,G->adj[i]);
            fprintf(out,"\n");
        }
    }
}

