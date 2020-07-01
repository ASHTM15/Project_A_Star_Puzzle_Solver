/*
 * node.h
 *      Author: ashley m
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

using namespace std;

typedef vector <vector<int>> intVec; //vector of vectors of integers

//need a struct in order to store puzzles/cost for uniform and heuristic
struct node{

	//set variables and nodes
	//stores costs and initialize
	int costUniform = 0;
	int costHeuristic = 0;//
	//g(n) start to end
	//h(n) node to goal

	//sum of uniform and heuristic costs
	int sumCost = 0;

	//children
	node *c0 = NULL;
	node *c1 = NULL;
	node *c2 = NULL;
	node *c3 = NULL;

	//parent
	node *p = NULL;

	//stores current puzzle
	intVec puzzle;

	node (intVec vec){
			//init
			costUniform=0;
			costHeuristic = 0;

			//set
			puzzle = vec;
		}



	node (const node &vec){
		//assign the new puzzle to current
		puzzle = vec.puzzle;

		//get the current puzzles costs and assign them
		costHeuristic = vec.costHeuristic;
		costUniform = vec.costUniform;

		//get sum
		sumCost = vec.sumCost;

		//get the child/parent
		c0 = vec.c0;
		c1 = vec.c1;
		c2 = vec.c2;
		c3 = vec.c3;
		p = vec.p;
	}

	void operator=(const node &vec){
		//assign puzzle
		puzzle = vec.puzzle;

		//assign costs
		costHeuristic = vec.costHeuristic;
		costUniform = vec.costUniform;

		//get sum
		sumCost = vec.sumCost;

		//get the child/parent
		c0 = vec.c0;
		c1 = vec.c1;
		c2 = vec.c2;
		c3 = vec.c3;
		p = vec.p;
	}

	node (intVec vec, int uniform_cost){
		//assign puzzle
		puzzle = vec;
		//set costs
		costHeuristic = 0;
		costUniform = uniform_cost;
	}

	void printPuzzle(){
		//see puzzle results w/ j rows and z columns
			for(int j=0;j<3;j++){
				for(int z=0;z<3;z++){
					cout << puzzle[j][z]; //print to user
				}
				cout << endl;
			}
		}

};

//we must have a comparison between nodes to find the next node to go to with the least/lesser cost in the queue
struct comparison{
	bool operator()(const node& nleft, const node& nright ){ //node right = nright and node left = nleft
		bool ncomp = (nleft.sumCost > nright.sumCost); //compare nleft and nright
		return ncomp;
	}
};


#endif /* NODE_H_ */
