#include<bits/stdc++.h>

struct node{
    int value;
    int lazy;
    node *child[2];

    int getvalue(){
        return this == NULL ? 0 : value;
    }

    int getlazy(){
        return this == NULL ? 0 : lazy;
    }

    node *getchild(int i){
        return this == NULL ? NULL : child[i];
    }
};

const int POOLSIZE = 100000;
node *nodepool;
int poolcnt = 0;

node *newnode(){
    if (!poolcnt){
        nodepool = new node [POOLSIZE];
        poolcnt += POOLSIZE;
    }
    return nodepool + (-- poolcnt);
}

void push(){
}

void add(node *seg, int l, int r, int l, int qr, int value){
    if (ql <= l && qr >= r){
        seg -> value += value * ()
}

int query(){
}
