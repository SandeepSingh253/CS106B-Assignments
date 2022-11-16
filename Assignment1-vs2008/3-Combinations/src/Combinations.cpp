/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
using namespace std;

int size=10; 

string space(int);
int c(int n,int k);

int main() {
   
	for(int i=0;i<size;i++){
	    cout<<space(size-i);
		for(int k=0;k<=i;k++){
			cout<<c(i,k)<<"  ";
		}
		cout<<endl;
	}
   return 0;
}

string space(int s){
	string space="";
	for(int i=0;i<s;i++){
		space+=" ";
	}

	return space;
}

int c(int n,int k){
	if(k==0||k==n){
		return 1;
	}else{
		return c(n-1,k-1)+c(n-1,k);
	}	
}