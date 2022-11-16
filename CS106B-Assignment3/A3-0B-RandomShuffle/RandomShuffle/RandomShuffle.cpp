/* File: RandomShuffle.cpp
 *
 * A program that uses recursion to randomly scramble the contents of
 * a string.
 */
#include <iostream>
#include <string>
#include "random.h"
#include "console.h"
using namespace std;

/* Function: randomShuffle(string input);
 * Usage: cout << randomShuffle("keith") << endl; // Might get htiek
 * =================================================================
 * Returns a random permutation of the given string.
 */
string randomShuffle(string input);

string removeChar(string str, int x);

int main() {
	
	cout<<randomShuffle("sandeep");
	
	return 0;
}

string randomShuffle(string input) {
	if(input=="")
		return "";
	int randomIndex=randomInteger(0, input.length()-1);
	return string()+input[randomIndex]+randomShuffle( removeChar(input, randomIndex) );
}

string removeChar(string str, int x){
	
	if(x==0)
		return str.substr(1);
	
	return string()+str.substr(0,x)+str.substr(x+1);

}

