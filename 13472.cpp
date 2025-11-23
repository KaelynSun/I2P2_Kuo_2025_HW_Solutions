#include "13472.h"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

int n, k, q;

Node *leftNode = nullptr, *rightNode = nullptr;

Node *createNode(int v){
    Node *newNode = new Node;
    newNode->val = v;
    newNode->tag = 0;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void updateMid(Node *&mid, int &sz, int &now, bool &reverse){
    int newNow = (sz+1)/2;
    int diff = newNow - now;

    now = newNow;
    if(diff < 0) mid = (reverse) ? mid->next : mid->prev;
    else if(diff > 0) mid = (reverse) ? mid->prev : mid->next;
}

KuoYangPresent::KuoYangPresent(int k) {
    this->sz = 0;
    this->k = k;
    this->now = 0;
    this->reverse = false;
    this->head = this->mid = createNode(-1);
    this->tail = createNode(-1);
    head->next = tail;
    tail->prev = head;
}

void KuoYangPresent::Push(int x) {
    Node *newNode = createNode(x);
    sz++;
    if(reverse){
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
    }else{
        newNode->next = tail;
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        tail->prev = newNode;
    }updateMid(mid, sz, now, reverse);
}

void KuoYangPresent::Pop() {
    if(!mid || mid == head || mid == tail) return;

    if(leftNode == mid) leftNode = (leftNode->next) ? leftNode->next : nullptr;
    if(rightNode == mid) rightNode = (rightNode->prev) ? rightNode->prev : nullptr;
    if(leftNode && leftNode->prev == rightNode) leftNode = rightNode = nullptr;
    if(mid->prev) mid->prev->next = (mid->next) ? mid->next : nullptr;
    if(mid->next) mid->next->prev = (mid->prev) ? mid->prev : nullptr;

    Node *temp = mid;
    sz--;
    updateMid(mid, sz, now, reverse);
    delete temp;
    temp = nullptr;
}
void KuoYangPresent::Reverse() {
    reverse = !reverse;
    if(!(sz&1)) mid = (reverse) ? mid->next : mid->prev;
}

void KuoYangPresent::ProgrammingTanoshi() {
    leftNode = head->next;
    rightNode = tail->prev;
    if(leftNode && leftNode->prev == rightNode) leftNode = rightNode = nullptr;
}

void KuoYangPresent::KuoYangTeTe() {
    Node *cur = (leftNode) ? leftNode : nullptr;
    while(cur && cur != rightNode->next){
        cur->tag = 1;
        cur->val%=k;
        cur = cur->next;
    }
}

void KuoYangPresent::PrintList() {
    Node *cur = (reverse) ? tail->prev : head->next;
    while(cur && cur != head && cur != tail){
        cout << cur->val << " ";
        cur = (reverse) ? cur->prev : cur->next;
    }

    cout << endl;
}

int main() {
    cin >> n >> k >> q;
    assert(k <= 4000);
    KuoYangPresent present = KuoYangPresent(k);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        assert(x <= 10000);
        present.Push(x);
    }
    while (q--) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            assert(x <= 10000);
            present.Push(x);
        } else if (op == "pop") {
            present.Pop();
        } else if (op == "reverse") {
            present.Reverse();
        } else {
            cin >> op;
            present.ProgrammingTanoshi();
        }
    }
    present.KuoYangTeTe();
    present.PrintList();
}
