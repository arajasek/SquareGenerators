#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v1 = {0, 36, 45, 54, 63};
	vector<int> v2 = {0, 136, 153, 170, 187, 204, 221, 238, 255};
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v1.size(); j++) {
			for (int k = 0; k < v1.size(); k++) {
				for (int l = 0; l < v2.size(); l++) {
					for (int m = 0; m < v2.size(); m++) {
						for (int n = 0; n < v2.size(); n++) {
							for (int o = 0; o < v2.size(); o++) {
								if (v1.at(i) + v1.at(j) + v1.at(k) + v2.at(l) + v2.at(m) + v2.at(n) + v2.at(o) == 520)
									cout<<v1.at(i)<<" "<<v1.at(j)<<" "<<v1.at(k)<<" "<<v2.at(l)<<" "<<v2.at(m)<<" "<<v2.at(n)<<" "<<v2.at(o)<<endl;
							}
						}
					}
				}
			}
		}
	}
}