/*
 * WeightedQuickUnion.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Marcel A. Pratikto
 */

#include <iostream>
#include "WeightedQuickUnion.h"

WeightedQuickUnion::WeightedQuickUnion(int num) : Num(num){
	RowSize = 2;
	ColumnSize = Num;
	ID = new int[RowSize * ColumnSize];

	// initialize default value in the array
	for (int i; i < Num; ++i){
		ID[Access(0, i)] = i;	// holds root of ID
		ID[Access(1, i)] = 1;	// holds size of tree
	}
}

WeightedQuickUnion::~WeightedQuickUnion(){
	delete[] ID;
}

int WeightedQuickUnion::Access(int row, int column){
	return (row * ColumnSize + column);
}

bool WeightedQuickUnion::Connected(int p, int q){
	return (ID[Access(0, p)] == ID[Access(0, q)]);	// if the root of p and q are the same
}

void WeightedQuickUnion::Link(int BiggerTree, int SmallerTree){
	// assign the root of the BiggerTree to the SmallerTree
	ID[Access(0, SmallerTree)] = ID[Access(0, BiggerTree)];
	// combine the size of the trees
	int CombinedTreeSize = ID[Access(1, BiggerTree)] + ID[Access(1, SmallerTree)];
	ID[Access(1, SmallerTree)] = CombinedTreeSize;
	ID[Access(1, BiggerTree)] = CombinedTreeSize;
}

void WeightedQuickUnion::Union(int p, int q){
	// link the smaller tree to the bigger one
	if (ID[Access(1, p)] >= ID[Access(1, q)]){	// if p's tree >= q's tree
		Link(p, q);
	}
	else {										// if p's tree < q's tree
		Link(q, p);
	}
}

void WeightedQuickUnion::Print(){
	// cycle through each number. If it is a root, output all values in its tree
	for (int Current = 0; Current < Num; ++Current){
		bool InsertNewline = false;
		for (int i = 0; i < Num; ++i){
			// if ID's root == Current
			if(ID[Access(0, i)] == Current){
				std::cout << i << " ";
				InsertNewline = true;
			}
		}
		// prevent ID that aren't roots from inserting newline
		if (InsertNewline)
			std::cout << "\n";
	}

	std::cout << "\n";
	// print out the root of each ID and its size
	for (int i = 0; i < Num; ++i){
		std::cout << "Root of ID " << i << ": ";
		std::cout << ID[Access(0, i)] << "\n";
		//std::cout << "Size of Tree: ";
		//std::cout << ID[Access(1, i)] << "\n\n";
	}
}
