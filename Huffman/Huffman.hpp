#pragma once
#include "HNode.hpp"
#include "HHeap.hpp"
#include "MinHeap.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
class Huffman{
    char* txt;
    char** codes;
    int txtLenght;
    MinHeap *minHeap;
    HHeap *hHeap;

    public:
    Huffman(){
        minHeap = new MinHeap();
        hHeap = new HHeap();
        codes = new char*[256];
        txtLenght = 0;
        for(int i = 0; i < 256; i++)
            codes[i] = nullptr;
    }
    ~Huffman(){
        if(txt != nullptr)
            delete[] txt;
        if(codes != nullptr){
            for(int i = 0; i < 256; i++)
                delete[] codes[i];
            delete[] codes;
        }
        if(minHeap != nullptr)
            delete minHeap;
        if(hHeap != nullptr)
            delete hHeap;
    }
    void encode(char* tekst, int size);
    void decode(char* fileName);
    double poboljsanje();
    void printCodes();
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

void Huffman::encode(char* tekst, int size){
    txtLenght = size;
    this->txt = tekst;
    //cout << "Ucitano!\n";
    //Pravimo cvorove za sve karaktere
    HNode **nodes = new HNode*[256];
    for(int i = 0; i < 256; i++)
        nodes[i] = new HNode(i, 0);
    //cout << "Napravio cvorove!\n";
    //Pri pojavljivanju karaktera povecavamo frekvenciju pojavljivanja
    for(size_t i = 0; i < size-1; i++)
        nodes[txt[i]]->freq++;
    //cout << "Podesio freq!\n";
    //Ubacujemo svaki karakter koji se nije javio u minHeap
    for(int i = 0; i < 256; i++){
        if(nodes[i]->freq > 0)
            minHeap->push(nodes[i]);
    }
    //minHeap->printNodes();
    //cout << "Dodao na minHeap!\n";
    //Generisemo Huffman-ovo stablo i kodove
    hHeap->generateHHeapFromMinHeap(minHeap);
    //cout << "Generisao HHeap!\n";
    hHeap->generateCodeTable(codes);
    //cout << " GOTOVO!\n";

}
void Huffman::printCodes(){
    for(int i = 0; i < 256; i++){
        if(codes[i] != nullptr)
            cout << (char)i << " : " << codes[i] << endl;
    }
}
double Huffman::poboljsanje(){ // Lose ali ok
    double num = 0;
    int lenghts[256];
    for(int i = 0; i < 256; i++)
        lenghts[i] = codes[i] == nullptr ? 0 : strlen(codes[i]);
    for(int i = 0; i < txtLenght; i++){
        num += lenghts[txt[i]];
    }
    return ceil(100.0 - 100.0 * num / (txtLenght * 8));
}