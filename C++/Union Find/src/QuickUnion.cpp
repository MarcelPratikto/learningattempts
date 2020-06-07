/*
 * QuickUnion.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: Marcel A. Pratikto
 */

#include <iostream>
#include "QuickUnion.h"

QuickUnion::QuickUnion(int num): Num(num) {
	// generate a dynamic array and initialize each value
	ID = new int[Num];
	for (int id = 0; id < Num; ++id)
		ID[id] = id;
}

QuickUnion::~QuickUnion(){ delete[] ID; }

int QuickUnion::FindRoot(int child){
	// if the child is not the same as the parent, keep searching
	// root is found when child == parent (in this case we use ID[child] for parent)
	while (child != ID[child])
		child = ID[child];

	return child;
}

// check to see if p and q are connected
bool QuickUnion::Connected(int p, int q){
	return(FindRoot(p) == FindRoot(q));
}

// set the root of p to the root of q to link
void QuickUnion::Union(int p, int q){
	int RootOfP = FindRoot(p);
	int RootOfQ = FindRoot(q);
	ID[RootOfP] = RootOfQ;
}

void QuickUnion::Print(){
	int *RootOf = new int[Num];

	// Loop through the array to find the root for all the numbers, place in Check[];
	for (int id = 0; id < Num; ++id){
		RootOf[id] = FindRoot(id);
	}
	// TODO
	// Output numbers that have the same root
	for (int CurrentRoot = 0; CurrentRoot < Num; ++CurrentRoot){
		bool InsertNewline = false;
		for (int id = 0; id < Num; ++id){
			if (RootOf[id] == CurrentRoot){
				std::cout << id << " ";
				InsertNewline = true;
			}
		}
		if (InsertNewline)
			std::cout << "\n";
	}

	// always delete dynamic memory before they go out of scope
	delete[] RootOf;
}
