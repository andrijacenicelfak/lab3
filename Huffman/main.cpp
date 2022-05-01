#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

#include "Huffman.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2)
        return -1;

    Huffman *h = new Huffman();
    ofstream f(argv[2], ios::app);
    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    h->loadFromTxtFile(argv[1]);    

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start;
    f   << "Naziv fajla : " << argv[1] << endl
        << "Vreme potrebno za kodiranje : " << mills  << " ms"<<endl
        << "-----------------------------------------------------" << endl;
    //h->printCodes();
    delete h;

    return 1;
}