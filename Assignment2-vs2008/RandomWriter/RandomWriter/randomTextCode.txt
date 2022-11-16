/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "error.h"
using namespace std;

const int length=2000;
int order=0; 

typedef Map<string , Vector<char> > frequencyMap;

string promptUserForFile(ifstream & infile, string prompt);
void generateMarkovModel(ifstream & infile ,frequencyMap & frequencies ,int order);
string higestFrequencyKey(frequencyMap);
void generateText(string initialSeed,frequencyMap frequencies);

void printMap(frequencyMap m);

int main() {
	ifstream infile;
	
	string seed,initialSeed;
	frequencyMap frequencies;

	promptUserForFile(infile,"Enter the name of the file: ");

	cout<<"Enter Order btw 1-10"<<endl;
	cin>>order;
	
	generateMarkovModel(infile,frequencies, order);
	
	//printMap(frequencies);

	initialSeed=higestFrequencyKey(frequencies);

	generateText(initialSeed,frequencies);

	return 0;
}

string promptUserForFile(ifstream & infile, string prompt) {
	 while (true) {
		 cout << prompt;
		 string filename;
		 getline(cin, filename);
		 infile.open(filename.c_str());
		 if (!infile.fail()) return filename;
		 infile.clear();
		 cout << "Unable to open that file. Try again." << endl;
		 if (prompt == "") prompt = "Input file: ";
	 }
}

void generateMarkovModel(ifstream & infile ,frequencyMap & frequencies ,int order){
	string seed="";
	for(int i =0;i<order;i++){
		seed+=(char)infile.get();
	}
	char ch;
	int read=0;
	while (infile.get(ch)) {
		frequencies[seed].add(ch);
		seed=seed.substr(1)+ch;
		if(read==2000) break;
	}

}



string higestFrequencyKey(frequencyMap frequencies){
	string seed;
	Vector<char> temp;
	foreach (string key in frequencies) {
		if(frequencies[key].size()>temp.size()){
			seed=key;
			temp=frequencies[key];
		}
	}
	return seed;

}

void generateText(string initialSeed,frequencyMap frequencies){
	string seed=initialSeed;
	int read=order;
	char nextChar;
	cout<<seed;
	while(read!=length){
		if(frequencies.containsKey(seed)){
			nextChar=frequencies[seed].get(randomInteger(0,frequencies[seed].size()-1));
		}else{
			return;
		}
		cout<<nextChar;
		seed=seed.substr(1)+nextChar;
		read++;
	}
}

void printMap(frequencyMap m){
	foreach(string key in m){
		cout<<key<<endl;
	}
}