//
//  main.cpp
//  coverage
//
//  Created by mjy on 17-12-14.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include <iostream>
#include "coverage.h"


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
    Node start(0,0);
    //start.col =0;
    //start.row =0;
    start.step= PathStep;
    //grid[start.row][start.col]=PathStep;
    
    vector<Node> path = MinOverlap(start, grid);
    printPathNode(path);
    
    printPathMap(grid, path);
    
    return 0;
}
