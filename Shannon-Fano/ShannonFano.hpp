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
    void loadFromTxtFile(char* fileName);
    void writeToFileCoded(char* fileName);
    double poboljsanje();
    void printCodes();
    void sort();
    void createTree(int beg, int end, SFNode *node);
};

void ShannonFano::loadFromTxtFile(char* fileName){
    //cout << "Ucitavam iz fajla \n";
    //deo za ucitavanje
    ifstream f(fileName);
    f.seekg(0, f.end);
    size_t size = f.tellg();
    size += 1;
    txtLenght = size;
    txt = new char[size];
    f.seekg(0, f.beg);
    f.get(txt, size);
    txt[size] = '\0';
    f.close();
    //cout << "Ucitano!\n";
    //Pravimo cvorove za sve karaktere
    /**/
    for(int i = 0; i < 256; i++)
        nodes[i] = new SFNode(i, 0);
    /**/
    //cout << "Napravio cvorove!\n";
    //Pri pojavljivanju karaktera povecavamo frekvenciju pojavljivanja
    for(size_t i = 0; i < size-1; i++)
        nodes[txt[i]]->freq++;
    //cout << "Podesio freq!\n";


    sort(); // Izbacimo sve cvorove u niz sortirani od najveceg do najmanjeg

    start = new SFNode(0, 0);
    createTree(0, numNodes-1, start);

    printCodes();
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
    numNodes = h->size();
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
        int i = 0, j = end;
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
        //j++; // i -- => ili da se nadje nekako efikasnije resenje da se vidi sta je bolje? mozda da se vidi da li je razlika veca na jedan ili drugi nacin?
        //(abs(fl - fr + nodes[j+1]->freq) < abs(fl - fr - nodes[i-1]->freq) ? j++ : i--);
        //mozda ovako?
        if(last) j++; else i--;

        node->left = new SFNode(0,0);
        node->right = new SFNode(0,0);
        createTree(beg, i, node->left);
        createTree(j, end, node->right);
    }
}