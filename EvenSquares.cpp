// A square of length n
// B sum of squares of length n, n-4
// C sum of squares of length n, n-6
// D sum of squares of length n, n-8
// E sum of squares of length n, n-4, n-6
// F sum of squares of length n, n-4, n-8
// G sum of squares of length n, n-6, n-8
// H sum of squares of length n-2, n-2, n-4
// I sum of squares of length n-2, n-2, n-6
// J sum of squares of length n, n-4, n-6, n-8
// K sum of squares of length n-2, n-2, n-4, n-4
// L sum of squares of length n-2, n-2, n-4, n-6

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

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
	void addBTransitions(State s);
	void addCTransitions(State s);
	void addDTransitions(State s);
	void addETransitions(State s);
	void addFTransitions(State s);
	void addGTransitions(State s);
	void addHTransitions(State s);
	void addITransitions(State s);
	void addJTransitions(State s);
	void addStateTransitions(State s);

public:
	AutomatonGenerator(string, int, int, int, int, int, int);
	void createStates();
	string getStateName(State s);
	void addTransitions();
};

AutomatonGenerator::AutomatonGenerator (string nm, int n0, int nMinusTwo, int nMinusFour, int nMinusSix, int nMinusEight, int gc) {
	name = nm + to_string(gc);
	n = n0;
	n2 = nMinusTwo;
	n4 = nMinusFour;
	n6 = nMinusSix;
	n8 = nMinusEight;
	maxCarry = n + n2 + n4 + n6 + n8 - 1;
	guessedCarry = gc;
}

string AutomatonGenerator::getStateName(State s) {
	string ret = " " + name;
	if (n)
		ret += "_" + to_string(s.secondLastN) + "_" + to_string(s.nextHigherN) + "_" + to_string (s.next2HigherN);
	if (n2)
		ret += "_" + to_string(s.nextHigherN2);
	if (n6)
		ret += "_" + to_string(s.lastN6) + "_" + to_string(s.nextLowerN6);	
	if (n8)
		ret += "_" + to_string(s.secondLastN8) + "_" + to_string(s.lastN8) + "_" + to_string (s.nextLowerN8) + "_" + to_string(s.next2LowerN8);

	return ret+"_"+to_string(s.lowerCarry)+"_"+to_string(s.higherCarry)+" ";
}

void AutomatonGenerator::createStates() {
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

void AutomatonGenerator::addStateTransitions(State s) {
	if ((s.nextHigherN + s.secondLastN8 + s.nextLowerN8) == 0)
		addBTransitions(s);
	addCTransitions(s);
	if ((s.nextLowerN8 == n8) && (s.next2LowerN8 == 0))
		addDTransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 == 0) && (s.nextLowerN6 == n6))
		addETransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 + s.nextLowerN6 + s.lastN8) == 0)
		addFTransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 + s.nextLowerN6 + 
		s.lastN8 + s.lastN6 + s.secondLastN8 + s.lowerCarry) == 0)
		addGTransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 + s.nextLowerN6 + s.nextHigherN2 +
		s.lastN8 + s.lastN6 + s.secondLastN8 + s.next2HigherN + s.lowerCarry) == 0)
		addHTransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 + s.nextLowerN6 + 
		s.lastN8 + s.lastN6 + s.secondLastN8 + s.nextHigherN2 +
		s.next2HigherN + s.lowerCarry + s.nextHigherN) == 0)
		addITransitions(s);
	if ((s.nextLowerN8 + s.next2LowerN8 + s.nextLowerN6 + 
		s.lastN8 + s.lastN6 + s.secondLastN8 + s.nextHigherN2 +
		s.next2HigherN + s.lowerCarry + s.nextHigherN + s.secondLastN) == 0)
		addJTransitions(s);
}

void AutomatonGenerator::addJTransitions(State s) {
	string sname = getStateName(s);
	int higherBit = (n + s.higherCarry) % 2;
	int higherCarry = (n + s.higherCarry) / 2;
	if ((higherBit != 1) || (higherCarry != 0))
		return;
	cout << "(" << sname << "j" << higherBit <<" acc)\n";
}

void AutomatonGenerator::addITransitions(State s) {
	string sname = getStateName(s);
	int higherBit = (s.secondLastN + s.higherCarry) % 2;
	int higherCarry = (s.secondLastN + s.higherCarry) / 2;
	string destName = getStateName(State(0, 
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, higherCarry));
	cout << "(" << sname << "i" << higherBit << destName <<")\n";
}

