#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void solveJosephus(long long int n, long long int k);

int main(){
    long long int n, k;
    scanf("%lld %lld", &n, &k);

    solveJosephus(n, k);
}

Node* create_list(long long int n){
    Node* head = NULL;
    Node* prev = NULL;

    for(long long int i = 1; i <= n; i++){
        Node* current = (Node*)malloc(sizeof(Node));
        current->data = i;
        current->next = NULL;

        if(head == NULL){
            head = current;
        }
        else{
            prev->next = current;
        }

        prev = current;
    }

    if(prev != NULL){
        prev->next = head;
    }

    return head;
}


void solveJosephus(long long int n, long long int k){
    if(n <= 0) return;

    Node* head = create_list(n);
    if(head == NULL) return;

    Node* current = head;
    Node* prev = NULL;

    int steps = 0;
    int remaining = n; //Add remainder

    if(k == 0){
        for(int i = 0; i < n; i++){
            printf("%lld ", current->data);
            current = current->next;
        }
        return;
    }

    // if k >=1
    while(current->next != current){
        steps = (k % remaining == 0) ? remaining : (k % remaining);
        for(long long int i = 0; i < steps; i++){
            prev = current;
            current = current->next;
        }

        // Eliminate the k-th node
        prev->next = current->next;
        printf("%lld ", current->data);
        free(current);
        current = prev->next;
        remaining--;
    }

    if(remaining == 1 || current->next == current){
        printf("%lld ", current->data);
        free(current);
        return;
    }
}
