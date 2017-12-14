//
//  astar.cpp
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include "astar.h"



astarPoint getLeastPoint(vector<astarPoint> openlist){
    vector<int> flist;
    astarPoint minfpoint;
    for (int i =0; i< openlist.size(); i++){
        flist.push_back(openlist[i].fvalue);
    }
    if(!openlist.empty()){
        vector<int> ::iterator minf = min_element(begin(flist),end(flist) );
        auto minfPosition= std::distance(begin(flist),minf);
        astarPoint minfpoint = openlist[minfPosition];
        return minfpoint;
        
    }
    else return minfpoint;
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

bool InList(vector<astarPoint> list, astarPoint point){
    for (int i=0; i< list.size(); i++){
        if (list[i].node.col == point.node.col && list[i].node.row == point.node.row )
            return true;
    }
    return false;
}


int calG(astarPoint cur, astarPoint target){
    int extraG = abs(cur.node.col - target.node.col) + abs(cur.node.row - target.node.row);
    if (extraG == 1) extraG = kcost1;
    else extraG= kcost2;
    
    int parentG;
    parentG = target.parent.gvalue;
    
    return int(extraG + parentG);
};

int calH(astarPoint target, astarPoint goal){
    return int(distance2N(target.node, goal.node) * kcost1);
};

int calF(astarPoint target){
    return target. gvalue + target. hvalue;
};


vector<astarPoint> astar(Node curPos, Node start, Node goal, vector<vector<int>> &costmap){
    
    vector<astarPoint> openlist;
    vector<astarPoint> closelist;
    
    astarPoint startPoint;
    startPoint.node.col= start.col;
    startPoint.node.row= start.row;
    
    astarPoint goalPoint;
    goalPoint.node.col= goal.col;
    goalPoint.node.row= goal.row;
    
    
    
    openlist.push_back(startPoint);
    
    while(!openlist.empty()){
        astarPoint cur = getLeastPoint(openlist);
        
        removePoint(openlist,cur);
        closelist.push_back(cur);
        
        // find around
        for (int i=0 ; i< TURNMAX; i++){
            astarPoint target;
            target.node= getNext(cur.node, dirlist[i]);
            
            // if not in list , add it in list;
            if (checkRange(target.node, costmap) && checkObs(target.node, costmap) \
                && checkUnvisited(target.node,costmap) && InList(openlist, target) \
                && !InList(closelist, target)){
                target.parent.node = cur.node;
                target.gvalue= calG(cur,target);
                target.hvalue= calH(target,goalPoint);
                target.fvalue= calF(target);
                
                openlist.push_back(target);
            }
            else{
                //cal g
                int tempG = calG(cur, target);
                if (tempG < target.gvalue){
                    target.parent.node = cur.node;
                    target.gvalue= tempG;
                    target.fvalue= calF(target);
                }
            }
            
            if (InList(openlist, goalPoint)){
                return openlist;
            }
            
            
        }
        
    }
    return openlist;
}


vector<Node> astarPath(Node &curPos, Node start, Node goal,vector<vector<int> > & costmap, vector<Node>& path){
    
    vector<astarPoint> p2pPath = astar(curPos, start, goal, costmap);
    reverse(p2pPath.begin(),p2pPath.end());
    Node tmp;
    for(int i=0 ; i < p2pPath.size(); i++){
        tmp = p2pPath[i].node;
        PathStep++;
        tmp.step = PathStep;
        path.push_back(tmp);
    }
    curPos = goal;
    return path;
}