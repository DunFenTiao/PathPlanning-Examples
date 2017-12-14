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

//astar point
struct aPoint{
    Node node;
    int fvalue;
    int hvalue;
    int gvalue;
};
//astar point (has parent)
struct astarPoint{
    Node node;
    int fvalue;
    int hvalue;
    int gvalue;
    aPoint parent;
};

vector<Node> astarPath(Node &curPos, Node start, Node goal,vector<vector<int> > & costmap, vector<Node>& path);



#endif /* defined(__coverage__astar__) */
