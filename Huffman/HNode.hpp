#pragma once
#include <iostream>
using namespace std;
class HNode{
    public:
    char info;
    int freq;
    HNode *left, *right;

    HNode(char info, int freq){
        this->info = info;
        this->freq = freq;
        right = left = nullptr;
    }
    ~HNode(){
        delete left;
        delete right;
    }
    void print(){
        cout << ((info == 0) ? '@' : info) << " : " << freq << endl;
        /*if(left != nullptr)
            left->print();
        if(right != nullptr)
            right->print();*/
    }
    void printAll(int i){
        cout << i << " ---- " << ((info == 0) ? '@' : info) << " : " << freq << endl;
        if(left != nullptr)
            left->printAll(i+1);
        if(right != nullptr)
            right->printAll(i+1);
    }
};
