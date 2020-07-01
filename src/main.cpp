//============================================================================
// Name        : Project1_AI
// Author      : Ashley McDaniel
// Version     :
// Description : eight-puzzle solver using uniform-cost search, misplaced tile heuristic, Euclidean distance heuristic
//============================================================================

#include <iostream>
#include <vector>
#include <stack>
#include <unistd.h>
#include <queue>

#include "functions.h"
#include "operators.h"
#include "node.h"
#include "heuristics.h"

using namespace std;

//stores nodes traversed
vector <node> nTraversed;

//queue nodes
priority_queue <node, vector<node>, comparison> findQ;

void solutionFinder(intVec, string);//forward declaration

int main() {
	//int program = 0;
	cout << "Program Beginning" << endl;
	cout << endl;

	//while(program != 999){

	cout << "Hello! Welcome to my eight-puzzle solver." << endl; // prints !!!Hello World!!!

	//starting puzzle values
	int q=1; //1
	int w=0; //2
	int e=3; //3
	int r=4; //4
	int t=2; //5
	int y=6; //6
	int u=7; //7
	int i=5; //8
	int o=8; //9


	cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle." << endl;
	int opt = 0;//holder for puzzle option

	cin >> opt; //user input
	cout << "\n";

	vector <int> user; //userinput
	if(opt==1){
		user.push_back(q);
		user.push_back(w);
		user.push_back(e);
		user.push_back(r);
		user.push_back(t);
		user.push_back(y);
		user.push_back(u);
		user.push_back(i);
		user.push_back(o);
	}
	if( opt == 2){

		cout << "Enter your puzzle: please use a zero to represent the blank/empty space " << endl;
		cout << "Enter first row, please use a space or tabs in between the numbers! " << endl;
		cin >> q >> w >> e;
		cout << "Enter second row, please use a space or tabs in between numbers! " << endl;
		cin >> r >> t >> y;
		cout << "Enter third row, please use a space or tabs in between numbers! " << endl;
		cin >> u >> i >> o;

		user.push_back(q);
		user.push_back(w);
		user.push_back(e);
		user.push_back(r);
		user.push_back(t);
		user.push_back(y);
		user.push_back(u);
		user.push_back(i);
		user.push_back(o);

	}

	intVec puzzleq(3, vector<int>(3)); //puzzle question

	int count = 0; //very important to initialize to 0 otherwise puzzle will not print out correctly

	//now form puzzle w/ j rows and k columns
	for(int j=0; j<3; j++){
		for(int k =0; k<3; k++){
			puzzleq[j][k] = user[count];
			cout << puzzleq[j][k];
			count++;//increment
		}
		cout << endl;//format
	}

	//reset opt
	opt = 0;
	//

	cout << "Enter your choice of algorithm" << endl;
	cout << "[1]: Uniform Cost Search " << endl;
	cout << "[2]: A* with the Misplaced Tile Heuristic " << endl;
	cout << "[3]: A* with the Euclidean Distance Heuristic" << endl;
	cout << endl;

	cin >> opt; //user input

	string choice = " "; //user input info

	if(opt == 1){
		choice = "Uniform";
	}
	else if(opt == 2){
		choice = "Misplaced";
	}
	else if(opt == 3){
		choice = "Euclidean";
	}
	else{
		choice = "Uniform";
	}

	solutionFinder(puzzleq, choice);

	//cout << endl;
	//cout << "Do you want to end the program? Enter [999] to end program or enter any other [number] to continue: " << endl;
	//cin >> program;

	cout << endl;
	//}//while

	cout << "Program Ending" << endl;
	return 0;
}

void solutionFinder(intVec puzzle, string h) {

	int expNodes;
	long unsigned int nodesInQ = 0; //max

	node onNode(puzzle);
	expNodes= 0;	//expanded node

	nTraversed.push_back(onNode);
	findQ.push(onNode);

	if(h == "Euclidean"){
		cout << "Using Euclidean Distance Heuristic \n" << endl;
	}

	if(h == "Misplaced"){
		cout << "Using Misplaced Tile Heuristic \n" << endl;
	}


	while(findQ.size() > 0){//while queue is not empty

		node* n ;

		n = new node(findQ.top());

		if(goalState == findQ.top().puzzle){

			printPuzzleNodes(findQ.top(), nodesInQ, expNodes);
			break;
		}
		else{

			nTraversed.push_back(findQ.top());
			if(nodesInQ < findQ.size()){
				nodesInQ = findQ.size();

			}

			findQ.pop();

			//name guide: n = node r = right l=left u=up d=down

			expNodes++;
			node* n_u = new node(shiftUp(n->puzzle), (n->costUniform + 1));
			node* n_d = new node(shiftDown(n->puzzle), (n->costUniform + 1));
			node* n_l = new node(shiftLeft(n->puzzle), (n->costUniform + 1));
			node* n_r = new node(shiftRight(n->puzzle), (n->costUniform + 1));

			if("Euclidean" == h){
				n_r->costHeuristic = euclideanDistH(n_r->puzzle);
				n_u->costHeuristic = euclideanDistH(n_u->puzzle);
				n_l->costHeuristic = euclideanDistH(n_l->puzzle);
				n_d->costHeuristic = euclideanDistH(n_d->puzzle);
			}
			if("Misplaced" == h ){
				n_u->costHeuristic = misplacedTileH(n_u->puzzle);
				n_d->costHeuristic = misplacedTileH(n_d->puzzle);
				n_r->costHeuristic = misplacedTileH(n_r->puzzle);
				n_l->costHeuristic = misplacedTileH(n_l->puzzle);

			}

			n_l->sumCost = n_l->costHeuristic + n_l->costUniform;
			n_r->sumCost = n_r->costHeuristic + n_r->costUniform;
			n_u->sumCost = n_u->costHeuristic + n_u->costUniform;
			n_d->sumCost = n_d->costHeuristic + n_d->costUniform;

			if(!previousNodes(n_r->puzzle, nTraversed)){
				n->c0 = n_r;//assign child
				n_r->p = n;//set to parent
				findQ.push(*n_r);
			}

			if(!previousNodes(n_l->puzzle, nTraversed)){
				n->c1 = n_l;
				n_l->p = n;
				findQ.push(*n_l);
			}

			if(!previousNodes(n_u->puzzle,nTraversed)){
				n->c2 = n_u;
				n_u->p = n;
				findQ.push(*n_u);
			}

			if(!previousNodes(n_d->puzzle,nTraversed)){
				n->c3 = n_d;
				n_d->p = n;
				findQ.push(*n_d);
			}

		}
	}
}
