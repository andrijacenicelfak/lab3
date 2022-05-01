#pragma once
#include <iostream>
#include "HNode.hpp"
#include "MinHeap.hpp"
using namespace std;
class HHeap{
    void gen(char** niz, char *curr, HNode* node);
    public:
    HNode *start;

    HHeap(){
        start = nullptr;
    }
    ~HHeap(){
        delete start;
    }

    void generateHHeapFromMinHeap(MinHeap *h);

    void generateCodeTable(char** niz);


};

void HHeap::generateHHeapFromMinHeap(MinHeap *h){
    HNode *l, *r, *novo;
    l = h->popMin();
    r = h->popMin();
    start = new HNode('\0', l->freq + r->freq);
    start->left = l;
    start->right = r;
    while(!h->empty()){
        /*
        cout << "--------------------------------------------\n";
        start->printAll(0);
        /**/
        h->push(start);

        l = h->popMin();
        r = h->popMin();
        start = new HNode('\0', l->freq + r->freq);
        start->left = l;
        start->right = r;
    }
}

void HHeap::generateCodeTable(char **niz){
    char *strL = new char[2];
    char *strR = new char[2];
    strcpy(strL, "0");
    strcpy(strR, "1");
    gen(niz, strL, start->left);
    gen(niz, strR, start->right);
    delete[] strL;
    delete[] strR;
}
void HHeap::gen(char **niz, char* curr, HNode *node){
    if(node == nullptr) return;
    if(node->info != '\0'){
        niz[node->info] = new char[strlen(curr+1)];
        strcpy(niz[node->info], curr);
    }else{
        int l = strlen(curr);
        char *strL = new char[l+2];
        char *strR = new char[l+2];
        strcpy(strL, curr);
        strcpy(strR, curr);
        strL[l] = '0';
        strL[l+1] = '\0';
        strR[l] = '1';
        strR[l+1] = '\0';

        gen(niz, strL, node->left);
        gen(niz, strR, node->right);

        delete[] strL;
        delete[] strR;
    }

}
