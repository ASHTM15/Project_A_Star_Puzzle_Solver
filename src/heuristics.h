/*
 * heuristics.h
 * Author: ashley m
 */

#ifndef HEURISTICS_H_
#define HEURISTICS_H_

#include <iostream>
#include <vector>
#include <math.h>
#include "node.h"

using namespace std;

const intVec goalState = {{1,2,3},{4,5,6},{7,8,0}};

//now do check with misplaced heuristic puzzle
int misplacedTileH(intVec puzzle){
	int mtiles = 0; //misplaced tiles counter
	//n rows w/ m columns in puzzle
	for(int n=0;n<3;n++){
		for(int m=0;m<3;m++){
			if(puzzle[n][m] == 0){
				continue;
				//the zero is found
			}
			if(puzzle[n][m] != goalState[n][m]){
				//current puzzle does not equal the goal state
				//there is a misplaced tile so increment counter
				mtiles ++;
			}
		}
	}
	return mtiles; //return the counter of misplaced tiles
}

int euclideanDistH(intVec puzzle){
	//formula: square root --> ((a1-b1)^2 + (a2-b2)^2)
	int counter = 0 ;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(puzzle[i][j] == 0){
				continue;
			}
			if(puzzle[i][j] != goalState[i][j]){
				int n=0;
				int m=0;

				for(int y=0;y<3;y++){
					for(int z=0;z<3;z++){
						if(goalState[y][z] == puzzle[i][j]){
							n = y;
							m = z;
						}
					}
				}
				n = pow(n-m,2);
				m = pow(i-j,2);
				while(n != 0 || m != 0){
					if(n<0){
						counter++;
						n++;
					}
					if(n>0){
						counter++;
						n--;
					}
					if(m<0){
						counter++;
						m++;
					}
					if(m>0){
						counter++;
						m--;
					}
				}
				//don't need this can omit for running time purposes
				//counter = sqrt(counter);
			}
		}
	}
	return counter;
}
#endif /* HEURISTICS_H_ */
