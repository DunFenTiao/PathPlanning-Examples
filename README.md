# Path Planning Examples

## information

author : jiayao 

date : 2017-12-13

## done
1. point to point path planner in exhausted way;
2. coverage path planner in exhausted way;(sprial direction template)

## todo
1. Point to Point path planner A star;
2. Point to Point path planner D star;
3. Spiral tree coverage in matlab upload;
4. Sprial tree coverage in c++ under ROS;
5. Spiral tree coverage in c++;
6. Bio-inspired CCPP in matlab upload;
7. Bio-inspried CCPP in c++ under ROS;
8. Bio-inspired CCPP in c++;

## File Organiztion

### 1. main files are in "coverage":

#### coverage planner:

1.1 coverage.cpp: coverage path planner 

#### point to point planner:

1.2 directGo.cpp : point to point path planner in exhausted way;
1.3 astar.cpp: point to point path planner 

### 2 easy examples in seperate files(each file has seperate main) :
#### 2.1 Point to Point planning 

 "p2pFreePrintMap.cpp":show map and path , 

"Point2PointFree.cpp":no map shows

#### 2.2 Coverage planning: 

"CoverageOverLap.cpp": simple spiral coverage, if meets deadlocks, stop

"CoverageDirect.cpp": if meet deadlocks find a new point restart until finish coverage

"CoverageDirectP2P.cpp": if meet deadlocks go to new point by point-to-point planner then restart.

## Algorithm
outline: 
✅a star
✅递归
非递归
广度优先
深度优先
使用对战

### A start point to point planning
步骤：
1. 从起点start开始，把它作为待处理的节点放在open list中，open list是个等待检查的列表
2. 寻找起点start周围可以到达的方格，将他们放入开启列表，并且设置他们的parent为start.
3. 从openlist中删除起点，将其加入到close list中，close list中存放的都是不需要再次检查的方格
4. 对于一个方格，计算其f=g+h，g表示从起点到方格的移动耗费，h表示从方格到终点的预计耗费。
5. 从openlist里面选择f值最低的方格，把它从open list中删除，放入close list。
6. 检查相邻且可到达的方格（非障碍物，也不在close list中），如果不在open list中加如openlist设置Parent。
7. 如果方格在openlist中，检查如果用新的路径到达它，g值是否更低，如果g更低，将其parent改为当前方格，重新计算f,g。
8. 当终点被加入到open list，说明路径已经找到

路径：
通过Parent找到路径。

伪代码：
```
do
{
    find cur node which has min fvalue;
    delete curnode in openlist;
    add curnode to closelist;
    find valiable nodes around cur node;
    if valiable node not in openlist
        add to openlist
        calculate f=g+h
        set parent is curnode;
    if valiable node in openlist
        if node.g lower than cur.g
            curnode = node.parent
            calculate f=g+h
}while(goal is in openlist)
if openlist is empty , no path;
```







