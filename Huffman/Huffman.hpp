#pragma once
#include "HNode.hpp"
#include "HHeap.hpp"
#include "MinHeap.hpp"
#include <iostream>
#include <fstream>
using namespace std;
class Huffman{
    char* txt, *codedTxt;
    int* codes;
    int txtLenght;
    MinHeap *minHeap;
    HHeap *hHeap;

    public:
    Huffman(){
        minHeap = new MinHeap();
        hHeap = new HHeap();
    }
    ~Huffman(){
        if(txt != nullptr)
            delete[] txt;
        if(codedTxt != nullptr)
            delete[] codedTxt;
        if(codes != nullptr)
            delete[] codes;
        if(minHeap != nullptr)
            delete minHeap;
        if(hHeap != nullptr)
            delete hHeap;
    }
    void loadFromTxtFile(char* fileName);
    void writeToFileCoded(char* fileName);
    void printCodes();
};

void Huffman::loadFromTxtFile(char* fileName){
    //cout << "Ucitavam iz fajla \n";
    //deo za ucitavanje
    ifstream f(fileName);
    f.seekg(0, f.end);
    size_t size = f.tellg();
    size += 1;
    txt = new char[size];
    f.seekg(0, f.beg);
    f.get(txt, size);
    txt[size] = '\0';
    f.close();
    //cout << "Ucitano!\n";
    //Pravimo cvorove za sve karaktere
    HNode **nodes = new HNode*[256];
    for(int i = 0; i < 256; i++)
        nodes[i] = new HNode(i, 0);
    //cout << "Napravio cvorove!\n";
    //Pri pojavljivanju karaktera povecavamo frekvenciju pojavljivanja
    for(size_t i = 0; i < size; i++)
        nodes[txt[i]]->freq++;
    //cout << "Podesio freq!\n";
    //Ubacujemo svaki karakter koji se nije javio u minHeap
    for(int i = 0; i < 256; i++){
        if(nodes[i]->freq > 0)
            minHeap->push(nodes[i]);
    }
    minHeap->printNodes();
    cout << "Dodao na minHeap!\n";
    //Generisemo Huffman-ovo stablo i kodove
    hHeap->generateHHeapFromMinHeap(minHeap);
    cout << "Generisao HHeap!\n";
    hHeap->generateCodeTable(codes);
    cout << " GOTOVO!\n";

}
void Huffman::printCodes(){
    for(int i = 0; i < 256; i++){
        cout << i << " : " << codes[i] << endl;
    }
}