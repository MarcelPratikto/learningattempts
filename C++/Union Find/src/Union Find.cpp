//============================================================================
// Name        : Union.cpp
// Author      : Marcel Pratikto
// Version     :
// Copyright   : 
// Description : Learn about algorithms for Union(connect p & q) and Find(check if they are connected)
//============================================================================

#include <iostream>		//cin, cout, getchar
#include <fstream>		//ifstream, ofstream, fstream
#include <cstdlib>		//exit
#include <string>		//string
#include <sstream>		//stringstream

#include "QuickFind.h"
#include "QuickUnion.h"
#include "WeightedQuickUnion.h"
using namespace std;

// function prototypes
int ConvertToInt(string Text);

int main(int argc, char* argv[]){
	// open file
	//ifstream TextFile(argv[1]);
	ifstream TextFile("a.txt");
	// if file could not be opened
	if (!TextFile){
		cerr << "Failed to open file." << endl;
		exit(1);
	}

	// keep track of text in file
	string Text;
	// read in the first argument in the file (number of objects)
	TextFile >> Text; // operator >> ignores whitespaces and newlines
	int Num = ConvertToInt(Text);
	cout << "Number of objects in file: " << Num << "\n";

	// Make an object of class UF
	WeightedQuickUnion WQU(Num);

	// Connected() to check if the pair is connected
	// Union() to connect the pair and print out pair
	for (int iii = 0; iii < Num; ++iii){
		TextFile >> Text;
		int P = ConvertToInt(Text);
		TextFile >> Text;
		int Q = ConvertToInt(Text);
		// if not connected, connect the pair
		if (!WQU.Connected(P, Q)){
			WQU.Union(P, Q);
		}
	}

	cout << "Components: \n";
	WQU.Print();
	// end program
	cout << "\nPress ENTER to exit...";
	getchar();
	return 0;
}

int ConvertToInt(string Text){
	stringstream ConvertText(Text);
	//ConvertText.str(Text) also works if not using constructor
	int Integer;
	// convert from stringstream to int, if failed default to 0
	if (!(ConvertText >> Integer))
		Integer = 0;
	return Integer;
}
