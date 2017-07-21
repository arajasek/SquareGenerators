#include <iostream>
#include <string> 
#include <utility>
#include <bitset>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

void convertOdd(string &s) {
	for (int i = 0; i < s.size()/2; i++) {
		if (s.at(i) == '0')
			s.at(i) = 'a';
		else
			s.at(i) = 'b';
	}

	if (s.at(s.size()/2) == '0')
		s.at(s.size()/2) = 'c';
	else
		s.at(s.size()/2) = 'd';

	for (int i = s.size()/2 + 1; i < s.size(); i++) {
		if (s.at(i) == '0')
			s.at(i) = 'e';
		else
			s.at(i) = 'f';
	}
}

void convertEven(string &s) {
	for (int i = 0; i < s.size()/2; i++) {
		if (s.at(i) == '0')
			s.at(i) = 'a';
		else
			s.at(i) = 'b';
	}

	for (int i = s.size()/2; i < s.size(); i++) {
		if (s.at(i) == '0')
			s.at(i) = 'e';
		else
			s.at(i) = 'f';
	}
}

string convert(string &s) {
	string output = "[";
	int limit = (s.size() - 6)/2;
	for (int i = 0, j = s.size() / 2 - 1; i < limit; i++, j++)
		output = output + "a" + s.at(j) + s.at(i) + " ";
	for (int i = limit, j = s.size() - 4; i < limit + 2; i++, j++)
		output = output + "b" + s.at(j) + s.at(i) + " ";
	char c = 'd';
	if (s.at(s.size() - 2) == '0')
		c = 'c';
	output += c;
	output += " ";
	output += "d]";
	return output;
}

int main() {
	vector<int> vals = {131,140,149,158,167,176,185,194,203,212,221,230,239,248};
	int pos = 0;
	int i = 8;
	unsigned int limit = pow (2,i);
	for (unsigned int j =  pow (2,i - 1); j < limit; j++) {
		string word = bitset< 64 >( j ).to_string();
		word = word.substr(word.size() - i, i);
//		cout << word << " ";
		std::reverse(word.begin(),word.end());
//		cout << convert (word) <<endl;
		if (pos < vals.size() && j == vals.at(pos) ) {
			pos++;
			cout<<"assert(!accepts(finalAut, "<<convert(word)<<")); // "<<j<<"\n";
		}
		else
			cout<<"assert(accepts(finalAut, "<<convert(word)<<")); // "<<j<<"\n";
	}
}