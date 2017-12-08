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
// grid[i][j] == step; path


// 无障碍物， 覆盖

struct Node{
    int col;
    int row;
    void print(){
        cout<< "("<<row<<","<<col<<")"<<endl;
    }
};

void printpath(vector<vector<int> >  & grid){
    cout<<"----map & path----"<<endl;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    for(int i=0; i < cols; i++){
        for(int j=0; j < rows; j++){
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
vector< Node > MinOverlap(vector<vector<int> > & grid){
    vector <Node> path;
    int cols = int(grid[0].size());
    int rows = int(grid.size());
    
    int i=0, j=0;
    int PathStep=0;
    grid[i][j]= PathStep;
    
        // right
    for(j=0; j<rows; j++){
        PathStep++;
        grid[i][j]= PathStep;
    }
    j--;
    i++;
        // left
    for(; i<cols; i++){
        PathStep++;
        grid[i][j]= PathStep;
        }
    
   
    return path;
}


int main(int argc, const char * argv[]){
    vector<vector <int> > grid;
    vector <int> tmp;
    for(int i=0; i<6 ;i++){
        tmp.push_back(0);
    }
    for(int i=0; i<6 ;i++){
        grid.push_back(tmp);
    }
    
    
    printpath(grid);
    
    MinOverlap(grid);
    
    printpath(grid);
    
    return 0;
}


