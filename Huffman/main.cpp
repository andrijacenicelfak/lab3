#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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
    ifstream in(argv[1]);
    in.seekg(0, in.end);
    size_t size = in.tellg();
    size += 1;
    char *txt = new char[size];
    in.seekg(0, in.beg);
    in.get(txt, size);
    txt[size] = '\0';
    in.close();

    ofstream f(argv[2], ios::app);

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    h->encode(txt, size);

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start;
    double p = h->poboljsanje();
    f   << "Naziv fajla : " << argv[1] << endl
        << "Vreme potrebno za kodiranje : " << mills  << " ms"<<endl
        << "Broj byte pre kodiranja : " << size <<endl
        << "Broj byte posle kodiranja : " << h->size() <<endl
        << "Nova velicina fajla : " << 100.0 * h->size() / size << '%' <<endl
        << "-----------------------------------------------------" << endl;
    h->printCodes();
    delete h;

    return 1;
}