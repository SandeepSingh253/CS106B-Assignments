/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
//playracegamemain
 
#include <iostream>
#include <cstdlib>
#include "gboggle.h"
#include "graphics.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* user made data type */
struct position{
	int r;
	int c;
};

/* global variables */

Grid<char> board;
Set<string> usedWords;
Lexicon english("EnglishWords.dat");


/* Constants */
const int MINIMUN_WORD_LENGTH=4;
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int STANDARD_CUBES_SIZE=16;
const int BIG_CUBES_SIZE=25;

const string STANDARD_CUBES[STANDARD_CUBES_SIZE]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[BIG_CUBES_SIZE]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void selectBoardType();
void inputCharForBoard();
void labelCubes(string latters="");
void randomizeVector(Vector<string> &vec);
void play();
void humanTurn();
bool isWordOnBoard(string str,Vector< position > &usedChar);
void highLightOnBoard(Vector<position> &positions);
bool isOnBoardBackTrack(string input,Grid<char> &board,position lastPos,Vector<position> &usedChar);
bool validSelection(position lastPos,position currentPos,Vector<position> &usedChar);
void toUpperStr(string &str);
void computerTurn();
void searchAllOnBoard(int min);
bool searchOnBoardBackTrack(string word,position lastPos,int min,Vector<position> &usedChar);


/* Main program */

