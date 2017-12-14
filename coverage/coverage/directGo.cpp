//
//  directGo.cpp
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include "directGo.h"


bool directGo(Node curPos, Node start, Node toGo, vector<vector<int>> &costmap, vector<Node> &directpath){
    /*
     point to point planner, exhausted finding in four directions to get a path.
     
     :param:  current node position
     :param:  start node
     :param:  goal node
     :param:  cost map for point to point planning, the visited flag is clear allow the robot to overlap
     :param:  point to point path
     
     :return: if reach the goal return true, else return false
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
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

vector<Node> directGoPath(vector<vector<int> > &costmap, vector <vector<int> > &grid, vector<Node> &path, Node &curPos, Node toGo){
    
    /*
     get path from point to point planner directGo
     
     :param:  path
     :param:  cost map
     :param:  grid map
     :param:  whole path
     :param:  current node postion
     :param:  goal node
     
     
     :return: whole path, including coverage and point to point path
     
     author: jiayao
     date: 2017-12-14 pku
     */
    
    vector<Node> directpath;
    // do direct go
    directGo(curPos, curPos, toGo, costmap, directpath);
    
    // revesre path from start to go
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
    return path;
}