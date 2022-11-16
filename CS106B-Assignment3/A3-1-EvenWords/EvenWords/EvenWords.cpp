/* File: EvenWords.cpp
 *
 * A program that uses recursion to determine which words are
 * even words.
 */
#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function: isEvenWord(string input);
 * Usage: if (isEvenWord("tattletale")) { ... }
 * ==================================================================
 * Returns whether the given word is an "even word;" that is, whether
 * every letter in the word appears an even number of times.
 */
bool isEvenWord(string word); 
bool eraseFirstAndDup(string &str);
string removeChar(string str, int x);

int main() {
	string str;
	cin>>str;
	if(isEvenWord(str)){
		cout<<str<<"  is a even string"<<endl;
	}else{
		cout<<str<<"  is not a even string"<<endl;
	}
	
	return 0;
}

bool isEvenWord(string word) {
	if(word=="")
		return true;
	
	char first= word[0];
	

	return eraseFirstAndDup(word) && isEvenWord(word);
}

bool eraseFirstAndDup(string &str){
	char first=str[0];
	int index=str.find(first,1);
		
	if(index==string::npos){
		return false;
	}else{
		str=removeChar(str.substr(1),index-1);
		return true;
	}
	
}

string removeChar(string str, int x){
	
	if(x==0)
		return str.substr(1);
	return string()+str.substr(0,x)+str.substr(x+1);

}
