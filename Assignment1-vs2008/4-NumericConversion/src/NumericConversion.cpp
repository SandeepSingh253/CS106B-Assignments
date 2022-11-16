/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
int toPower(int x,int n);

/* Main program */

int main() {

	string s= "5342";
	int x=stringToInt(s);
	cout
		<<stringToInt("-34213");
	
   return 0;
}

string intToString(int n){
	if(n<10&&n>=0){
		return string()+(char)(n%10+(int)'0');
	}
	if(n<0){
		return "-"+intToString(-1*n);
	}
	return intToString(n/10)+string()+(char)(n%10+(int)'0');
}

int stringToInt(string str){
	if(str.at(0)=='-'){
		return -1*stringToInt(str.substr(1));
	}
	if(str.length()==1){
		return ((int)str[0]-(int)'0');
	}
	return ( (int)str[0]-(int)'0' )*( toPower(10,str.length()-1) )+ stringToInt(str.substr(1));
}

int toPower(int x,int n){
	int ans=1;
	for(int i=0;i<n;i++){
		ans*=x;
	}
	return ans;
}