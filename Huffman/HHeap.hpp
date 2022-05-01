#pragma once
#include <iostream>
#include "HNode.hpp"
#include "MinHeap.hpp"
using namespace std;
class HHeap{
    void gen(int* niz, int curr, HNode* node);
    public:
    HNode *start;

    HHeap(){
        start = nullptr;
    }
    ~HHeap(){
        delete start;
    }

    void generateHHeapFromMinHeap(MinHeap *h);

    void generateCodeTable(int* niz);


};

void HHeap::generateHHeapFromMinHeap(MinHeap *h){
    HNode *l, *r, *old, *novo;
    l = h->popMin();
    r = h->popMin();
    start = new HNode('\0', l->freq + r->freq);
    start->left = l;
    start->right = r;
    old = start;
    while(!h->empty()){
        novo = h->popMin();
        if(novo->freq > old->freq){
            l = novo;
            r = old;
        }else{
            l = old;
            r = novo;
        }
        start = new HNode('\0', l->freq + r->freq);
        start->left = l;
        start->right = r;
        old = start;
    }
}

void HHeap::generateCodeTable(int * niz){
    gen(niz,0, start->left);
    gen(niz,1, start->right);
}
void HHeap::gen(int *niz, int curr, HNode *node){
    if(node->info != '\0'){
        niz[node->info] = curr;
    }else{
        gen(niz, curr*2, node->left);
        gen(niz, (curr *2) + 1, node->right);
    }
}