int main() {
   initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   welcome();
   giveInstructions();
   selectBoardType();
   inputCharForBoard();
   string ans;
   humanTurn();
   computerTurn();
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

/*
 * Function: selectBoardType
 * Usage: selectBoardType();
 * --------------------------
 * Prompts user to select the type of board to play 4X4 or 5X5.
 */
void selectBoardType(){
	cout<<"What kind of borad you want to play on?"<<endl<<
		  "1. 4X4 Boogle"<<endl<<
		  "2. 5X5 Big Boogle"<<endl;
	int opt=0;
	while(true){
		opt = getInteger("Enter option 1 or 2: ");
		if(opt==1 || opt==2)  break;
		cout<<"Please chose between 1 or 2 "<<endl;
	}

	if(opt==1){
		drawBoard(4,4);
		board.resize(4,4);
	}else{
		drawBoard(5,5);
		board.resize(5,5);
	}
}
/*
*Function: inputCharForBoard
*Usage: inputCharForBoard();
*----------------------------
* takes input from user for the cubes.
*/
void inputCharForBoard(){
	cout<<"Do you want to set-up the letters on the cubes by yourself? "<<endl;
	string ans;
	while(true){
		ans= getLine();
		if(ans=="Yes" || ans=="yes" || ans=="No" || ans=="no" )break;
		cout<<"??";
	}
	if(ans=="Yes" || ans=="yes"){
		string latters;
		while(true){	
			latters =getLine("Enter the letter without space for each cube from top-right to bottom left :");
			if(latters.size()>=(board.numCols()*board.numRows()))break;
			cout<<"Please enter all the "<<board.numCols()*board.numRows()<<" latters at once"<<endl;
		}
		labelCubes(latters);
	}else{
		labelCubes();
	}

}

/*
*Function: labelCubes
*Usage: labelCubes(string latters);
*----------------------------
*labes the cube as inputed by user if not inputed
*labels cube by using random characters from BIG_BOGGLE_CUBES or STANDARD_CUBE.
*/
void labelCubes(string latters){
	toUpperStr(latters);
	if(!latters.empty()){
		int num=0;
		for(int i=0;i<board.numRows();i++){
			for(int j=0;j<board.numCols();j++){
				board[i][j]=latters[num];
				labelCube(i,j, latters[num]);
				num++;
			}
		}
	}else{
		string latters;
		Vector<string> dice;
		if(board.numCols()*board.numRows()==STANDARD_CUBES_SIZE){
			for(int i=0;i<board.numCols()*board.numRows();i++){
				dice.add(STANDARD_CUBES[i]);
			}
		}else{
			for(int i=0;i<board.numCols()*board.numRows();i++){
				dice.add(BIG_BOGGLE_CUBES[i]);
			}
		}
		randomizeVector(dice);
		for(int i=0;i<board.numCols()*board.numRows();i++){
			string alphabates=dice[i];
			latters+=alphabates[randomInteger(0,alphabates.size()-1)];
		}
		labelCubes(latters);
	}
}

/*
*Function: randomizeVector
*Usage: randomizeVector(Vector<string> &vec);
*----------------------------------------------
*Helper funtion to randomize the vecor passed by refernce.
*/
void randomizeVector(Vector<string> &vec){
	int r=0;
	for (int i = 0; i < vec.size(); i++) {
		r=randomInteger(i,vec.size()-1);
		string str=vec[i];
		vec[i]=vec[r];
		vec[r]=str;
	}
}


/*
*Function: humanTurn
*Usage: humanTurn();
*--------------------
*takes inpute from user and if
*big enough, is a word, not already used and is present on board,
*records it for player.
*
*/
void humanTurn(){
	string input;
	cout<<"Enter the words, or hit enter to pass turn."<<endl;
	while(true){
		input=getLine();
		toUpperStr(input);
		if(input=="")return;
		
		//continue if size too small.
		if(input.size()<MINIMUN_WORD_LENGTH){
			cout<<"Word too small, should be atleast 4 letters long."<<endl;
			continue;
		}
		//contine if no such word exist.
		if(!english.contains(input)){
			cout<<"There is no such word."<<endl;
			continue;
		}
		//continue if word already used.
		if(usedWords.contains(input)){
			cout<<"Word is already used."<<endl;
			continue;
		}

		Vector< position > pos;
		//cheack weither the word can be made on board.
		if(!isWordOnBoard(input,pos)){
			cout<<"Word is not on the board."<<endl;
			continue;
		}
		highLightOnBoard(pos);
		usedWords.add(input);
		recordWordForPlayer(input,HUMAN);
		cout<<"Enter next word, or hit enter to pass turn."<<endl;
		if(input.size()==0)break;
	}
}

/*
*Function: highLightOnBoard
*Usage: highLightOnBoard(Vector<position> &positions);
*--------------------
*Highlights the passed positions of charater on boards for 500ms.
*
*/
void highLightOnBoard(Vector<position> &positions){
	//flags every character on 
	foreach(position pos in positions){
		highlightCube(pos.r, pos.c, true);
	}
	pause(500);
	//flags every charater off
	foreach(position pos in positions){
		highlightCube(pos.r, pos.c, false);
	}
	
}

/*
*Function: isWordOnBoard
*Usage: isWordOnBoard(string str,Vector< position > &usedChar);
*--------------------
*wrapper function for isOnBoardBackTrack
*finds the string on the board if present on board adds the positions 
*of character to the usedChar.
*
*/
bool isWordOnBoard(string str,Vector< position > &usedChar){
	usedChar.clear();
	toUpperStr(str);
	position pos;
	pos.c=-1;
	pos.r=-1;
	return isOnBoardBackTrack(str,board,pos,usedChar);
}

/*
*Function: isOnBoardBackTrack
*Usage: isOnBoardBackTrack(string input,Grid<char> &board,position lastPos,Vector<position> &usedChar);
*--------------------
*checks weather the inputed word in on the board
*if it is on board it returns true and adds its position as data type position 
*in vector usedChar by reference.
*
*/
bool isOnBoardBackTrack(string input,Grid<char> &board,position lastPos,Vector<position> &usedChar){
	if(input==""){
		return true;
	}else{
		for(int i=0;i<board.numRows();i++){
			for(int j=0;j<board.numCols();j++){
				if(board[i][j]==input[0]){
					position currentPos;
					currentPos.r=i;
					currentPos.c=j;
					if(validSelection(lastPos,currentPos,usedChar)){
						position pos;
						pos.r=i;
						pos.c=j;
						usedChar.add(pos);
						if(isOnBoardBackTrack(input.substr(1),board,pos,usedChar)) return true;
						usedChar.removeAt(usedChar.size()-1);
					}
				}
			}
		}
	}
	return false;
}

/*
*Function: validSelection
*Usage: validSelection(position lastPos,position currentPos,Vector<position> &usedChar);
*--------------------
*checks weather current position, passesd as input is adjacent
*or touching the last position on the board, and makes sure the charater
*is not already used.
*Values -1 tells that the charater is firt character of word so its okay to pick.
*
*/
bool validSelection(position lastPos,position currentPos,Vector<position> &usedChar){
	//sentinal value -1 for 1st character of the word
	if(lastPos.c==-1 && lastPos.r==-1)return true;

	//cheking if the character is already used
	foreach(position pos in usedChar){
		if(pos.r==currentPos.r && pos.c==currentPos.c ) return false;
	}
	//cheking for vertically or horizontally adjacent
	if((lastPos.r==currentPos.r && abs(lastPos.c-currentPos.c)==1) || (lastPos.c==currentPos.c && abs(lastPos.r-currentPos.r)==1)) return true;
	
	//cheking for diagonally adjacent
	if(abs(lastPos.c-currentPos.c)==1 && abs(lastPos.r-currentPos.r)==1) return true;
	return false;
}

/*
*Function: computerTurn
*Usage: computerTurn();
*--------------------
*finds all the possible words on board and record
*all the unused for computer.
*/
void computerTurn(){
	int minLength=MINIMUN_WORD_LENGTH;
	searchAllOnBoard(minLength);
}

/*
*Function: searchAllOnBoard
*Usage: searchAllOnBoard(int min);
*--------------------
*wrapper funtioin for backtraking search.
*passes -1 as sentinal values for first charaters as they 
*are not supposed to be connected to any other charater on board 
*usedChar stores characters used on board while making a word.
*/
void searchAllOnBoard(int min){
	cout<<"searchAllOnBoard"<<endl;
	position lastChar;
	lastChar.c=-1;
	lastChar.r=-1;
	string word="";
	Vector<position> usedChar;
	searchOnBoardBackTrack(word,lastChar,min,usedChar);
}

/*
*Function: searchOnBoardBackTrack
*Usage: searchOnBoardBackTrack(string word,position lastPos,int min,Vector<position> &usedChar);
*--------------------
*back tracks all the possible words on the board 
*and records all unused words for computer.
*/
bool searchOnBoardBackTrack(string word,position lastPos,int min,Vector<position> &usedChar){
	if(word.size()>=2 && !english.containsPrefix(word)){
		return false;
	}
	for(int i=0;i<board.numRows();i++){
		for(int j=0;j<board.numCols();j++){
				char ch=board[i][j];
				position currentPos;
				currentPos.r=i;
				currentPos.c=j;
				if(!validSelection(lastPos,currentPos,usedChar)){				
					continue;
				}
				string newWord=word;
				newWord+=ch;
				usedChar.add(currentPos);
				if(newWord.size()>=min && english.contains(newWord) && !usedWords.contains(newWord)){
					recordWordForPlayer(newWord, COMPUTER);
					usedWords.add(newWord);
				}
				searchOnBoardBackTrack(newWord,currentPos,min,usedChar);
				usedChar.removeAt(usedChar.size()-1);
		}
	}
	return false;

}

/*
*Function: toUpperStr
*Usage: toUpperStr(string & str);
*--------------------
* helper funtion to make each character in the input string
* capital.
*/
void toUpperStr(string & str){
	string s;
	for(int i =0;i<str.size();i++){
		char ch=str[i];
		s+=(char)toupper(ch);
	}
	str=s;	
}