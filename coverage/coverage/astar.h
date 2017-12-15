//
//  astar.h
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#ifndef __coverage__astar__
#define __coverage__astar__

#include <stdio.h>
#include "coverage.h"

//astar
const static int kcost1=10; //直走消耗
const static int kcost2=14; //斜走消耗


struct astarPoint{
    Node node;
    int fvalue;
    int hvalue;
    int gvalue;
    astarPoint * parent;
    astarPoint(Node _node):node(_node),fvalue(0),gvalue(0),hvalue(0),parent(0){
    }
};











vector<Node> astarPath(Node &curPos, Node start, Node goal,vector<vector<int> > & costmap,vector<vector<int> > & grid, vector<Node>& path);


#endif /* defined(__coverage__astar__) */