void AutomatonGenerator::addHTransitions(State s) {
	string sname = getStateName(s);
	int higherBit = (s.nextHigherN + n2 + s.higherCarry) % 2;
	int higherCarry = (s.nextHigherN + n2 + s.higherCarry) / 2;
	string destName = getStateName(State(s.secondLastN, 
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, higherCarry));
	cout << "(" << sname << "h" << higherBit << destName <<")\n";
}

void AutomatonGenerator::addGTransitions(State s) {
	string sname = getStateName(s);
	int higherBit = (s.nextHigherN + s.nextHigherN2 + s.higherCarry) % 2;
	int higherCarry = (s.nextHigherN + s.nextHigherN2 + s.higherCarry) / 2;
	string destName = getStateName(State(s.secondLastN, 
		s.next2HigherN, 0, 0, 0, 0,
		0, 0, 0, 0, 0, higherCarry));
	cout << "(" << sname << "g" << higherBit << destName <<")\n";
}

void AutomatonGenerator::addFTransitions(State s) {
	string sname = getStateName(s);
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
			int lowerBit = (lowerN + lowerN2 + n4 + s.lastN6 + s.secondLastN8 + s.lowerCarry) % 2;
			int lowerCarry = (lowerN + lowerN2 + n4 + s.lastN6 + s.secondLastN8 + s.lowerCarry) / 2;
			int higherBit = (s.nextHigherN + s.nextHigherN2 + n4 + s.higherCarry) % 2;
			int higherCarry = (s.nextHigherN + s.nextHigherN2 + n4 + s.higherCarry) / 2;
			if (lowerCarry != guessedCarry)
				return;
			string destName = getStateName(State(s.secondLastN, 
				s.next2HigherN, lowerN, lowerN2, 0, 0,
				0, 0, 0, 0, 0, higherCarry));
			cout << "(" << sname << "f" << higherBit << lowerBit << destName <<")\n";
		}		
	}								
}		

void AutomatonGenerator::addETransitions(State s) {
	string sname = getStateName(s);
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
			for (int N4 = 0; N4 <= n4; N4++) {
				int lowerBit = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.lastN8 + s.lowerCarry) % 2;
				int lowerCarry = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.lastN8 + s.lowerCarry) / 2;
				int higherBit = (s.nextHigherN + s.nextHigherN2 + N4 + s.higherCarry) % 2;
				int higherCarry = (s.nextHigherN + s.nextHigherN2 + N4 + s.higherCarry) / 2;
				string destName = getStateName(State(s.secondLastN, 
					s.next2HigherN, lowerN, lowerN2, s.lastN6, 0,
					s.secondLastN8, 0, 0, 0, lowerCarry, higherCarry));
				cout << "(" << sname << "e" << higherBit << lowerBit << destName <<")\n";
			}		
		}								
	}		
}	

void AutomatonGenerator::addDTransitions(State s) {
	string sname = getStateName(s);
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
			for (int N4 = 0; N4 <= n4; N4++) {
				int lowerBit = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.nextLowerN8 + s.lowerCarry) % 2;
				int lowerCarry = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.nextLowerN8 + s.lowerCarry) / 2;
				int higherBit = (s.nextHigherN + s.nextHigherN2 + N4 + n6 + s.higherCarry) % 2;
				int higherCarry = (s.nextHigherN + s.nextHigherN2 + N4 + n6 + s.higherCarry) / 2;
				string destName = getStateName(State(s.secondLastN, 
					s.next2HigherN, lowerN, lowerN2, s.lastN6, n6,
					s.secondLastN8, s.lastN8, 0, 0, lowerCarry, higherCarry));
				cout << "(" << sname << "d" << higherBit << lowerBit << destName <<")\n";
			}		
		}								
	}		
}		

void AutomatonGenerator::addCTransitions(State s) {
	string sname = getStateName(s);
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
			for (int N4 = 0; N4 <= n4; N4++) {
				for (int higherN6 = 0; higherN6 <= n6; higherN6++) {
					for (int higherN8 = 0; higherN8 <= n8; higherN8++) {
						int lowerBit = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.nextLowerN8 + s.lowerCarry) % 2;
						int lowerCarry = (lowerN + lowerN2 + N4 + s.nextLowerN6 + s.nextLowerN8 + s.lowerCarry) / 2;
						int higherBit = (s.nextHigherN + s.nextHigherN2 + N4 + higherN6 + higherN8 + s.higherCarry) % 2;
						int higherCarry = (s.nextHigherN + s.nextHigherN2 + N4 + higherN6 + higherN8 + s.higherCarry) / 2;
						string destName = getStateName(State(s.secondLastN, 
							s.next2HigherN, lowerN, lowerN2, s.lastN6, higherN6,
							s.secondLastN8, s.lastN8, s.next2LowerN8, higherN8, lowerCarry, higherCarry));
						cout << "(" << sname << "c" << higherBit << lowerBit << destName <<")\n";
					}		
				}								
			}		
		}		
	}	
}			

