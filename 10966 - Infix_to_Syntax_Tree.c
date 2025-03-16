#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

BTNode* makeNode(char c){
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));

    if(c == sym[0]){
        newNode->data = ID_A;
    }
    else if(c == sym[1]){
        newNode->data = ID_B;
    }
    else if(c == sym[2]){
        newNode->data = ID_C;
    }
    else if(c == sym[3]){
        newNode->data = ID_D;
    }
    else if(c == sym[4]){
        newNode->data = OP_AND;
    }
    else{
        newNode->data = OP_OR;
    }

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


BTNode* EXPR(){
    // EXPR = FACTOR | EXPR OP FACTOR

    char c;
    BTNode *right = FACTOR(); // find the first factor in the tree node

    while (pos >= 0 && (expr[pos] == sym[4] || expr[pos] == sym[5])){ //if our position in the expression falls on an operator
        BTNode* root = makeNode(expr[pos]); //make the node for that operator;
        pos--;
        root->left = EXPR(); //recursive calling to go further down the tree
        root->right = right; // let the right branch be the factor we just collected
        right = root; //let the right node now become the root node
    }

    return right;
}

BTNode* FACTOR(){
    // FACTOR = ID | (EXPR)

    BTNode* newNode = NULL;

    if(expr[pos] >= sym[0] && expr[pos] <= sym[3]){ //if the position we're in is in the A-D range
        newNode = makeNode(expr[pos]); //make the node
        pos--; //shift to the next factor (id or operator)
    }
    else if(expr[pos] == ')'){
        pos--;
        newNode = EXPR();
        if(pos >= 0 && expr[pos] == '(') pos--;
    }

    return newNode;
}

