/*
 * UF.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: Marcel A. Pratikto
 */

#include "QuickFind.h"

#include <iostream>


// constructor
UF::UF(int num) : NumOfObj(num)
{
	ID = new int[NumOfObj];
	// set the ID to their links, since they are not yet connected, each ID is its own link
	// each ID[id] stands for an identifier that determines the linkage
	for (int id = 0; id < NumOfObj; ++id)
		ID[id] = id;
}

// destructor
UF::~UF(){
	delete[] ID;
}

// Connected() to check if the pair is connected
bool UF::Connected(int Obj1, int Obj2){
	return (ID[Obj1] == ID[Obj2]);
}

// Union() to connect the pair
void UF::Union(int Obj1, int Obj2){
	int ID1 = ID[Obj1];
	int ID2 = ID[Obj2];
	// Link Obj1 and its links with Obj2 and its link
	for (int iii = 0; iii < NumOfObj; ++iii){
		if (ID[iii] == ID1)			// if an object is linked with Obj1
			ID[iii] = ID2;			// change its ID[] to link with ID[Obj2]
	}

	std::cout << Obj1 << " is now connected to ";
	for (int iii = 0; iii < NumOfObj; ++iii){
		if (iii == Obj1)
			continue;
		if (ID[iii] == ID[Obj1])
			std::cout << iii << " ";
	}
	std::cout << "\n";
}
