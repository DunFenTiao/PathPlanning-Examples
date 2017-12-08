//
//  main.cpp
//  path
//
//  Created by mjy on 17-12-6.
//  Copyright (c) 2017年 jiayao. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

// vector<vector<int>> grid;
// grid[i][j] == 0 ; free
// grid[i][j] == 1 ; object


// 无障碍物， 从左上走到右下

struct Node{
    int col;
    int row;
    void print(){
        cout<< "("<<row<<","<<col<<")"<<endl;
    }
};

vector< Node > MinOverlap(vector<vector<int> > const & grid){
    vector <Node> path;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    int i=0, j=0;
    for(j=0; j<rows; j++){
        Node node;
        node.col=i;
        node.row=j;
        path.push_back(node);
    }
    j--;
    for(i=0; i< cols; i++){
        Node node;
        node.col=i;
        node.row=j;
        path.push_back(node);
    }
    return path;
}


int main(int argc, const char * argv[]){
    vector<vector <int> > grid;
    vector <int> tmp;
    for(int i=0; i<5 ;i++){
        tmp.push_back(0);
    }
    for(int i=0; i<5 ;i++){
        grid.push_back(tmp);
    }
    vector <Node> path = MinOverlap(grid);
    int length = int(path.size());
    for(int i=0; i< length ; i++){
        path[i].print();
    }
    
    return 0;
}


