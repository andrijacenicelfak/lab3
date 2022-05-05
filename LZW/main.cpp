#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

string decode(const vector<int> &v){
	map<int,string> inv_dict;
	int dictSize = 256;
	for(int i=0;i<dictSize;++i)
		inv_dict[i] = string(1,i);
	string s, entry, res;
	s = res = inv_dict[v[0]];
	for(size_t i = 1; i<v.size(); ++i){
		int k = v[i];
		if(inv_dict.count(k))
			entry = inv_dict[k];
		else if(k==dictSize)
			entry = s+s[0];
		else throw "error";
		res += entry;
		inv_dict[dictSize++] = s + entry[0];
		s = entry;
	}
	return res;
}

vector<int> encode(const string &ori){
	map<string,int> dict;
	int dictSize = 256;
	for(int i=0;i<dictSize;++i){
		dict[string(1,i)] = i;
    }
	vector<int> res;
	string s;
	for(char z : ori){
		if(dict.count(s+z)) s += z;
		else{
			res.push_back(dict[s]);
			dict[s+z] = dictSize++;
			s = z;
		}
	}
	if(s.size()) res.push_back(dict[s]);
	return res;
}

int main(int argc, char* argv[]){

    if(argc < 2)
        return -1;

    ofstream f(argv[2], ios::app);
	char* txt;

	ifstream inf(argv[1]);
    inf.seekg(0, f.end);
    size_t size = inf.tellg();
    size += 1;
    txt = new char[size];
    inf.seekg(0, f.beg);
    inf.get(txt, size);
    txt[size] = '\0';
    inf.close();

    string input(txt);
	vector<int> zdc;
    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	zdc = encode(input);

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start;
    f   << "Naziv fajla : " << argv[1] << endl
        << "Vreme potrebno za kodiranje : " << mills  << " ms"<<endl
        << "Broj byte pre kodiranja : " << input.size() <<endl
        << "Broj byte posle kodiranja : " << zdc.size()*4 <<endl
        << "Nova velicina fajla : " << 100.0 * zdc.size()*4 / input.size() << '%' <<endl
        << "-----------------------------------------------------" << endl;

    return 1;
}