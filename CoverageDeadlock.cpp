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
#include <math.h>
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
static int PathStep=1;
static int dirlist[TURNMAX]={RIGHT,DOWN, LEFT,UP};


// 有障碍物， 覆盖

struct Node{
    int row;
    int col;
    int dir;
    int step;
    void print(){
        cout<< "node("<<row<<","<<col<<")"<<endl;
    }
};

void printPathMap(vector<vector<int> > grid, vector<Node> path){
    cout<<"----map & path----"<<endl;
    vector<vector<int>> PathStepMap= grid;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    for(int i = 0; i < path.size(); i++){
        PathStepMap[path[i].row][path[i].col] = path[i].step;
    }
    
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            cout<< PathStepMap[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    
}

void printMap(vector<vector<int> > grid){
    cout<<"----map ----"<<endl;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            cout<< grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void printPathNode(vector<Node> path){
    cout<<"---- path----"<<endl;
    for(int i = 0; i < path.size() ; i++){
        cout<<path[i].step<<" ("<<path[i].row<<","<<path[i].col<<") ";
    }
    cout<<endl;
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
            break;
    }
    return nextNode;
}

bool checkUnvisited(Node node, vector<vector<int> > &grid){
    if (grid[node.row][node.col] == unVisited) return true;
    else return false;
}
bool checkObs(Node node,vector<vector<int> > & grid){
    if (grid[node.row][node.col] == Obs) return false;
    else return true;
}

bool reachGoal(Node node1, Node node2){
    if (node1.col == node2.col && node1.row == node2.row)
        return true;
    else
        return false;
}

bool checkRange(Node node,vector<vector<int> > & grid){
    if (node.col < int(grid[0].size()) && node.row < int(grid.size()) && node.col >= 0 && node.row >= 0)
        return true;
    else
        return false;
}


vector<Node> updateUnVisit(vector<vector<int> > & grid){
    int cols = int(grid[0].size());
    int rows = int(grid.size());

    vector<Node> unVisitList;
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            if (grid[i][j] == unVisited){
                Node newnode;
                newnode.row=i;
                newnode.col=j;
                newnode.step= 0;
                unVisitList.push_back(newnode);
            }
        }
    }
    return  unVisitList;
}

bool checkFinish(vector<vector<int> > & grid){
    vector<Node> unVisitList = updateUnVisit(grid);
    int length=int(unVisitList.size());
    if (length == 0) return true;
    else return false;
}

bool directGo(Node curPos, Node start, Node toGo, vector<vector<int>> &costmap, vector<Node> &directpath){
    
    if (checkRange(curPos, costmap) && checkObs(curPos, costmap) && checkUnvisited(curPos,costmap)){
        if (reachGoal(toGo, curPos)){
            costmap[curPos.row][curPos.col]= Visited;
            return true;
        }
        
        costmap[curPos.row][curPos.col] = Visited;
       
        for (int i=0 ; i< TURNMAX; i++){
            Node tmpNode  = getNext(curPos, dirlist[i]);
            if (directGo(tmpNode, start, toGo ,costmap, directpath) == true){
                directpath.push_back(tmpNode);
                

                return true;
            }
        }
        costmap[curPos.row][curPos.col] = unVisited;
        return false;
    }
    return false;
    
}




bool move(Node &curPos, Node toGo,vector<vector<int> > & grid, vector<Node>& path){
    //prepare point to point path planning : costmap
    vector<vector<int>> costmap = grid;
    
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            if (grid[i][j]== Obs) costmap[i][j]= Obs;
            else costmap[i][j]= unVisited;
        }
    }
    
    vector<Node> directpath;
    //point to point planning
    directGo(curPos, curPos, toGo, costmap, directpath);
   
    // reverse the path to start to go
    reverse(directpath.begin(),directpath.end());
    // save new path step
    for (int i=0; i< directpath.size(); i++){
        PathStep++;
        directpath[i].step= PathStep;
        grid[directpath[i].row][directpath[i].col]= Visited;
    }
    // add point to point path to coverage path
    path.insert(path.end(),directpath.begin(),directpath.end());
    // reset current position
    curPos = toGo;
    
    return true;
}


double distance2N(Node node1,Node node2){
    return sqrt( abs(node1.col - node2.col)* abs(node1.col - node2.col)+
            abs(node1.row - node2.row)*abs(node1.row - node2.row));
    
}

Node Nearest(Node curPos, vector<Node> unVisitList){
    vector<int> distanceList;
    //Node NearestNode = unVisitList[0];
    for(int i = 0; i < unVisitList.size();i++){
        distanceList.push_back(distance2N(curPos, unVisitList[i]));
    }
    //FIND MIN DISTANCE NODE
    vector<int> ::iterator NearN = min_element(std::begin(distanceList),std::end(distanceList));
    auto NearPosition=std::distance(std::begin(distanceList),NearN);
    Node NearestNode = unVisitList[NearPosition];
    
    
    //TODO :如果地图很大，以当前点为半径寻找
    return NearestNode;
}



vector< Node > MinOverlap(Node start, vector<vector<int> > & grid){
    vector <Node> path;
    //int cols = int(grid[0].size());
    //int rows = int(grid.size());
    
    //int PathStep=1;
    
    Node curPos=start;
    Node tmpNode;
    int curDir= 0;
    int count=0;
    int count_max=1000;
    int TryTurn=TURNMAX;
    
    curPos.step = PathStep;
    grid[curPos.row][curPos.col]= Visited;
    path.push_back(curPos);
   
   
    while(checkRange(curPos,grid) && !checkFinish(grid) && count<count_max){
        tmpNode= getNext(curPos,curDir);
        if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
            curPos=tmpNode;
            PathStep++;
            curPos.step = PathStep;
            grid[curPos.row][curPos.col]= Visited;
            path.push_back(curPos);
            
            TryTurn=TURNMAX;
        }
        else{
            curDir= (curDir+1)%TURNMAX;
            TryTurn--;
            //cout<< "change direct to" <<curDir<<endl;
            if(TryTurn == 0){
                cout<<"deadlock"<<endl;
                if (checkFinish(grid) == false){
                    vector<Node> unVisitList = updateUnVisit(grid);
                    Node toGo = Nearest(curPos,unVisitList);
                    move(curPos,toGo,grid,path);
                    }
            }
            
        }
        count++;
            
        }
    
    if (checkFinish(grid)) cout<<"finish"<<endl;
    
    
    
    return path;
}


int main(int argc, const char * argv[]){
    vector<vector <int> > grid(6,vector<int>(6));
  
    int map[SIZE_M][SIZE_N]={
        0,0,0,0,0,0,
        0,0,0,0,0,0,
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
    
    
    //initialized
    
    //ADD START
    Node start;
    start.col =0;
    start.row =0;
    start.dir= dirlist[0]; // start right
    start.step= PathStep;
    //grid[start.row][start.col]=PathStep;
    
    vector<Node> path = MinOverlap(start, grid);
    printPathNode(path);
   
    printPathMap(grid, path);
    
    return 0;
}


