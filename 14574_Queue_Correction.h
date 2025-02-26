#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    const int v;
    struct Node *next;
}Node;

void solve(Node* head, int l, int r){
    if(head == NULL || l == r) return head;

    Node dummyHead;
    dummyHead.next = head->next;
    Node* nodeBeforeSublist = &dummyHead;
    int position = 1;

    if(l == 1){
        nodeBeforeSublist = head;
    }

    while(position < l){
        nodeBeforeSublist = nodeBeforeSublist->next;
        position++;
        //essentially moves it to the next pointer until it reaches just below the start of the sublist
    }
    Node* workingPtr = nodeBeforeSublist->next;
    //points to the start of the sub list
    while(l < r){
        Node* nodeToBeExtracted = workingPtr->next;
        workingPtr->next = nodeToBeExtracted->next;
        nodeToBeExtracted->next = nodeBeforeSublist->next;
        nodeBeforeSublist->next = nodeToBeExtracted;
        l++;
    }

    return dummyHead.next;
}

#endif
