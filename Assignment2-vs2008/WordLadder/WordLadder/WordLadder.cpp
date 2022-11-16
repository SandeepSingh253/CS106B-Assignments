/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

typedef Vector<string> Ladder; 
Set<string> usedWord; 
Lexicon english("EnglishWords.dat");

void printLadder(Ladder ladder);
bool isWord(string newWord);
Ladder findShortestLadder(string start,string end);

int main() {
	string start, end;
	Ladder ladder;

	start=getLine("Enter the starting word : ");
	end=getLine("Enter the ending word : ");

	ladder=findShortestLadder(start,end);

	if(!ladder.isEmpty()){
		cout<<"The shortest Ladder from "<<start<<" to "<<end<<" is : ";  
		printLadder(ladder);
	}else{
		cout<<"No such ladder exist";
	}

	return 0;
}

Ladder findShortestLadder(string start,string end){
	usedWord.add(start);
	Queue<Ladder> ladderQueue;
	
	Ladder ladder;
	ladder.add(start);
	ladderQueue.enqueue(ladder);
	while(!ladderQueue.isEmpty()){

		ladder=ladderQueue.peek();
		ladderQueue.dequeue();

		if(ladder[ladder.size()-1]==end){
			return ladder;
		}
		
		for(int i=0;i<ladder.get(ladder.size()-1).length();i++){
			for(int j='a';j<='z';j++){
				string newWord=ladder[ladder.size()-1];
				newWord.at(i)=(char)j;
				
				if(isWord(newWord) && !usedWord.contains(newWord)){
					Ladder newLadder=ladder;
					newLadder.add(newWord);
				
					ladderQueue.enqueue(newLadder);
					usedWord.add(newWord);
				}
			}
		}
	}
	usedWord.clear();
	ladder.clear();
	return ladder;

}

bool isWord(string word){
	return english.contains(word);
}

void printLadder(Ladder ladder){
	for (int i = 0; i < ladder.size(); i++) {
		cout<<ladder[i]<<" ";
	}
	cout<<endl;
}

