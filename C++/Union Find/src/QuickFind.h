/*
 * UF.h
 *
 *  Created on: Jan 2, 2017
 *      Author: Marcel A. Pratikto
 *
 *  A method for quicker Find function: Connected()
 *  but the Union() is slow
 */

#ifndef QUICKFIND_H_
#define QUICKFIND_H_

class UF {
private:
	int NumOfObj;
	int *ID;
public:
	UF(int num);
	~UF();
	bool Connected(int Obj1, int Obj2);
	void Union(int Obj1, int Obj2);
};

#endif /* QUICKFIND_H_ */
