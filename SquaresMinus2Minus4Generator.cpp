#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

string getAutomatonName(int i, int j, int k) {
	return("squareChecker"+to_string(i)+"_"+to_string(j)+"_"+to_string(k));
}

string getRStateName(int a, int c1, int c2, int e) {
	return ("r_"+to_string(a)+"_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(e));
}

string getStateName(int a, int b, int c1, int c2, int e) {
	return ("q_"+to_string(a)+"_"+to_string(b)+"_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(e));
}

void addRStateBTransitions(int twoNumber, string name, int last4, int c1, int c2, int guess) {
	int i = twoNumber;
	int lowerBit = (i+ c2 + last4) % 2;
	int higherBit = (i + c1) % 2;
	int lowerCarry = (i + c2 + last4) / 2;
	int higherCarry = (i + c1) / 2;	
	if (lowerCarry == guess) {
		if (higherCarry == 2)
			cout << "(" << name << " b" << higherBit << lowerBit << " s2)\n";
		if (higherCarry == 3)
			cout << "(" << name << " b" << higherBit << lowerBit << " s3)\n";
	}
}

void addSingleStateBTransitions(int twoNumber, int fourNumber, string name, int last4, int next4, int c1, int c2, int guess) {
	if(next4 != fourNumber)
		return;
	for(int i = 0; i <= twoNumber; i++) {
		int lowerBit = (i+ c2 + next4) % 2;
		int higherBit = (i + c1) % 2;
		int lowerCarry = (i + c2 + next4) / 2;
		int higherCarry = (i + c1) / 2;	
		cout << "(" << name << " b" << higherBit << lowerBit << " " << getRStateName(last4, higherCarry, lowerCarry, guess)<<")\n";
	}
}

void addSingleStateTransitions(int twoNumber, int fourNumber, string name, int last4, int next4, int c1, int c2, int guess) {
	for(int i = 0; i <= twoNumber; i++) {
		for (int j = 0; j <= fourNumber; j++) {		
			int lowerBit = (i+ c2 + next4) % 2;
			int higherBit = (i + j + c1) % 2;
			int lowerCarry = (i + c2 + next4) / 2;
			int higherCarry = (i + j + c1) / 2;	
			cout << "(" << name << " a" << higherBit << lowerBit << " " << getStateName(last4, j, higherCarry, lowerCarry, guess)<<")\n";
		}
	}
}

void addAllStateTransitions(int twoNumber, int fourNumber, int guessedCarry) {
	for(int i = 0; i <= fourNumber; i++) 
		for (int j = 0; j <= fourNumber; j++)
			for (int k = 0; k < twoNumber+fourNumber; k++)	
				for (int l = 0; l < twoNumber+fourNumber; l++) {
					addSingleStateTransitions(twoNumber, fourNumber, getStateName(i,j,k,l,guessedCarry), i, j, k, l, guessedCarry);
					addSingleStateBTransitions(twoNumber, fourNumber, getStateName(i,j,k,l,guessedCarry), i, j, k, l, guessedCarry);
					cout << endl;
				}
	for(int i = 0; i <= fourNumber; i++) 
		for (int k = 0; k < twoNumber+fourNumber; k++)	
			for (int l = 0; l < twoNumber+fourNumber; l++) {
				addRStateBTransitions(twoNumber, getRStateName(i,k,l,guessedCarry), i, k, l, guessedCarry);
			}
	cout <<"(s2 c t)\n(s3 d t)\n(t d acc)";
}

void addQTransitions(int twoNumber, int fourNumber, int guessedCarry) {
	for(int i = 0; i <= twoNumber; i++) {
		for (int j = 0; j <= fourNumber; j++) {		
			for (int k = 0; k <= fourNumber; k++) {
				int lowerBit = (i+j) % 2;
				int higherBit = (guessedCarry + i + k) % 2;
				int lowerCarry = (i+j) / 2;
				int higherCarry = (guessedCarry + i + k) / 2;
				cout << "(q a" << higherBit << lowerBit << " " << getStateName(j, k, higherCarry, lowerCarry, guessedCarry)<<")\n";
			}
		}
	}
}

// states are 5-tuples (a,b,c1,c2,e) where a is the last digit of the n-4 guesses
// b is the next guessed n-4 digit
// c1 is the upper carry
// c2 is the lower carry
// e is the guessed middle carry

void createStates(int twoNumber, int fourNumber, int guessedCarry) {
	cout << "states = { q\n";
	for(int i = 0; i <= fourNumber; i++) 
		for (int j = 0; j <= fourNumber; j++)
			for (int k = 0; k < twoNumber+fourNumber; k++)	
				for (int l = 0; l < twoNumber+fourNumber; l++)
					cout << getStateName(i,j,k,l,guessedCarry) <<endl;	
	for(int i = 0; i <= fourNumber; i++) 
		for (int k = 0; k < twoNumber+fourNumber; k++)	
			for (int l = 0; l < twoNumber+fourNumber; l++)
				cout << getRStateName(i,k,l,guessedCarry) <<endl;	
	cout<<"s2 s3 t acc},\n";
}

void createAutomaton (int twoNumber, int fourNumber, int guessedCarry) {
	cout << "FiniteAutomaton "<<getAutomatonName(twoNumber, fourNumber, guessedCarry)<<" = (\n";
	cout << "alphabet = {a00 a01 a10 a11 b00 b01 b10 b11 c d},";
	createStates(twoNumber, fourNumber, guessedCarry);
	cout << "initialStates = {q},\nfinalStates = {acc},\n";
	cout << "transitions = {\n";
	addQTransitions(twoNumber, fourNumber, guessedCarry);
	addAllStateTransitions(twoNumber, fourNumber, guessedCarry);
	cout << "\n}\n";
	cout << ");\n";
}

int main() {
	vector<string> autNames;
	int twoNumber = 4, fourNumber = 3;
	for (int i = 1; i <= twoNumber; i++) {
		for (int j = 0; j <= fourNumber; j++) {
			if (i+j < 3)
				continue;
			for (int k = 0; k < (i + j); k++) {
				createAutomaton(i, j, k);
				autNames.push_back(getAutomatonName(i,j,k));
			}
		}
	}
	cout<<endl<<endl<<"FiniteAutomaton finalAut = intersect(complement("<<autNames.at(0)<<"), complement("<<autNames.at(1)<<"));\n";
	for(int i = 2; i < autNames.size(); i++)
		cout<<"finalAut = intersect(finalAut, complement("<<autNames.at(i)<<"));\n";
	cout<<"finalAut = removeUnreachable(complement(finalAut));";
}