#pragma once
#include "HNode.hpp"
class MinHeap{
    void heapify_down(int i);
    public:
    int size, tr;
    HNode **arr;
    MinHeap(){
        size = 256;
        arr = new HNode*[size];
        tr = 0;
    }
    ~MinHeap(){
        for(int i = 0; i < tr;i++)
            delete arr[i];
        delete[] arr;
    }
    void push(HNode *node);

    HNode* popMin();
    int empty(){ return tr == 0;}
    void printNodes(){
        cout << "Tr broj : " << tr << endl;
        for(int i = 0; i < tr; i++){
            cout << i << " : ";
            arr[i]->print();
        }
    }
};

void MinHeap::push(HNode *node){//NE VA:LJAAAA
    int i = tr++, p = (i - 1) / 2;
    arr[i] = node;
    while(arr[p]->freq > arr[i]->freq && i != p){
        HNode * pom = arr[p];
        arr[p] = arr[i];
        arr[i] = pom;

        i = p;
        p = (i - 1) / 2;
    }
}
HNode* MinHeap::popMin(){
    HNode* ret = arr[0];
    tr--;
    arr[0] = arr[tr];
    heapify_down(0);
    ret->print();
    return ret;
}
void MinHeap::heapify_down(int i){ // NZM STO NECE OVOOOO!
    int left = (2*i + 1);
    int right = (2*i + 2);
    int smallest = i;
    if (left < size && arr[left]->freq < arr[i]->freq) {
        smallest = left;
    }
    if (right < size && arr[right]->freq < arr[smallest]->freq) {
        smallest = right;
    }
    if (smallest != i){
        HNode* pom = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = pom;
        heapify_down(smallest);
    }
}