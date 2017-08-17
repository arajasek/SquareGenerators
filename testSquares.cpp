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
	vector<int> vals1 = {827,836,844,845,853,854,861,862,863,870,871,872,878,879,880,881,887,888};
 
	vector<int> vals2 = {889,890,895,896,897,898,899,904,905,906,907,908,912,913,914,915,916,917,921,922,923,924,925,926,929,930,931,932,933,934,935,938,939};

	vector<int> vals3 = {940,941,942,943,944,946,947,948,949,950,951,952,953,955,956,957,958,959,960,961,962,963,964,965,966,967,968,969,970,971,972,973,974};
 
	vector<int> vals4 = {975,976,977,978,979,980,981,982,983,984,985,986,987,988,989,990,991,992,993,994,995,996,997,998};
 
	vector<int> vals5 = {999,1000,1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,1022,1023};


	vector<int> vals = vals1;

	vals.insert(vals.end(), vals2.begin(), vals2.end());
	vals.insert(vals.end(), vals3.begin(), vals3.end());
	vals.insert(vals.end(), vals4.begin(), vals4.end());
	vals.insert(vals.end(), vals5.begin(), vals5.end());

	int pos = 0;
	int i = 10;
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
			cout<<"assert(accepts(finalAut, "<<convert(word)<<")); \n";
	}
}