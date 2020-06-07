/*
 * QuickUnion.h
 *
 *  Created on: Jan 3, 2017
 *      Author: Marcel A. Pratikto
 *
 *  A method for quicker Union() function
 *  but Find() is slower
 */

#ifndef QUICKUNION_H_
#define QUICKUNION_H_

class QuickUnion {
private:
	int Num;
	int *ID;
	int FindRoot(int child);
public:
	QuickUnion(int num);
	~QuickUnion();
	bool Connected(int p, int q);
	void Union(int p, int q);
	void Print();
};

#endif /* QUICKUNION_H_ */
