//
//  main.cpp
//  path
//  全覆盖规划，按照规定的方向，右、下、左、上进行覆盖，不走重复走过的路径。
//  -1 为障碍物
//  Created by mjy on 17-12-6.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include <iostream>
#include <vector>
#define SIZE_M 6
#define SIZE_N 6

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3


using namespace std;

// vector<vector<int>> grid;
// grid[i][j] == 0 ; unvisited
// grid[i][j] == -1 ; object-obstacle
// grid[i][j] == 1; visited

const static int Obs=-1;
const static int unVisited=0;
const static int Visited=1;



// 无障碍物， 覆盖

struct Node{
    int row;
    int col;
    int state=unVisited;
    int dir;
    void print(){
        cout<< "node("<<row<<","<<col<<")"<<endl;
    }
};

void printpath(vector<vector<int> >  & grid){
    cout<<"----map & path----"<<endl;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            cout<< grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

void addpath(vector<Node> path, int i, int j){
    Node node;
    node.col=i;
    node.row=j;
    path.push_back(node);
}

Node getNext(Node node, int dir){
    Node nextNode;
    switch (dir) {
        case RIGHT:{
            nextNode.col=node.col+1;
            nextNode.row=node.row;
            break;
        }
        case DOWN:{
            nextNode.col=node.col;
            nextNode.row=node.row+1;
            break;
        }
        case LEFT:{
            nextNode.col=node.col-1;
            nextNode.row=node.row;
            break;
        }
        case UP:{
            nextNode.col=node.col;
            nextNode.row=node.row-1;
            break;
        }
        default:
            cout<<"no direct"<<endl;
            break;
    }
    return nextNode;
}

bool checkUnvisited(Node node, vector<vector<int> > &grid){
    if (grid[node.row][node.col] == unVisited) return true;
    else return false;
    //if (node.state == unVisited) return true;
    //else return false;

}
bool checkObs(Node node,vector<vector<int> > & grid){
    if (grid[node.row][node.col] == Obs) return false;
    else return true;
}

bool reachGoal(Node node1, Node node2){
    if (node1.col==node2.col && node1.row == node2.row)
        return true;
    else
        return false;
}

bool checkRange(Node node,vector<vector<int> > & grid){
    if (node.col < int(grid[0].size()) && node.row < int(grid.size()) && node.col >=0 && node.row >= 0)
        return true;
    else
        return false;
}
        


vector< Node > MinOverlap(vector<vector<int> > & grid){
    vector <Node> path;
    //int cols = int(grid[0].size());
    //int rows = int(grid.size());
    
    int PathStep=1;
    int dirlist[5]={RIGHT,DOWN, LEFT,UP ,-1};
    
    //ADD START
    Node start;
    start.col =0;
    start.row =0;
    start.dir= dirlist[0]; // start right
    start.state= Visited;
    grid[start.row][start.col]=PathStep;
    
    //ADD GOAL
    Node goal;
    goal.col =6;
    goal.row =6;
    goal.state= unVisited;
    //ADD CURRENT
    
    Node curPos=start;
    Node tmpNode;
    int curDir= 0;
    
    int count=0;
    int count_max=100;
    int TryTurn=4;
   
    while(!reachGoal(curPos,goal) && checkRange(curPos,grid) && count < count_max){
        while(curDir != -1 && checkRange(curPos,grid) && count < count_max){
            tmpNode= getNext(curPos,curDir);
            if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                curPos=tmpNode;
                PathStep++;
                curPos.state= Visited;
                grid[curPos.row][curPos.col]= PathStep;
                printpath(grid);
                TryTurn=4;
            }
            else{
                curDir= (curDir+1)%4;
                TryTurn--;
                cout<<"change direct to"<<curDir<<endl;
                if( !TryTurn){
                    cout<<"deadlock"<<endl;
                    return path;
                }
                
            }
            count++;
        }
    }

   
    return path;
}


int main(int argc, const char * argv[]){
    vector<vector <int> > grid(6,vector<int>(6));
  
    int map[SIZE_M][SIZE_N]={
        0,0,0,0,0,0,
        0,0,-1,0,0,0,
        0,0,-1,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0};
   
    
    int cols = SIZE_M;
    int rows = SIZE_N;
    for(int i=0; i < cols; i++){
        for(int j=0; j < rows; j++){
            grid[i][j]=map[i][j];
        }
    }
    
    
    
    //printpath(grid);
    
    MinOverlap(grid);
    
    printpath(grid);
    
    return 0;
}


