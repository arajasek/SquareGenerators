// every length-n integer, n odd, n >= 13, is the sum of binary squares of
// length

// (A)
// - exactly one of (n-1) and exactly one of (n-3) OR
// - exactly 2 of (n-1) and exactly one of (n-3) OR
// - exactly one of (n-1) and exactly two of (n-3) OR
// - two exactly of n-1 and two exactly of n-3 OR

// (B)
// - one each exactly of n-1, n-3, n-5 OR
// - two exactly of n-1, one exactly of n-3, one exactly of n-5 .

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

class AutomatonGeneratorA {
private:
	string name;
	int maxCarry;
	int guessedCarry;
	int oneNumber, threeNumber;
	bool firstAut;
	string getQStateName(int, int, int, int);
	void createStates();
	void addQTransitions();
	void addAllStateTransitions();
	void addSingleStateABCTransitions(int, int, int, int);
	void addSingleStateDTransitions(int, int, int, int);
	void addSingleStateETransitions(int, int, int, int);
public:
	AutomatonGeneratorA(int, int, int, bool);
	void print();

};

//sqChecker_n1_n2_n3_n4 means
// n1 squares of length n-1
// n2 squares of length n-3
// n3 squares of length n-5
// guessed carry of n4

AutomatonGeneratorA::AutomatonGeneratorA(int i, int j, int k, bool f) {
	string subname = to_string(i) + "_" + to_string(j) + "_0_" + to_string(k);
	name = "sqChecker_" + subname;
	maxCarry = i + j - 1;
	oneNumber = i;
	threeNumber = j;
	guessedCarry = k;
	firstAut = f;
}

// Q states are 4-tuples (a,b,c1,c2) where a is the last digit of the n-3 guesses
// b is the next guessed n-3 digit
// c1 is the upper carry
// c2 is the lower carry

string AutomatonGeneratorA::getQStateName(int a, int b, int c1, int c2) {
	return (name+"_"+to_string(a)+"_"+to_string(b)+"_"+to_string(c1)+"_"+to_string(c2));
}

void AutomatonGeneratorA::addSingleStateETransitions(int a, int b, int c1, int c2) {
	string name = getQStateName(a,b,c1,c2);
	int i = oneNumber;
	int lowerBit = (i+ c2 + a) % 2;
	int higherBit = (i + c1) % 2;
	int lowerCarry = (i + c2 + a) / 2;
	int higherCarry = (i + c1) / 2;	
	if ((lowerCarry == guessedCarry) && (higherCarry == 1)) {
		cout << "(" << name << " e" << higherBit << lowerBit << " s1)\n";
	}
}

void AutomatonGeneratorA::addSingleStateDTransitions(int a, int b, int c1, int c2) {
	if(b != threeNumber)
		return;
	string name = getQStateName(a,b,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		int lowerBit = (i+ c2 + b) % 2;
		int higherBit = (i + c1) % 2;
		int lowerCarry = (i + c2 + b) / 2;
		int higherCarry = (i + c1) / 2;	
		// note that the b in the destination state is meaningless
		cout << "(" << name << " d" << higherBit << lowerBit << " " << getQStateName(a, b, higherCarry, lowerCarry)<<")\n";
	}
}

void AutomatonGeneratorA::addSingleStateABCTransitions(int a, int b, int c1, int c2) {
	string name = getQStateName(a,b,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {		
			int lowerBit = (i+ c2 + b) % 2;
			int higherBit = (i + j + c1) % 2;
			int lowerCarry = (i + c2 + b) / 2;
			int higherCarry = (i + j + c1) / 2;	
			cout << "(" << name << " a" << higherBit << lowerBit << " " << getQStateName(a, j, higherCarry, lowerCarry)<<")\n";
			cout << "(" << name << " b" << higherBit << lowerBit << " " << getQStateName(a, j, higherCarry, lowerCarry)<<")\n";
			if (j == threeNumber)
				cout << "(" << name << " c" << higherBit << lowerBit << " " << getQStateName(a, j, higherCarry, lowerCarry)<<")\n";
		}
	}
}

void AutomatonGeneratorA::addAllStateTransitions() {
	for(int i = 0; i <= threeNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {
			for (int k = 0; k <= maxCarry; k++)	{
				for (int l = 0; l <= maxCarry; l++) {
					addSingleStateABCTransitions(i, j, k, l);
					addSingleStateDTransitions(i, j, k, l);
					addSingleStateETransitions(i, j, k, l);
					cout << endl;
				}
			}
		}
	}
	cout <<"(s1 f acc)\n}\n);\n";
}

