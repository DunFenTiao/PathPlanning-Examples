# Path Planning Examples

## information

author : jiayao 

date : 2017-12-15

## done

 - point to point path planner (in exhausted way; in Astar way)
 - coverage path planner in exhausted way;(sprial direction template)

例子，运行 /coverage/coverage/main.cpp：
![astar result][1]
fig. 1 初始地图，0 free -1 obstacle 1 startpoint
fig. 2 覆盖之后，数字代表步数step，-1为障碍物。覆盖方法是贪心法。
fig. 3 遇到deadlock的情况(周围点都走过，或者为障碍物，图中为点32)，为了保证完整覆盖，利用点到点规划到新起点后继续进行覆盖，这里采用astar点到点规划（另有有回溯法可选）
fig. 4 完整路径 步数：坐标（col,row） 
## todo

- Spiral tree coverage in matlab upload;
- Sprial tree coverage in c++ under ROS;
- Spiral tree coverage in c++;
- Bio-inspired CCPP in matlab upload;
- Bio-inspried CCPP in c++ under ROS;
- Bio-inspired CCPP in c++;

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

## Coverage path planning algorithm
outline: 
✅贪心法
STC
BSA
Bio-inspired

### 贪心法
步骤：
- 一直以一个方向前进
- 如果不能走则按顺序换方向
- 如果死锁寻找最近未覆盖点，点到点规划过去
- 然后重新开心覆盖
- 直到地图全部走过

伪代码
```
while(current node is in range , still has unvisited node in map){
    next node = current node in current direction;
    if next node can go
        go;
    else 
        tmp node = current node change direction;;
        if all surronding nodes can not go this is a deadlock situation;
            find nearest unvistied node as a new start;
            use point to point path planning to get to a new start;
            caculate overlap
}
```


## Point to point path planning algorithm
outline: 
✅astar
✅递归
非递归
广度优先
深度优先
使用对战

### Astar point to point planning
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
通过Parent找到路径，再反转，即为start到goal的路径。

伪代码：
```
while(open list not empty)
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
    if goal is in openlist
        break;
}
if openlist is empty , no path;
```
代码示例，/coverage/coverage/astar.cpp



  [1]: https://wx3.sinaimg.cn/mw690/c7716318gy1fmho52e44nj20ad0dlmy5.jpg