//
//  coverage.cpp
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include "coverage.h"
#include "astar.h"
#include "directGo.h"

int PathStep=1;


void printPathMap(vector<vector<int> > grid, vector<Node> path){
    /*
     print map and path on screen, the number show in the map is the path step,
     if overlap occurs shows the later step in grid.
     
     :param: grid map
     :param: path node
     
     :return: none
     
     author: jiayao
     date: 2017-12-14 pku
     */
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
    /*
     print map on screen
     
     :param: grid map
     
     :return: none
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
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
    /*
     print path on screen , step :(row, col)
     
     :param: path node
     
     :return: none
     
     author: jiayao
     date: 2017-12-14 pku
     */
    cout<<"---- path----"<<endl;
    for(int i = 0; i < path.size() ; i++){
        cout<<path[i].step<<": ("<<path[i].row<<","<<path[i].col<<") ";
    }
    cout<<endl;
}




Node getNext(Node node, int dir){
    /*
     get next node by given the current node and exect direction.
     
     :param: cur ndoe
     :param: expect direction
     
     :return: next node
     
     author: jiayao
     date: 2017-12-14 pku
     */
    Node nextNode(0,0);
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
    /*
     check if the node is unvisited
     
     :param: node we want to check
     :param: grid map
     
     :return:  unvisited return true; has visited return false,
     
     author: jiayao
     date: 2017-12-14 pku
     */
    if (grid[node.row][node.col] == unVisited) return true;
    else return false;
}

bool checkObs(Node node,vector<vector<int> > &grid){
    /*
     check if the node is obstacle
     
     :param: node we want to check
     :param: grid map
     
     :return:  not obstacle return true; obstacle return false,
     
     author: jiayao
     date: 2017-12-14 pku
     */
    if (grid[node.row][node.col] == Obs) return false;
    else return true;
}

bool reachGoal(Node node1, Node node2){
    /*
     check if the position of two nodes are the same
     
     :param: node we want to check
     :param: node we want to check
     
     :return:  same return true; different return false,
     
     author: jiayao
     date: 2017-12-14 pku
     */
    if (node1.col == node2.col && node1.row == node2.row)
        return true;
    else
        return false;
}

bool checkRange(Node node,vector<vector<int> > &grid){
    /*
     check if the position of two nodes are the same
     
     :param: node we want to check
     :param: grid map
     
     :return:  same return true; different return false,
     
     author: jiayao
     date: 2017-12-14 pku
     */
    if (node.col < int(grid[0].size()) && node.row < int(grid.size()) && node.col >= 0 && node.row >= 0)
        return true;
    else
        return false;
}

