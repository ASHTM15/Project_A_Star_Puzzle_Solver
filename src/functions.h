/*
 * functions.h
 *      Author: ashley m
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <vector>
#include <vector>
#include <stack>
#include <unistd.h>
#include <queue>

#include "node.h"

using namespace std;

//functions.h holds functions used in main so that main.cpp doesn't look so messy//

void printPuzzleNodes(node n, int expNodes, int nodesInQ ){
	stack<node> nStack; //stack of nodes
	node val = n; //assign
	//push node to stack
	nStack.push(val);

	//while the parent is not null then push
	while(NULL != val.p){
		val = *val.p;
		nStack.push(val);
	}

	cout << "expanding state" << endl;
	nStack.top().printPuzzle(); //print out the stack
	cout << "\n";

	nStack.pop(); //pop node

	//print stack
	while(1 < nStack.size()){

		cout << "The best state to expand with g(n) = " << nStack.top().costUniform
		<< " and h(n) = " << nStack.top().costHeuristic << " is...\n" ;

		nStack.top().printPuzzle();

		cout << "expanding this node...\n" << endl;
		nStack.pop();
	}

	cout << " \n " << "Goal !!! \n" << endl;

	cout << "The maximum number of nodes in the queue at any one time: " << nodesInQ << ". \n" ;
	cout << "To solve this problem the search algorithm expanded a total of " << expNodes << " nodes \n";

}


//function to find nodes already visited
bool previousNodes(intVec p, vector<node> nTraversed){
	//if(!p.empty()){
		for(long unsigned int j=0; j<nTraversed.size();j++){
			if(nTraversed[j].puzzle == p){
				return true;
			}
		}
		return false;
	//}
}

#endif /* FUNCTIONS_H_ */
