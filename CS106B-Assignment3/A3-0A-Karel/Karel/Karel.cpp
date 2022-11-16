/* File: Karel.cpp
 *
 * A program that finds out how many paths home Karel can take.
 */
#include <iostream>
#include "console.h"
using namespace std;

/* Function: numPathsHome(int street, int avenue);
 * Usage: cout << numPathsHome(3, 2) << endl; // Prints 3
 * =================================================================
 * Returns how many paths home Karel can take from (street, avenue)
 * back to (1, 1).
 */
int numPathsHome(int street, int avenue);

int main() {
	cout<<"for street 1 avenue 1 , "<<numPathsHome(1,1)<<endl;
	cout<<"for street 2 avenue 2 , "<<numPathsHome(2,2)<<endl;
	cout<<"for street 3 avenue 5 , "<<numPathsHome(3,5)<<endl;
	cout<<"for street 2 avenue 3 , "<<numPathsHome(2,3)<<endl;
	cout<<"for street 5 avenue 3 , "<<numPathsHome(5,3)<<endl;
	cout<<"for street 6 avenue 3 , "<<numPathsHome(6,3)<<endl;
	return 0;
}

int numPathsHome(int street, int avenue) {
	if(street==1 || avenue==1)
		return 1;

	return numPathsHome(street-1,avenue)+numPathsHome(street,avenue-1);
	
}

