/*
 * operators.h
 *      Author: ashley m
 */

#ifndef OPERATORS_H_
#define OPERATORS_H_

#include <iostream>
#include <vector>
#include "node.h"

using namespace std;

intVec switchPoints( int , int , int , int , intVec);//forward

typedef vector<vector<int>> intVec;

intVec shiftDown(intVec puzzle){
	//set variables
	int n = 0;
	int m = 0;
	//the zero should not be in the first row condition
	//if it is then return puzzle
	for(int j=0; j<3;j++){
		if(puzzle[0][j] == 0){//check if zero in first row
			return puzzle; //return puzzle unchanged
		}
	}
	//now must locate point containing zero
	//passed the last condition: no zero in first row
	//we know zero cannot be in first row so start search at second row
	for(int j=1;j<3;j++){//skip first row start at j=1
		for(int k=0; k<3; k++){//column
			if(puzzle[j][k] == 0){
				//the zero is found
				//assign
				n=j;
				m=k;
			}
		}
	}
	return switchPoints(n,m,(n-1),m, puzzle);
}


intVec switchPoints( int x, int y, int i, int j, intVec puzzle){
	int temp; //store point
	temp = puzzle[i][j];
	puzzle[x][y] = temp;//set
	puzzle[i][j] = 0;
	return puzzle;
}

intVec shiftUp(intVec puzzle){
	//set variables
	int n = 0;
	int m = 0;
	//zero cannot be in last row
	//if condition fails and puzzle[2][j] == 0
	for(int j=0; j<3; j++){
		if(puzzle[2][j] == 0){
			return puzzle;//end function return unchanged puzzle
		}
		else{}
	}
	//if the last condition passes and puzzle[j][k] == 0
	for(int j=0;j<2;j++){
		for(int k=0;k<3;k++){
			if(puzzle[j][k] == 0){
				//found the zero
				m = k;//assign
				n = j;//assign
			}
		}
	}
	//swap the points in puzzle
	return switchPoints(n,m,(n+1),m,puzzle);
}

intVec shiftRight(intVec puzzle){
	//should not have zero in leftmost column
	//set variables
	int n = 0;
	int m = 0;
	//if there is zero in the leftmost column then return unchanged puzzle
	//check for zero in leftmost column
	for(int j=0;j<3;j++){
		if(puzzle[j][0] == 0){
			return puzzle;
		}
		else{}
	}
	//now find the point containing zero
	for(int j=0; j<3; j++){
		for(int k=0;k<3;k++){
			if(puzzle[j][k] == 0){
				m=k;
				n=j;
			}
			else{}
		}
	}
	return switchPoints(n,m,n,(m-1), puzzle);
}
intVec shiftLeft(intVec puzzle){
	//should not have zero in rightmost column
	//set variables
	int n = 0;
	int m = 0;
	//if there is zero in the rightmost column then return unchanged puzzle
	//check for zero in rightmost column
	for(int j=0;j<3;j++){
		if(puzzle[j][2] == 0){
			return puzzle;
		}
		else{}
	}
	//now find the point containing zero
	//zero cannot be in column 3 because it is the rightmost
	for(int j=0; j<3; j++){
		for(int k=0; k<2; k++){//only check till k<2
			if(puzzle[j][k] == 0){
				m=k;
				n=j;
			}
			else{}
		}
	}
	return switchPoints(n,m,n,(m+1),puzzle);
}

#endif /* OPERATORS_H_ */
