/*
 * WeightedQuickUnion.h
 *
 *  Created on: Jan 5, 2017
 *      Author: Marcel A. Pratikto
 */

#ifndef WEIGHTEDQUICKUNION_H_
#define WEIGHTEDQUICKUNION_H_

class WeightedQuickUnion {
private:
	int Num;
	int RowSize;
	int ColumnSize;
	int *ID;
	int Access(int row, int column);
	void Link(int BiggerTree, int SmallerTree);
public:
	WeightedQuickUnion(int num);
	~WeightedQuickUnion();
	bool Connected(int p, int q);
	void Union(int p, int q);
	void Print();
};

#endif /* WEIGHTEDQUICKUNION_H_ */