void AutomatonGenerator::addBTransitions(State s) {
	string sname = getStateName(s);
	for (int lowerN = 0; lowerN <= n; lowerN++) {
		for (int lowerN2 = 0; lowerN2 <= n; lowerN2++) {
			for (int N4 = 0; N4 <= n4; N4++) {
				for (int higherN6 = 0; higherN6 <= n6; higherN6++) {
					for (int lowerN8 = 0; lowerN8 <= n8; lowerN8++) {
						for (int higherN8 = 0; higherN8 <= n8; higherN8++) {
							int lowerBit = (lowerN + lowerN2 + N4 + s.nextLowerN6 + lowerN8 + s.lowerCarry) % 2;
							int lowerCarry = (lowerN + lowerN2 + N4 + s.nextLowerN6 + lowerN8 + s.lowerCarry) / 2;
							int higherBit = (n + s.nextHigherN2 + N4 + higherN6 + higherN8 + s.higherCarry) % 2;
							int higherCarry = (n + s.nextHigherN2 + N4 + higherN6 + higherN8 + s.higherCarry) / 2;
							string destName = getStateName(State(s.secondLastN, 
								s.next2HigherN, lowerN, lowerN2, s.lastN6, higherN6,
								lowerN8, s.lastN8, s.next2LowerN8, higherN8, lowerCarry, higherCarry));
							cout << "(" << sname << "b" << higherBit << lowerBit << destName <<")\n";
						}		
					}								
				}		
			}		
		}	
	}			
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
									int higherBit = (higherN + n2 + N4 + higherN6 + higherN8 + guessedCarry) % 2;
									int higherCarry = (higherN + n2 + N4 + higherN6 + higherN8 + guessedCarry) / 2;
									string destName = getStateName(State(higherN, 
										0, lowerN, lowerN2, lowerN6, higherN6,
										0, lowerN8, 0, higherN8, lowerCarry, higherCarry));
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

void addMachines(string nm, int n0, int nMinusTwo, int nMinusFour, int nMinusSix, int nMinusEight, vector <AutomatonGenerator> &ms) {
	int maxGC = n0 + nMinusTwo + nMinusFour + nMinusSix + nMinusEight;
	for (int i = 0; i < maxGC; i++) {
		ms.push_back(AutomatonGenerator(nm, n0, nMinusTwo, nMinusFour, nMinusSix, nMinusEight, i));
	}
} 
int main() {
	vector <AutomatonGenerator> machines;

	// A square of length n
	// B sum of squares of length n, n-4
	// C sum of squares of length n, n-6
	// D sum of squares of length n, n-8
	// E sum of squares of length n, n-4, n-6
	// F sum of squares of length n, n-4, n-8
	// G sum of squares of length n, n-6, n-8
	// H sum of squares of length n-2, n-2, n-4
	// I sum of squares of length n-2, n-2, n-6
	// J sum of squares of length n, n-4, n-6, n-8
	// K sum of squares of length n-2, n-2, n-4, n-4
	// L sum of squares of length n-2, n-2, n-4, n-6

	addMachines("A", 1, 0, 0, 0, 0, machines);
	addMachines("B", 1, 0, 1, 0, 0, machines);
	addMachines("C", 1, 0, 0, 1, 0, machines);
	addMachines("D", 1, 0, 0, 0, 1, machines);
	addMachines("E", 1, 0, 1, 1, 0, machines);
	addMachines("F", 1, 0, 1, 0, 1, machines);
	addMachines("G", 1, 0, 0, 1, 1, machines);
	addMachines("H", 0, 2, 1, 0, 0, machines);
	addMachines("I", 0, 2, 0, 1, 0, machines);
	addMachines("J", 1, 0, 1, 1, 1, machines);
	addMachines("K", 0, 2, 2, 0, 0, machines);
	addMachines("L", 0, 2, 1, 1, 0, machines);

	cout << "FiniteAutomaton evenSqChecker = (\n";	
	cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c00 c01 c10 c11\n";
	cout << "d00 d01 d10 d11 e00 e01 e10 e11 f00 f01 f10 f11 g0 g1 h0 h1 i0 i1 j1},\n";

	cout << "states = {\n";
	for(int i =0; i < machines.size(); i++)
		machines.at(i).createStates();
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