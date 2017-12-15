//
//  astar.cpp
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include "astar.h"



Node nullnode = Node(-1,-1);
astarPoint nullpoint= astarPoint(nullnode);


astarPoint  getLeastPoint(vector<astarPoint> openlist){
    if (openlist.empty()) return nullpoint;
    int min=openlist[0].fvalue;
    int minpos=0;
    
    for(int i=0; i<openlist.size();i++){
        if (openlist[i].fvalue < min){
            min= openlist[i].fvalue;
            minpos=i;
        }
    }
    return openlist[minpos];
}

bool removePoint(vector<astarPoint> &list,astarPoint point){
    for (vector<astarPoint>::iterator it=list.begin(); it!= list.end();){
        if (it->node.col == point.node.col && it->node.row == point.node.row ){
            it = list.erase(it);
            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}

bool InList(vector<astarPoint> list,  astarPoint point){
    if (list.empty()) return false;
    for (int i = 0; i< list.size(); i++){
        if (list[i].node.col == point.node.col && list[i].node.row == point.node.row ){
            return true;
        }
    }
    return false;
}


int calG(astarPoint cur, astarPoint target){
    //int extraG = kcost1* (abs(cur.node.col - target.node.col) + abs(cur.node.row - target.node.row));
//    if (extraG == 1) extraG = kcost1;
//    else{
//        extraG= kcost2;
//    }
    int extraG= kcost1;
    
    int parentG;
    if (target.parent == NULL ){
        parentG = 0;
    }
    else {
        parentG = target.parent->gvalue;
    }
    
    return int(extraG + parentG);
};

int calH(astarPoint target, astarPoint goal){
    return int(distance2N(target.node, goal.node) * kcost1);
};

int calF(astarPoint target){
    return (target. gvalue + target. hvalue);
};

void printPathPoint(vector<astarPoint> path){
    /*
     print path on screen , step :(row, col)
     
     :param: path point
     
     :return: none
     
     author: jiayao
     date: 2017-12-14 pku
     */
    cout<<"---- path point----"<<endl;
    for(int i = 0; i < path.size() ; i++){
        cout<<path[i].node.step<<": ("<<path[i].node.row<<","<<path[i].node.col<<") ";
    }
    cout<<endl;
}


vector<astarPoint> surroundPoint(astarPoint cur, vector<vector<int>> costmap, vector<astarPoint> closelist){
    vector<astarPoint> surround;
    for (int i = 0 ; i< TURNMAX; i++){
        astarPoint target = astarPoint(getNext(cur.node, dirlist[i]));
        if (checkRange(target.node, costmap) && checkObs(target.node, costmap) \
            && !InList(closelist, target)){
            surround.push_back(target);
        }
    }
    return surround;
}

vector<astarPoint> astar(Node curPos, Node start, Node goal, vector<vector<int> > &costmap){
    
    vector<astarPoint> openlist;
    vector<astarPoint> closelist;
    
    astarPoint startPoint(start);
    astarPoint goalPoint(goal);
    
    openlist.push_back(startPoint);
    
    while(!openlist.empty()){
        astarPoint cur = getLeastPoint(openlist);
        
        removePoint(openlist, cur);
        closelist.push_back( cur);
        
        
        // surround around
        vector <astarPoint> targetlist = surroundPoint(cur,costmap,closelist);
       
        for(int i =0 ; i< targetlist.size() ; i++){
            astarPoint target= targetlist[i];
            
            if (!InList(openlist, target)){
                astarPoint* p = new astarPoint(Node(0,0));
                *p = cur;
                target.parent= p;
                
                target.gvalue= calG(cur,target);
                target.hvalue= calH(target,goalPoint);
                target.fvalue= calF(target);
                openlist.push_back(target);
                
            }
            else{
                //cal g
                int tempG = calG( cur, target);
                if (tempG < cur.gvalue){
                    astarPoint* p = new astarPoint(Node(0,0));
                    *p = cur;
                    target.parent= p;
                    
                    target.gvalue =tempG;
                    target.fvalue =calF(cur);
                }
                
            }
        }
        
       if (InList(openlist, goalPoint)){
            vector<astarPoint> list;
            int tmp;
                
            for (int i = 0; i< openlist.size(); i++){
                if (openlist[i].node.col == goalPoint.node.col && \
                    openlist[i].node.row == goalPoint.node.row ){
                    tmp=i;
                    break;
                }
            }
           
           list.push_back(openlist[tmp]);
           
            astarPoint * father= openlist[tmp].parent;
    
            while ( father != NULL ){
                
                list.push_back(*father);
                father= (*father).parent;
            }
           
          
           
           
           return list;
       }
        
    }
    return openlist;
}


vector<Node> astarPath(Node &curPos, Node start, Node goal,vector<vector<int> > & costmap,vector<vector<int> > & grid, vector<Node>& path){
    
    
    vector<astarPoint> p2pPath;
    p2pPath = astar(curPos, start, goal, costmap);
    
    
    
    reverse(p2pPath.begin(),p2pPath.end());
    
    printPathMap(grid,path);
    cout<<" point to point path :"<<endl;
    printPathPoint(p2pPath);
    
   
    for(int i=0 ; i < p2pPath.size(); i++){
        Node tmp = p2pPath[i].node;
        tmp.step = PathStep++;
        path.push_back(tmp);
        grid[tmp.row][tmp.col]= Visited;
    }
    
    
    curPos = goal;
    
    return path;
}