#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100005

typedef struct Node{
    int value;
    struct Node* next;
} Node;

Node* adj[MAX_NODES];
int maxDistance[MAX_NODES];

Node* createNode(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
};

/* we use and adjacency list instead of a doubly linked list mainly because in a doubly linked list
you cannot traverse the neighbors of a node directly like in an adjacency list
*/

void addEdge(int u, int v){//notice how there's a list in this? This is an adjacency list
    Node* newNode = createNode(v); //this creates a new node with the value v and v's next will be NULL
    newNode->next = adj[u]; //this lets v's next point to the current head in u's list
    //this means that v is inserted at the beginning of the (u's) list
    adj[u] = newNode; //update the head of u's adjacency list to point to v (the new node), now u's list starts with v

    newNode = createNode(u); //creates a new node with the value u, and it's next as NULL
    // this represents v's neighbor: u
    newNode->next = adj[v]; // sets the next pointer of u (the new node) to the current head of v's adjacency list
    //this means that u is inserted at the beginning of the (v's) list;
    adj[v] = newNode; //update the head of v's adjacency list to point to u, now v's list starts with u
}

void depthFirstSearch(int node, int parent, int depth){
    /* node is the current node we're exploring,
    parent is the node that we came from to reach the "node",
    we use this to avoid revisiting the parent node and get stuck in an infinite loop
    depth is the distance from the starting node to the current node ("node")
    this represents how far the node is from the root of traversal.
    */
    maxDistance[node] = depth; //this records the distance (depth) from the current node in the maxDistance array.
    //this array keeps track how far each node is from the starting node
    for(Node* current = adj[node]; current != NULL; current = current->next){
    //this loop iterates through all the neighbors in the current node("node"). each neighbor is represented by an edge in the adjacency list
        if(current->value != parent){
            // this ensures we don't revisit the node we just came from (parent). Prevents DFS from going back and forth between 2 nodes infinitely
            depthFirstSearch(current->value, node, depth + 1);
            /*
            For reach valid neighbor (current->value), the function calls itself recursively to explore that neighbor.
            current->value: the neighbor to explore next
            node: the current node, becomes the parent node
            depth + 1, the distance increases by 1, because we "walk" by one step further from the starting node
            */
        }
    }
}

int main(){
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N - 1; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    depthFirstSearch(1, -1, 0);
    /* This line calls the depthFirstSearch function to traverse the tree starting from node 1.
    1: the starting node for this depthFirstSearch
    -1: implies that the node has no parent node
    0: indicates the initial depth, it's 0 because we're starting here
    */

    /* This DFS explores the entire tree, starting from node 1. For each node it calculates the distance from
    node 1 and stores it in the maxDistance array. After this DFS, maxDistance[i] will contain the distance of node i from node 1*/
    int farthestNode = 1;
    for(int i = 1; i <= N; i++){
        if(maxDistance[i] > maxDistance[farthestNode]){
            farthestNode = i;
        }
    }

    depthFirstSearch(farthestNode, -1, 0);
    /* This calls the depthFirstSearch function to traverse the tree starting from the node farthestNode
    farthestNode: this is the farthest node found in the first DFS
    -1: indicates that this node has no parent node, since it's the root of traversal
    0: the initial depth is 0, since we're starting here */

    // the first DFS helps find the longest path in the tree
    // the second DFS finds the ACTUAL diameter of the tree

    int diameter = 0;

    for(int i = 1; i <= N; i++){
        if(maxDistance[i] > diameter){
            diameter = maxDistance[i];
        }
    }

    int minMana = (diameter + 1) / 2;
    printf("%d", minMana);

    return 0;
}
