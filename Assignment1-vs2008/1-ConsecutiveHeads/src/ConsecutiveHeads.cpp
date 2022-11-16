/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "random.h"
using namespace std;

enum coinToss{head, tail };

int flipCoin();
string tossToString(int toss);
int main() {
   int consecutiveHeadCount=0;
   int totalFlips=0;
   while(1){

	if(consecutiveHeadCount==3){
		break;
	}

	int toss= flipCoin();
	cout<<tossToString(toss)<<endl;

	if(toss==head){
		consecutiveHeadCount++;
	}
	
	if(toss==tail){
		consecutiveHeadCount=0;
	}
	totalFlips++;
   }
   cout<<"it took "<<totalFlips<<" flips to get 3 consicutive heads.";
   return 0;
}

int flipCoin() {
 if (randomChance(0.50)) {
	return head;
 } else {
	return tail;
 }
}

string tossToString(int toss){

	 switch(toss){
		case(head):return "Heads";
		case(tail):return "Tails";
		default: return "??";
	 }

}