vector<Node> updateUnVisit(vector<vector<int> >  &grid){
    /*
     maintain a list of unvisited node
     
     :param: grid map
     
     :return: a list of unvisited node
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    vector<Node> unVisitList;
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            if (grid[i][j] == unVisited){
                Node newnode(i,j);
                //newnode.row=i;
                //newnode.col=j;
                newnode.step= 0;
                unVisitList.push_back(newnode);
            }
        }
    }
    return  unVisitList;
}

bool checkFinish(vector<vector<int> > &grid){
    /*
     check if the coverage finish by check the length of unvisited list
     
     :param: grid map
     
     :return: all finish return true; or return false
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
    vector<Node> unVisitList = updateUnVisit(grid);
    int length=int(unVisitList.size());
    if (length == 0) return true;
    else return false;
}





double distance2N(Node node1,Node node2){
    return sqrt( abs(node1.col - node2.col)* abs(node1.col - node2.col)+
                abs(node1.row - node2.row)*abs(node1.row - node2.row));
    
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
    
    
    //point to point planning
    
    astarPath(curPos, curPos, toGo,  costmap, grid, path);
    
    //directGoPath(costmap, grid, path, curPos, toGo);
    
    return true;
}




Node Nearest(Node curPos, vector<Node> unVisitList){
    /*
     find nearst node arount current node in the unvisitlist list,
     
     :param:  current node postion
     :param:  unvisited list
     
     
     :return: node nearest node in the list
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
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



vector< Node > CoverageSprial(Node start, vector<vector<int> > & grid){
    /*
     Coverage path planning , coverage unvisited node following the direction in directionlist, if meeting deadlocks , ignore the visited flag, do point to point path planning to escape and continue coverage
     
     :param:  start node
     :param:  grid map
     
     :return: whole path
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
    vector <Node> path;
    
    //Node tmpNode; // tmp save next node
    int TryTurn=TURNMAX;
    
    //for debug
    int count=0;
    int count_max=1000;
    
    //initial start
    Node curPos=start;
    int curDir= dirlist[0]; // start direction set
    curPos.step = PathStep;
    grid[curPos.row][curPos.col]= Visited;
    path.push_back(curPos);
    
    printPathMap(grid,path);
    
    
    while(checkRange(curPos,grid) && !checkFinish(grid) && count<count_max){
        Node tmpNode= getNext(curPos,curDir);
        
        // if can go
        if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
            curPos=tmpNode;
            PathStep++;
            curPos.step = PathStep;
            grid[curPos.row][curPos.col]= Visited;
            path.push_back(curPos);
            
            TryTurn=TURNMAX;
        }
        
        // change direction
        else{
            curDir= (curDir+1)%TURNMAX;
            TryTurn--;
            
            // meet deadlock, all the direction has been visited or obs, cant go.
            if(TryTurn == 0){
                
                if (checkFinish(grid) == false){
                    vector<Node> unVisitList = updateUnVisit(grid);
                    Node toGo = Nearest(curPos,unVisitList);
                    
                    //start point 2 point to escape
                    move(curPos,toGo,grid,path);
                }
            }
            
        }
        count++;
        
    }
    
    
    
    return path;
}


vector< Node > CoveragePlowing(Node start, vector<vector<int> > & grid){
    /*
     Coverage path planning , coverage unvisited node following the direction in directionlist, if meeting deadlocks , ignore the visited flag, do point to point path planning to escape and continue coverage
     
     :param:  start node
     :param:  grid map
     
     :return: whole path
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
    vector <Node> path;
    
    //Node tmpNode; // tmp save next node
    int TryTurn=2;
    
    //for debug
    int count=0;
    int count_max=1000;
    
    //initial start
    Node curPos=start;
    int curDir= RIGHT; // start direction set
    curPos.step = PathStep;
    grid[curPos.row][curPos.col]= Visited;
    path.push_back(curPos);
    
    printPathMap(grid,path);
    
    
    while(checkRange(curPos,grid) && !checkFinish(grid) && count<count_max){
        Node tmpNode= getNext(curPos,curDir);
        
        // if can go
        if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
            curPos=tmpNode;
            PathStep++;
            curPos.step = PathStep;
            grid[curPos.row][curPos.col]= Visited;
            path.push_back(curPos);
            
            TryTurn = 2;
        }
        
        // change direction
        else{
          
            curDir= DOWN;
            tmpNode= getNext(curPos,curDir);
            if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                curPos=tmpNode;
                PathStep++;
                curPos.step = PathStep;
                grid[curPos.row][curPos.col]= Visited;
                path.push_back(curPos);
                
                curDir = RIGHT;
                tmpNode= getNext(curPos,curDir);
                if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                    curPos=tmpNode;
                    PathStep++;
                    curPos.step = PathStep;
                    grid[curPos.row][curPos.col]= Visited;
                    path.push_back(curPos);
                    
                    TryTurn=1;
                }
                else{
                    curDir = LEFT;
                    tmpNode= getNext(curPos,curDir);
                    if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                        curPos=tmpNode;
                        PathStep++;
                        curPos.step = PathStep;
                        grid[curPos.row][curPos.col]= Visited;
                        path.push_back(curPos);
                        
                        TryTurn=1;
                    }
                }
            }
            
            
            
            else{
                curDir= UP;
                tmpNode= getNext(curPos,curDir);
                if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                    curPos=tmpNode;
                    PathStep++;
                    curPos.step = PathStep;
                    grid[curPos.row][curPos.col]= Visited;
                    path.push_back(curPos);
                    
                    curDir = RIGHT;
                    tmpNode= getNext(curPos,curDir);
                    if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                        curPos=tmpNode;
                        PathStep++;
                        curPos.step = PathStep;
                        grid[curPos.row][curPos.col]= Visited;
                        path.push_back(curPos);
                        
                        TryTurn=1;
                    }
                    else{
                        curDir = LEFT;
                        tmpNode= getNext(curPos,curDir);
                        if (checkRange(tmpNode,grid) && checkObs(tmpNode,grid) && checkUnvisited(tmpNode,grid) ){
                            curPos=tmpNode;
                            PathStep++;
                            curPos.step = PathStep;
                            grid[curPos.row][curPos.col]= Visited;
                            path.push_back(curPos);
                            
                            TryTurn=1;
                        }
                    }
                }
                else{
                    if (checkFinish(grid) == false){
                        vector<Node> unVisitList = updateUnVisit(grid);
                        Node toGo = Nearest(curPos,unVisitList);
                        
                        //start point 2 point to escape
                        move(curPos,toGo,grid,path);
                    }
                }

            }
            
            
            // meet deadlock, all the direction has been visited or obs, cant go.
            
        }
        count++;
        
    }
    
    
    
    return path;
}