void AutomatonGeneratorA::addQTransitions() {
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {		
			for (int k = 0; k <= threeNumber; k++) {
				int lowerBit = (i+j) % 2;
				int higherBit = (guessedCarry + i + k) % 2;
				int lowerCarry = (i+j) / 2;
				int higherCarry = (guessedCarry + i + k) / 2;
				cout << "(q a" << higherBit << lowerBit << " " << getQStateName(j, k, higherCarry, lowerCarry)<<")\n";
			}
		}
	}
}



void AutomatonGeneratorA::createStates() {
	cout << "states = { q\n";
	for(int i = 0; i <= threeNumber; i++) 
		for (int j = 0; j <= threeNumber; j++)
			for (int k = 0; k <= maxCarry; k++)	
				for (int l = 0; l <= maxCarry; l++)
					cout << getQStateName(i,j,k,l) <<endl;	
	cout<<"s1 acc},\n";
	cout << "initialStates = {q},\nfinalStates = {acc},\n";
}

void AutomatonGeneratorA::print() {
	cout << "FiniteAutomaton "<<name<<" = (\n";
	cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c00 c01 c10 c11\n";
	cout << "d00 d01 d10 d11 e00 e01 e10 e11 f},\n";
	createStates();
	cout << "transitions = {\n";
	addQTransitions();
	addAllStateTransitions();
	if (firstAut) 
		cout << "FiniteAutomaton finalAut = shrinkNwa(complement("<<name<<"));\n";
	else
		cout<< "finalAut = intersect(finalAut, shrinkNwa(complement("<<name<<")));\n";
}

class AutomatonGeneratorB {
private:
	string name;
	int maxCarry;
	int guessedCarry;
	int oneNumber, threeNumber, fiveNumber;
	string getQStateName(int, int, int, int, int, int, int, int);
	string getPStateName(int, int, int, int, int, int);
	void createStates();
	void addQTransitions();
	void addPTransitions();
	void addSinglePTransitions(int, int, int, int, int, int);
	void addAllStateTransitions();
	void addSingleStateATransitions(int, int, int, int, int, int, int, int);
	void addSingleStateBTransitions(int, int, int, int, int, int, int, int);
	void addSingleStateCTransitions(int, int, int, int, int, int, int, int);
	void addSingleStateDTransitions(int, int, int, int, int, int, int, int);
	void addSingleStateETransitions(int, int, int, int, int, int, int, int);

public:
	AutomatonGeneratorB(int, int, int, int);
	void print();

};

// //sqChecker_n1_n2_n3_n4 means
// // n1 squares of length n-1
// // n2 squares of length n-3
// // n3 squares of length n-5
// // guessed carry of n4

AutomatonGeneratorB::AutomatonGeneratorB(int i, int j, int k, int l) {
	string subname = to_string(i) + "_" + to_string(j) + "_" + to_string(k) + "_" + to_string(l);
	name = "sqChecker_" + subname;
	maxCarry = i + j + k - 1;
	oneNumber = i;
	threeNumber = j;
	fiveNumber = k;
	guessedCarry = l;
}

// // R states are 4-tuples (a,b,c1,c2,e) where a is the last digit of the n-3 guesses
// // c1 is the upper carry
// // c2 is the lower carry

// string AutomatonGeneratorB::getRStateName(int a, int c1, int c2) {
// 	return ("r_"+to_string(a)+"_"+to_string(c1)+"_"+to_string(c2));
// }

// P states are 6-tuples (a,b,u,w,c1,c2) where a is the last digit of the n-3 guesses
// b is the next guessed n-3 digit
// u is the last n-5 digit
// w is the next n-5 guess
// c1 is the upper carry
// c2 is the lower carry

string AutomatonGeneratorB::getPStateName(int a, int b, int u, int w, int c1, int c2) {
	return (name+"_p_"+to_string(a)+"_"+to_string(b)+"_"+to_string(u)+"_"+to_string(w)+"_"+to_string(c1)+"_"+to_string(c2));
}

// Q states are 8-tuples (a,b,u,v,w,x,c1,c2) where a is the last digit of the n-3 guesses
// b is the next guessed n-3 digit
// u is the last n-5 digit
// v is the second-last n-5 guess
// w is the next n-5 guess
// x is the 2-away n-5 guess
// c1 is the upper carry
// c2 is the lower carry

