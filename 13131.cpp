#include"13131.h"
#include<iostream>
#include<algorithm>
using namespace std;

Array_MAX_HEAP::Array_MAX_HEAP() : MAX_HEAP(){}

void Array_MAX_HEAP::PUSH(const int &key){
    array[Count] = key;
    int current = Count;
    Count++;

    while(current > 0){
        int parent = (current - 1)/2;
        if(array[current] > array[parent]){
            swap(array[current], array[parent]);
            current = parent;
        } else{
            break;
        }
    }
}

int Array_MAX_HEAP::MAX() const{
    if(Count == 0){
        return -1;
    } else{
        return array[0];
    }
}
int Array_MAX_HEAP::POP(){
    if(Count == 0) return -1;

    int root = array[0];
    array[0] = array[Count - 1];
    Count--;

    int i = 0;
    while(true){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if(left < Count && array[left] > array[largest]){
            largest = left;
        }
        if(right < Count && array[right] > array[largest]){
            largest = right;
        }

        if(largest != i){
            swap(array[i], array[largest]);
            i = largest;
        } else{
            break;
        }
    }

    return root;
}

List_MAX_HEAP::List_MAX_HEAP() : MAX_HEAP(), root(nullptr) {}

void List_MAX_HEAP::PUSH(const int &key) {
    Count++;
    if(Count == 1){
        root = new ListNode(key);
        return;
    }

    ListNode *parent = findparent(Count, root);

    ListNode *newNode = new ListNode(key);
    newNode->parent = parent;

    if(Count % 2 == 0){
        parent->left = newNode;
    } else{
        parent->right = newNode;
    }

    ListNode *current = newNode;
    while(current->parent != nullptr && current->value > current->parent->value){
        std::swap(current->value, current->parent->value);
        current = current->parent;
    }
}

int List_MAX_HEAP::MAX() const {
    if(Count == 0){
        return -1;
    } else{
        return root->value;
    }
}

int List_MAX_HEAP::POP() {
    if(Count == 0) return -1;

    int maxValue = root->value;

    if(Count == 1){
        delete root;
        root = nullptr;
        Count--;
        return maxValue;
    }

    ListNode *lastNodeParent = findparent(Count, root);
    ListNode *lastNode = (Count % 2 == 1) ? lastNodeParent->right : lastNodeParent->left;

    root->value = lastNode->value;

    if(Count % 2 == 1){
        lastNodeParent->right = nullptr;
    } else{
        lastNodeParent->left = nullptr;
    }
    delete lastNode;
    Count--;

    ListNode *current = root;
    while(true){
        ListNode *largest = current;

        if(current->left != nullptr && current->left->value > largest->value){
            largest = current->left;
        }
        if(current->right != nullptr && current->right->value > largest->value){
            largest = current->right;
        }

        if(largest != current){
            swap(current->value, largest->value);
            current = largest;
        } else{
            break;
        }
    }
    return maxValue;
}

void List_MAX_HEAP::deleteTree(ListNode *root){
    if(root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


int main(){
    int n, a;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "A_push"){
            cin >> a;
            A_heap.PUSH(a);
        }else if(s == "L_push"){
            cin >> a;
            B_heap.PUSH(a);
        }
        else if(s == "max"){
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        }
        else if(s == "A_pop"){
            cout << A_heap.POP() << "\n";
        }
        else if(s == "L_pop"){
            cout << B_heap.POP() << "\n";
        }
        else if(s == "size"){
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}
