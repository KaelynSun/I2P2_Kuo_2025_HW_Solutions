#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

char treeX[100001], treeY[100001];
int posX = 0, posY = 0;

Node* createNodeX(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    while(isdigit(treeX[posX])){
        newNode->data = newNode->data * 10 + (treeX[posX] - '0');
        posX++;
    }

    return newNode;
}

Node* createNodeY(){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    while(isdigit(treeY[posY])){
        newNode->data = newNode->data * 10 + (treeY[posY] - '0');
        posY++;
    }

    return newNode;
}

Node* createTreeX(){
    // Tree X grammar: '(' INT '/' TREE '/' TREE ')' | NIL

    Node* root = NULL;

    //skip through the first '('
    if(treeX[posX] == '(') posX++;

    if(isdigit(treeX[posX])){
        root = createNodeX();
    }

    if(root && treeX[posX] == '/'){
        posX++;
        root->left = createTreeX();
    }

    if(root && treeX[posX] == '/'){
        posX++;
        root->right = createTreeX();
    }

    if(treeX[posX] == ')') posX++;

    return root;

}
Node* createTreeY(){
    // tree Y grammar: INT '(' TREE ')' '(' TREE ')' | NIL
    Node* root = NULL;

    if(isdigit(treeY[posY])){
        root = createNodeY();
    }

    if(root && treeY[posY] == '('){
        posY++;
        root->left = createTreeY();
    }

    if(root && treeY[posY] == ')'){
        posY++;
    }

    if(root && treeY[posY] == '('){
        posY++;
        root->right = createTreeY();
    }

    if(root && treeY[posY] == ')'){
        posY++;
    }

    return root;
}

bool isIdentical(Node* rootX, Node* rootY){
    if(rootX == NULL && rootY == NULL) return true;
    if(rootX == NULL || rootY == NULL) return false;

    return(rootX->data == rootY->data)
    && isIdentical(rootX->left, rootY->left)
    && isIdentical(rootX->right, rootY->right);
}

int main(){
    int N;
    scanf("%d", &N);

    scanf("%s", treeX);
    Node* rootX = createTreeX();
    scanf("%s", treeY);
    Node* rootY = createTreeY();

    if(isIdentical(rootX, rootY)){
        printf("YES");
    }
    else{
        printf("NO");
    }

    return 0;
}
