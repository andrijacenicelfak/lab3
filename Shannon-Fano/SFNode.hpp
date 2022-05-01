#pragma once
#include <iostream>
using namespace std;
class SFNode{
    public:
    char info;
    int freq;
    SFNode *left, *right;

    SFNode(char info, int freq){
        this->info = info;
        this->freq = freq;
        right = left = nullptr;
    }
    ~SFNode(){
        delete left;
        delete right;
    }
    void print(){
        cout << ((info == 0) ? '@' : info) << " : " << freq << endl;
    }
    void printAll(int i){
        cout << i << " ---- " << ((info == 0) ? '@' : info) << " : " << freq << endl;
        if(left != nullptr)
            left->printAll(i+1);
        if(right != nullptr)
            right->printAll(i+1);
    }
};
