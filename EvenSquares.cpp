// 1 square of length n
// 2 sum of squares of length n, n-4
// 3 sum of squares of length n, n-6
// 4 sum of squares of length n, n-8
// 5 sum of squares of length n, n-4, n-6
// 6 sum of squares of length n, n-4, n-8
// 7 sum of squares of length n, n-6, n-8
// 8 sum of squares of length n, n-4, n-6, n-8
// 9 sum of squares of length n-2, n-2, n-4
// 10 sum of squares of length n-2, n-2, n-6
// 11 sum of squares of length n-2, n-2, n-4, n-4
// 12 sum of squares of length n-2, n-2, n-4, n-6

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

enum {CREATE_STATES, ADD_TRANSITIONS};

struct State {
	int secondLastN;
	int nextHigherN;
	int next2HigherN;
	int nextHigherN2;
	int lastN6;
	int nextLowerN6;
	int secondLastN8;
	int lastN8;
	int nextLowerN8;
	int next2LowerN8;
	int lowerCarry;
	int higherCarry;
	State(int q = 0, int w = 0, int e = 0, int r = 0, int t = 0, int y = 0, int u = 0, 
		int i = 0, int o = 0, int p = 0, int a = 0, int s = 0) {
		secondLastN = q;
		nextHigherN = w;
		next2HigherN = e;
		nextHigherN2 = r;
		lastN6 = t;
		nextLowerN6 = y;
		secondLastN8 = u;
		lastN8 = i;
		nextLowerN8 = o;
		next2LowerN8 = p;
		lowerCarry = a;
		higherCarry = s;		
	}
};

class AutomatonGenerator {
private:
	string name;
	int n, n2, n4, n6, n8;
	int maxCarry;
	int guessedCarry;
	void addATransitions();
	void addStateTransitions(State s);

public:
	AutomatonGenerator(string, bool, bool, bool, bool, bool, int);
	string getStateName(State s);
	void addTransitions();
	void loopOverStates(int param);
};

AutomatonGenerator::AutomatonGenerator (string nm, bool n0, bool nMinusTwo, bool nMinusFour, bool nMinusSix, bool nMinusEight, int gc) {
	name = nm;
	if (n0)
		n = 1;
	if (nMinusTwo)
		n2 = 2;
	if (nMinusFour)
		n4 = 1;
	if (nMinusSix)
		n6 = 1;
	if (nMinusEight)
		n8 = 1;
	maxCarry = n + n2 + n4 + n6 + n8 - 1;
	guessedCarry = gc;
}

string AutomatonGenerator::getStateName(State s) {
	string ret = name;
	if (n)
		ret += "_" + to_string(s.secondLastN) + "_" + to_string(s.nextHigherN) + "_" + to_string (s.next2HigherN);
	if (n2)
		ret += "_" + to_string(s.nextHigherN2);
	if (n6)
		ret += "_" + to_string(s.lastN6) + "_" + to_string(s.nextLowerN6);	
	if (n8)
		ret += "_" + to_string(s.secondLastN8) + "_" + to_string(s.lastN8) + "_" + to_string (s.nextLowerN8) + "_" + to_string(s.next2LowerN8);

	return ret+"_"+to_string(s.lowerCarry)+"_"+to_string(s.higherCarry);
}

void AutomatonGenerator::addStateTransitions(State s) {

}

void AutomatonGenerator::addATransitions() {
	string sname = getStateName(State());
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int higherN = 0; higherN <= n; higherN++) {
			for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
				for (int N4 = 0; N4 <= n4; N4++) {
					for (int lowerN6 = 0; lowerN6 <= n6; lowerN6++) {
						for (int higherN6 = 0; higherN6 <= n6; higherN6++) {
							for (int lowerN8 = 0; lowerN8 <= n8; lowerN8++) {
								for (int higherN8 = 0; higherN8 <= n8; higherN8++) {
									int lowerBit = (lowerN + lowerN2 + N4 + lowerN6 + lowerN8) % 2;
									int lowerCarry = (lowerN + lowerN2 + N4 + lowerN6 + lowerN8) / 2;
									int higherBit = (higherN + 1 + N4 + higherN6 + higherN8) % 2;
									int higherCarry = (higherN + 1 + N4 + higherN6 + higherN8) / 2;
									string destName = getStateName(State(higherN, 
										0, lowerN, lowerN2, lowerN6, higherBit,
										lowerN8, 0, 0, higherN8, lowerCarry, higherCarry));
									cout << "(" << sname << "a" << higherBit << lowerBit << destName <<")\n";
								}		
							}								
						}		
					}		
				}	
			}			
		}		
	}
}

