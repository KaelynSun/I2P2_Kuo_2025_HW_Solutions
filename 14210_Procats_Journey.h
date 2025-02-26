#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdbool.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

bool hasCycle(ListNode *head){
    struct ListNode *slowNode = head, *fastNode = head;

    //The loop that runs while the fast node and the slow node are not NULL pointers and are not equal (as in they don't land on the same node)

    while(slowNode && fastNode && fastNode->next){
        slowNode = slowNode->next;
        fastNode = fastNode->next->next;

        if(slowNode == fastNode){
            return true;
        }
    }

    return false;
}

// Implement the above function in a `.c` file
// You might start with the following codes:

/*
#include "function.h"

bool hasCycle(ListNode *head) {
    // ...
}
*/

#endif
