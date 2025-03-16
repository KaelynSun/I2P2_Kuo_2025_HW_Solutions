#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

void connectEdges(Node **head, int*count, int*queue, int*operation, int N);
void addEdge(Node** head, int *count, int u, int v);
int breadthFirstSearch(Node** head, int*count, int*queue, int*operation, int N, int K);
void freeMemory(Node**head, int*count, int*queue, int*operation, int N);

int main(){
    int testcase;
    Node **head = NULL;
    int *count = NULL;
    int *queue = NULL;
    int *operation = NULL;


    scanf("%d", &testcase);

    while(testcase--){
        int N, K;
        scanf("%d %d", &N, &K);
        head = (Node*)malloc((N+1)*sizeof(Node));
        count = (int*)malloc((N+1)*sizeof(int));
        queue = (int*)malloc((N+1)*sizeof(int));
        operation = (int*)malloc((N+1)*sizeof(int));

        connectEdges(head, count, queue, operation, N);
        printf("%d\n", breadthFirstSearch(head, count, queue, operation, N, K));
        freeMemory(head, count, queue, operation, N);

    }

    return 0;
}

void addEdge(Node **head, int *count, int u, int v){
    Node* newNode = NULL;

    newNode = (Node*)malloc(sizeof(Node)); //allocate memory for a newnode
    newNode->data = u; //let the newnode's data be u
    newNode->next = head[v]; //let the newnode become the new head of v's adjacent list
    head[v] = newNode; //let v also point back to newnode

    newNode = (Node*)malloc(sizeof(Node)); //do the same for v -> u
    newNode->data = v;
    newNode->next = head[u];
    head[u] = newNode;

    count[u]++, count[v]++;
    // count is an array which stores the degree of node u (count[u]) and v (count[v])
    // incrementing it means adding a degree
}

void connectEdges(Node**head, int*count, int*queue, int*operation, int N){
    int i = 0;
    for(i = 1; i <= N; i++){
        head[i] = NULL; //head is the adjacency list, each element (head[i]) is a pointer to the head of the linked list for node i
        //setting head[i] = NULL means that i has no neighbours
        count[i] = 0; //sets that i has no degree (no nodes connected to it)
        operation[i] = 0;
        //operation is used later in the BFS to determine if that node has been "operated" on or not
        // operation[i] = 0 to show that the node i has not been operated on
    }

    int u, v;
    for(int i = 1; i < N; i++){
        scanf("%d %d", &u, &v);
        addEdge(head, count, u, v);
    }
}

int breadthFirstSearch(Node **head, int *count, int *queue, int* operation, int N, int K){
    // breadthFirstSearch identifies all leaves (nodes with degree 1) and adds them to the queue
    // Process the queue level by level, for each leaf reduce the degree of its neighbors (as we remove them)
    int queueCount = 0, i = 0;

    for(i = 1; i <= N; i++){
        if(count[i] == 1){ //if the node has a degree of 1, that mean it's a leaf
            queue[queueCount++] = i; //add the (node i) leaf to the queue
            operation[i] = 1;
            //queue is an array that acts as a queue
            //queueCount keeps track of the number of leaves in the queue
            //operation[i] = 1, marks that node as operated on
        }
    }

    for(i = 0; i < queueCount; i++){ //loop through the queue (i from 0 to queueCount-1)
        for(Node *current = head[queue[i]]; current; current = current->next){
            //for each node in the queue (queue[i]), traverse it's neighbors using the adjacency list(head[queue[i]])
            //for each neighbor (current->data):
            if(--count[current->data] == 1 && !operation[current->data]){
                //reduce it's degree by 1: --count[current->data
                // if the neighbor's degree becomes 1 and it hasn't been processed yet (!operation[current->data])
                operation[current->data] = operation[queue[i]] + 1;
                // mark it as processed (operation[current->data] = operation[queue[i]] + 1;
                //the operation level is incremented by 1 from the current node
                queue[queueCount++] = current->data;
                //add the node to the queue
            }
        }
    }

    //count how many nodes are removed
    int remove = 0;
    for(i = 1; i <= N; i++){//loop through all nodes(1 to N)
        if(operation[i] <= K) remove++;//if a nodes's operation level is less than or equal to K, it has been removed
        //count the number of removed nodes
    }

    return N-remove; //return the number of remaining nodes

    /*
    SUMMARY:

    1. leaves are nodes with degree 1
    2. When a leaf is removed, its neighbor's degrees are reduced
    3. If a neighbor's degree becomes 1, it is now a (also) a leaf and it (also) added to the queue
    4. After K operations, the function counts how many nodes are left
    */
}

void freeMemory(Node **head, int *count, int*queue, int*operation, int N){
    Node* deleteNode = NULL;
    for(int i = 1; i <= N; i++){
        for(Node* temp = head[i]; temp;){
            deleteNode = temp;
            temp = temp->next;
            free(deleteNode);
            deleteNode = NULL;
        }
        head[i] = NULL;
    }

    free(head);
    free(count);
    free(queue);
    free(operation);
}
