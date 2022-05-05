#pragma once
#include <iostream>
#include <fstream>
#include <math.h>

#include "SFNode.hpp"
#include "MinHeap.hpp"
using namespace std;
class ShannonFano{
    char* txt;
    char** codes;
    int txtLenght;
    int numNodes;
    SFNode *start;
    SFNode **nodes;
    public:
    ShannonFano(){
        start = nullptr;
        numNodes = 0;
        codes = new char*[256];
        txtLenght = 0;
        for(int i = 0; i < 256; i++)
            codes[i] = nullptr;
        nodes = new SFNode*[256];
        
    }
    void writeToFileCoded(char* fileName);
    double poboljsanje();
    void printCodes();
    void sort();
    void createTree(int beg, int end, SFNode *node);
    void generateCodeTable(char **niz);
    void gen(char **niz, char* curr, SFNode *node);
    void encode(char* tekst, int size);
    int size(){
        double num = 0;
        int lenghts[256];
        for(int i = 0; i < 256; i++)
            lenghts[i] = codes[i] == nullptr ? 0 : strlen(codes[i]);
        for(int i = 0; i < txtLenght; i++){
            num += lenghts[txt[i]];
        }
        return ceil(num/8.0);
    }
};
void ShannonFano::encode(char* tekst, int size){
    txt = tekst;
    txtLenght = size;
    
    for(int i = 0; i < 256; i++)
        nodes[i] = new SFNode(i, 0);

    for(size_t i = 0; i < size-1; i++)
        nodes[txt[i]]->freq++;
    //cout << "Podesio freq!\n";


    sort(); // Izbacimo sve cvorove u niz sortirani od najveceg do najmanjeg

    //cout << "Uspesan sort!\n";
    start = new SFNode(0, 0);
    createTree(0, numNodes-1, start);
    generateCodeTable(codes);
}
void ShannonFano::printCodes(){
    for(int i = 0; i < 256; i++){
        if(codes[i] != nullptr)
            cout << (char)i << " : " << codes[i] << endl;
    }
}
double ShannonFano::poboljsanje(){ // Lose ali ok
    double num = 0;
    int lenghts[256];
    for(int i = 0; i < 256; i++)
        lenghts[i] = codes[i] == nullptr ? 0 : strlen(codes[i]);
    for(int i = 0; i < txtLenght; i++){
        num += lenghts[txt[i]];
    }
    return ceil(100.0 - 100.0 * num / (txtLenght * 8));
}

void ShannonFano::sort(){
    MinHeap *h = new MinHeap();
    for(int i = 0; i < 256; i++){
        if(nodes[i]->freq > 0){
            h->push(nodes[i]);
        }else{
            delete nodes[i];
        }
        nodes[i] = nullptr;
    }
    numNodes = h->getSize();
    int i= numNodes-1;
    while(!h->empty() && i >= 0)
        nodes[i--] = h->popMin();
}
void ShannonFano::createTree(int beg, int end, SFNode* node){
    if(beg == end){ // 1 node
        node->info = nodes[beg]->info;
        node->freq = nodes[beg]->freq;
        delete nodes[beg];
        nodes[beg] = nullptr;
    }else if(beg +1 == end){ // 2 node
        node->left = nodes[beg];
        node->right = nodes[end];
        nodes[beg] = nullptr;
        nodes[end] = nullptr;
    }else{ // vise noda ostalo
        int fl = 0, fr = 0;
        int i = beg, j = end;
        int last = 0;
        while(i < j){
            if(fl <= fr){
                fl += nodes[i++]->freq;
                last = 0;
            }else{
                fr += nodes[j--]->freq;
                last = 1;
            }
        }
        if(last) j++; else i--;

        node->left = new SFNode(0,0);
        node->right = new SFNode(0,0);
        createTree(beg, i, node->left);
        createTree(j, end, node->right);
    }
}

void ShannonFano::generateCodeTable(char **niz){
    char *strL = new char[2];
    char *strR = new char[2];
    strcpy(strL, "0");
    strcpy(strR, "1");
    gen(niz, strL, start->left);
    gen(niz, strR, start->right);
    delete[] strL;
    delete[] strR;
}
void ShannonFano::gen(char **niz, char* curr, SFNode *node){
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