string AutomatonGeneratorB::getQStateName(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	return (name+"_q_"+to_string(a)+"_"+to_string(b)+"_"+to_string(u)+"_"+to_string(v)+"_"+to_string(w)+"_"+to_string(x)+"_"+to_string(c1)+"_"+to_string(c2));
}

void AutomatonGeneratorB::addSingleStateETransitions(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	if ((w != fiveNumber) || (x != fiveNumber) || (b != threeNumber))
		return;
	int i = oneNumber;
	string name = getQStateName(a,b,u,v,w,x,c1,c2);
	int lowerBit = (i+ c2 + a + u) % 2;
	int higherBit = (i + c1) % 2;
	int lowerCarry = (i + c2 + a + u) / 2;
	int higherCarry = (i + c1) / 2;	
	if ((lowerCarry == guessedCarry) && (higherCarry == 1))
		cout << "(" << name << " e" << higherBit << lowerBit << " s1)\n";
}

void AutomatonGeneratorB::addSingleStateDTransitions(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	if ((w != fiveNumber) || (x != fiveNumber) || (b != threeNumber))
		return;
	string name = getQStateName(a,b,u,v,w,x,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		int lowerBit = (i+ c2 + b + v) % 2;
		int higherBit = (i + c1) % 2;
		int lowerCarry = (i + c2 + b + v) / 2;
		int higherCarry = (i + c1) / 2;	
		cout << "(" << name << " d" << higherBit << lowerBit << " " << getQStateName(a, b, u, v, x, x, higherCarry, lowerCarry)<<")\n";
	}
}

void AutomatonGeneratorB::addSingleStateCTransitions(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	if ((w != fiveNumber) || (x != fiveNumber))
		return;
	int j = threeNumber;
	string name = getQStateName(a,b,u,v,w,x,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		int lowerBit = (i+ c2 + b + w) % 2;
		int higherBit = (i + j + c1) % 2;
		int lowerCarry = (i + c2 + b + w) / 2;
		int higherCarry = (i + j + c1) / 2;	
		cout << "(" << name << " c" << higherBit << lowerBit << " " << getQStateName(a, j, u, v, x, x, higherCarry, lowerCarry)<<")\n";
	}
}

void AutomatonGeneratorB::addSingleStateBTransitions(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	if (x != fiveNumber)
		return;
	string name = getQStateName(a,b,u,v,w,x,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {	
			int lowerBit = (i+ c2 + b + w) % 2;
			int higherBit = (i + j + c1) % 2;
			int lowerCarry = (i + c2 + b + w) / 2;
			int higherCarry = (i + j + c1) / 2;	
			cout << "(" << name << " b" << higherBit << lowerBit << " " << getQStateName(a, j, u, v, x, x, higherCarry, lowerCarry)<<")\n";
		}
	}
}

void AutomatonGeneratorB::addSingleStateATransitions(int a, int b, int u, int v, int w, int x, int c1, int c2) {
	string name = getQStateName(a,b,u,v,w,x,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {	
			for (int k = 0; k <= fiveNumber; k++) {	
				int lowerBit = (i+ c2 + b + w) % 2;
				int higherBit = (i + j + c1 + k) % 2;
				int lowerCarry = (i + c2 + b + w) / 2;
				int higherCarry = (i + j + c1 + k) / 2;	
				cout << "(" << name << " a" << higherBit << lowerBit << " " << getQStateName(a, j, u, v, x, k, higherCarry, lowerCarry)<<")\n";
			}
		}
	}
}

void AutomatonGeneratorB::addAllStateTransitions() {
	for(int a = 0; a <= threeNumber; a++) {
		for (int b = 0; b <= threeNumber; b++) {
			for(int u = 0; u <= fiveNumber; u++)  {
				for (int v = 0; v <= fiveNumber; v++) {
					for(int w = 0; w <= fiveNumber; w++)  {
						for (int x = 0; x <= fiveNumber; x++) {
							for (int k = 0; k <= maxCarry; k++)	 {
								for (int l = 0; l <= maxCarry; l++) {
									addSingleStateATransitions(a,b,u,v,w,x,k,l);
									addSingleStateBTransitions(a,b,u,v,w,x,k,l);
									addSingleStateCTransitions(a,b,u,v,w,x,k,l);
									addSingleStateDTransitions(a,b,u,v,w,x,k,l);
									addSingleStateETransitions(a,b,u,v,w,x,k,l);
									cout << endl;
								}
							}
						}
					}
				}
			}
		}

	}
	cout <<"(s1 f acc)\n}\n);\n";
}

