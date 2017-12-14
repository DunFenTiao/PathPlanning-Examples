//
//  coverage.h
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#ifndef __coverage__coverage__
#define __coverage__coverage__

#include <stdio.h>

#include <stdio.h>


#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define SIZE_M 6
#define SIZE_N 6

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define TURNMAX 4


using namespace std;

// vector<vector<int>> grid;
// grid[i][j] == 0 ; unvisited
// grid[i][j] == -1 ; object-obstacle
// grid[i][j] == 1; visited

const static int Obs=-1;
const static int unVisited=0;
const static int Visited=1;
extern int PathStep;
static int dirlist[TURNMAX]={RIGHT,DOWN, LEFT,UP};
//astar
const static int kcost1=10; //直走消耗
const static int kcost2=14; //斜走消耗


struct Node{
    int row;
    int col;
    int step; // step in the path
    void print(){
        cout<< "node("<<row<<","<<col<<")"<<endl;
    }
};

vector< Node > MinOverlap(Node start, vector<vector<int> > & grid);
vector<Node> updateUnVisit(vector<vector<int> > & grid);

Node getNext(Node node, int dir);
Node Nearest(Node curPos, vector<Node> unVisitList);

double distance2N(Node node1,Node node2);

bool checkUnvisited(Node node, vector<vector<int> > &grid);
bool checkObs(Node node,vector<vector<int> > &grid);
bool reachGoal(Node node1, Node node2);
bool checkRange(Node node,vector<vector<int> > &grid);
bool checkFinish(vector<vector<int> > &grid);
bool move(Node &curPos, Node toGo,vector<vector<int> > & grid, vector<Node>& path);

void printPathMap(vector<vector<int> > grid, vector<Node> path);
void printPathNode(vector<Node> path);






#endif /* defined(__coverage__coverage__) */


