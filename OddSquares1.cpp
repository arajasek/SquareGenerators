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
	return ("q_"+to_string(a)+"_"+to_string(b)+"_"+to_string(c1)+"_"+to_string(c2));
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