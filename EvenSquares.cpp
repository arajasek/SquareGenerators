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

class AutomatonGenerator {
private:
	int n, n2, n4, n6, n8;
	int maxCarry;
	int guessedCarry;
	// string getQStateName(int, int, int, int);
	// void addQTransitions();
	// void addAllStateTransitions();
	// void addSingleStateABCTransitions(int, int, int, int);
	// void addSingleStateDTransitions(int, int, int, int);
	// void addSingleStateETransitions(int, int, int, int);
public:
	AutomatonGenerator(int, int, int, int, int, int);
	// string getInitialState();
	// void createStates();
	// void addTransitions();
};

AutomatonGenerator (int n0, int nMinusTwo, int nMinusFour, int nMinusSix, int nMinusEight, int gc) {
	n = n0;
	n2 = nMinusTwo;
	n4 = nMinusFour;
	n6 = nMinusSix;
	n8 = nMinusEight;
	maxCarry = n + n2 + n4 + n6 + n8 - 1;
	guessedCarry = gc;
}

int main() {
	vector <AutomatonGenerator> machines;

	va.push_back(AutomatonGenerator(1, 0, 0, 0, 0, 0));

	cout << "FiniteAutomaton evenSqChecker = (\n";	
	// cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c00 c01 c10 c11\n";
	// cout << "d00 d01 d10 d11 e00 e01 e10 e11 f},\n";

	cout << "states = {\n";
	for(int i =0; i < machines.size(); i++)
		machines.at(i).createStates();
	// cout<<"s1 acc},\n";

	cout << "initialStates = {\n";
	for(int i =0; i < machines.size(); i++)
		cout << machines.at(i).getInitialState()<<endl;
	cout << "},\nfinalStates = {acc},\n";

	cout << "transitions = {\n";
	for(int i =0; i < machines.size(); i++)
		machines.at(i).addTransitions();

	// cout <<"(s1 f acc)\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(evenSqChecker);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n\n\n\n\n";
}
