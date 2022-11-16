/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Obenglobish problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "strlib.h"
using namespace std;

string obenglobish(string str);

bool isVowel(char chr);

int main() {
 while (true) {
	string word;
	cout<<"Enter a word:";
	//cin>>word;
	getline(cin,word);
	if (word == "") break;
	string trans = obenglobish(word);
	cout << word << " -> " << trans << endl;
 }
 return 0;
}

string obenglobish(string str){
	string result="";
	char lastChar=' ';
	for(int i=0; i<str.length(); i++ ){

		if(i==str.length()-1){
			result+=str[i];
			break;
		}

		if( ( isVowel(str.at(i)) ) && ( lastChar==' ' || (!isVowel(lastChar)) ) ){
			result+=(string)"ob"+str.at(i);
		}else{
			result+=str.at(i);
		}

		lastChar=str.at(i);
	}
		
	return result;
}

bool isVowel(char ch) {
	if(ch==' ')return false;
	switch (ch) {
		case 'A': case 'E': case 'I': case 'O': case 'U':
		case 'a': case 'e': case 'i': case 'o': case 'u':
		return true;
		default:
		return false;
	}
}