void AutomatonGeneratorB::addSinglePTransitions(int a, int b, int u, int v, int c1, int c2) {
	string name = getPStateName(a,b,u,v,c1,c2);
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {		
			for (int l = 0; l <= fiveNumber; l++) {		
				for (int m = 0; m <= fiveNumber; m++) {
					int lowerBit = (i+b+l+c2) % 2;
					int higherBit = (i + j + m +c1) % 2;
					int lowerCarry = (i+b+l+c2) / 2;
					int higherCarry = (i + j + m +c1) / 2;
					cout << "(" << name <<" a" << higherBit << lowerBit << " " << getQStateName(a, b, u, l, v, m, higherCarry, lowerCarry)<<")\n";
				}
			}
		}
	}
}

void AutomatonGeneratorB::addPTransitions() {
	for(int a = 0; a <= threeNumber; a++) {
		for (int b = 0; b <= threeNumber; b++) {
			for(int u = 0; u <= fiveNumber; u++)  {
				for (int v = 0; v <= fiveNumber; v++) {
					for (int k = 0; k <= maxCarry; k++)	 {
						for (int l = 0; l <= maxCarry; l++) {
							addSinglePTransitions(a,b,u,v,k,l);
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorB::addQTransitions() {
	for(int i = 0; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {		
			for (int k = 0; k <= threeNumber; k++) {
				for (int l = 0; l <= fiveNumber; l++) {		
					for (int m = 0; m <= fiveNumber; m++) {
						int lowerBit = (i+j+l) % 2;
						int higherBit = (guessedCarry + i + k+m) % 2;
						int lowerCarry = (i+j+l) / 2;
						int higherCarry = (guessedCarry + i + k+m) / 2;
						cout << "(q a" << higherBit << lowerBit << " " << getPStateName(j, k, l, m, higherCarry, lowerCarry)<<")\n";
					}
				}
			}
		}
	}
}

void AutomatonGeneratorB::createStates() {
	cout << "states = { q\n";
	for(int a = 0; a <= threeNumber; a++) 
		for (int b = 0; b <= threeNumber; b++)
			for(int u = 0; u <= fiveNumber; u++) 
				for (int v = 0; v <= fiveNumber; v++)
					for(int w = 0; w <= fiveNumber; w++) 
						for (int x = 0; x <= fiveNumber; x++)
							for (int k = 0; k <= maxCarry; k++)	
								for (int l = 0; l <= maxCarry; l++)
									cout << getQStateName(a,b,u,v,w,x,k,l) <<endl;	
	for(int a = 0; a <= threeNumber; a++) 
		for (int b = 0; b <= threeNumber; b++)
			for(int u = 0; u <= fiveNumber; u++) 
				for (int v = 0; v <= fiveNumber; v++)
					for (int k = 0; k <= maxCarry; k++)	
						for (int l = 0; l <= maxCarry; l++)
							cout << getPStateName(a,b,u,v,k,l) <<endl;	
	
	cout<<"s1 acc},\n";
	cout << "initialStates = {q},\nfinalStates = {acc},\n";
}

void AutomatonGeneratorB::print() {
	cout << "FiniteAutomaton "<<name<<" = (\n";	
	cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c00 c01 c10 c11\n";
	cout << "d00 d01 d10 d11 e00 e01 e10 e11 f},\n";
	createStates();
	cout << "transitions = {\n";
	addQTransitions();
	addPTransitions();
	addAllStateTransitions();
 	cout<< "finalAut = intersect(finalAut, shrinkNwa(complement("<<name<<")));\n";
}

int main() {
	bool flag = true;
	int oneNumber = 2, threeNumber = 2;
	for (int i = 1; i <= oneNumber; i++) {
		for (int j = 0; j <= threeNumber; j++) {
			if (i+j < 2)
				continue;
			for (int k = 0; k < (i + j); k++) {
				AutomatonGeneratorA a (i, j ,k, flag);
				a.print();
				flag = false;
			}
		}
	}
	cout << "finalAut = shrinkNwa(complement(finalAut));\n";
	cout << "print(numberOfStates(finalAut));\n";
}