void AutomatonGenerator::addTransitions() {
	addATransitions();
	for(int secondLastN = 0; secondLastN <= n; secondLastN++) {
		for(int nextHigherN = 0; nextHigherN <=n; nextHigherN++) {
			for(int next2HigherN = 0; next2HigherN <=n; next2HigherN++) {
				for(int nextHigherN2 = 0; nextHigherN2 <=n2; nextHigherN2++) {
					for(int lastN6 = 0; lastN6 <= n6; lastN6++) {
						for(int nextLowerN6 = 0; nextLowerN6 <= n6; nextLowerN6++) {
							for(int secondLastN8 = 0; secondLastN8 <= n8; secondLastN8++) {
								for(int lastN8 = 0; lastN8 <=n8; lastN8++) {
									for(int nextLowerN8 = 0; nextLowerN8 <=n8; nextLowerN8++) {
										for(int next2LowerN8 = 0; next2LowerN8 <=n8; next2LowerN8++) {
											for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
												for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
											addStateTransitions (State(secondLastN,
												nextHigherN,next2HigherN,
												nextHigherN2,lastN6,
												nextLowerN6,secondLastN8,lastN8,
												nextLowerN8, next2LowerN8, lowerCarry, higherCarry));
												cout << endl;	
												}
											}
										}
									}
								}
							}
						}
					}
				}	
			}			
		}
	}
}

void AutomatonGenerator::loopOverStates(int param) {
	for(int secondLastN = 0; secondLastN <= n; secondLastN++) {
		for(int nextHigherN = 0; nextHigherN <=n; nextHigherN++) {
			for(int next2HigherN = 0; next2HigherN <=n; next2HigherN++) {
				for(int nextHigherN2 = 0; nextHigherN2 <=n2; nextHigherN2++) {
					for(int lastN6 = 0; lastN6 <= n6; lastN6++) {
						for(int nextLowerN6 = 0; nextLowerN6 <= n6; nextLowerN6++) {
							for(int secondLastN8 = 0; secondLastN8 <= n8; secondLastN8++) {
								for(int lastN8 = 0; lastN8 <=n8; lastN8++) {
									for(int nextLowerN8 = 0; nextLowerN8 <=n8; nextLowerN8++) {
										for(int next2LowerN8 = 0; next2LowerN8 <=n8; next2LowerN8++) {
											for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
												for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {
													if (param == CREATE_STATES) {
														cout << getStateName(State(secondLastN,
															nextHigherN,next2HigherN,
															nextHigherN2,lastN6,
															nextLowerN6,secondLastN8,lastN8,
															nextLowerN8, next2LowerN8, lowerCarry, higherCarry)) <<endl;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}	
			}			
		}
	}
}


int main() {
	vector <AutomatonGenerator> machines;

	machines.push_back(AutomatonGenerator("A", true, false, false, false, false, 0));

	cout << "FiniteAutomaton evenSqChecker = (\n";	
	// cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c00 c01 c10 c11\n";
	// cout << "d00 d01 d10 d11 e00 e01 e10 e11 f},\n";

	cout << "states = {\n";
	for(int i =0; i < machines.size(); i++)
		machines.at(i).loopOverStates(CREATE_STATES);
	cout<<"acc},\n";

	cout << "initialStates = {\n";
	for(int i =0; i < machines.size(); i++)
		cout << machines.at(i).getStateName(State())<<endl;
	cout << "},\nfinalStates = {acc},\n";

	cout << "transitions = {\n";
	for(int i =0; i < machines.size(); i++)
		machines.at(i).addTransitions();

	cout <<"\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(evenSqChecker);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n\n\n\n\n";
}
