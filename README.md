# Path Planning Examples

---

## information

author : jiayao 

date : 2017-12-15

## done

 - point to point path planner (in exhausted way; in Astar way)
 - coverage path planner in exhausted way;(sprial direction template, plowing template)

例子，运行 /coverage/coverage/main.cpp：
![astar result][1]

*图片解释：
fig. 1 初始地图，0 free -1 obstacle 1 startpoint
fig. 2 第一次覆盖后的地图，数字代表步数step，-1为障碍物，遇到deadlock（step 32 in (2,1)）
fig. 3 遇到deadlock的情况后的点到点规划（32-34），第二次覆盖（36-37）完成覆盖
fig. 4 完整路径，步数：坐标（col,row）* 
## todo

- Spiral tree coverage in matlab upload;
- Sprial tree coverage in c++ under ROS;
- Spiral tree coverage in c++;
- Bio-inspired CCPP in matlab upload;
- Bio-inspried CCPP in c++ under ROS;
- Bio-inspired CCPP in c++;

## File Organiztion

### 1. main files are in "coverage":

- coverage planner:

    1.1 coverage.cpp: coverage path planner 

- point to point planner:

    1.2 directGo.cpp : point to point path planner in exhausted way;
    1.3 astar.cpp: point to point path planner 

### 2 easy examples in seperate files(each file has seperate main) :
- Point to Point planning 

    "p2pFreePrintMap.cpp":show map and path , 

    "Point2PointFree.cpp":no map shows

- Coverage planning: 

    "CoverageOverLap.cpp": simple spiral coverage, if meets deadlocks, stop
    
    "CoverageDirect.cpp": if meet deadlocks find a new point restart until finish coverage
    
    "CoverageDirectP2P.cpp": if meet deadlocks go to new point by point-to-point planner then restart.

## Coverage path planning algorithm - grid-based method examples 

根据地图类型的不同，覆盖算法可以有诸多分类，如下图。此文中只针对栅格地图（grid-based coverage）的全覆盖路径规划算法。
![coverage planning][2]
*fig 综述[217] 对于覆盖算法的总结(部分)， 根据地图类型的不同，覆盖算法可以有诸多分类，
- class exact cell decomposition, 
- morse-based cell decomposition, 
- natural landmark-based topological coverage, 
- grid-based coverage, 
- graph coverage.
- ...*


## grid-based coverage outline: 
✅穷举法：螺旋、牛耕
STC,BSA
Bio-inspired( our method )

### 穷举法

- 螺旋覆盖 
步骤：
    - 一直以一个方向前进
    - 如果不能走则按顺序换方向
    - 如果死锁寻找最近未覆盖点，点到点规划过去
    - 然后重新开始覆盖
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
结果示意图
![spiral][3] fig. 第一次覆盖 
![sprial finish][4] fig 全部覆盖完成

- 牛耕覆盖 
步骤：
    - 一直以一个方向前进，
    - 如果不能走则转弯，掉头继续走
    - 如果死锁寻找最近未覆盖点，点到点规划过去
    - 然后重新开始覆盖
    - 直到地图全部走过

伪代码
```
while(current node is in range , still has unvisited node in map){
    next node = current node in current direction RIGHT;
    if next node can go
        go;
    else 
        next node = current node change to direction DOWN;
        if  DOWN ok
            go one step
            if next node RIGHT ok go
            if next node LEFT ok go
        else UP ok
            go one step
            if next node RIGHT ok go
            if next node LEFT ok go
        else all surronding nodes can not go this is a deadlock situation;
            find nearest unvistied node as a new start;
            use point to point path planning to get to a new start;
            caculate overlap;
}
```
结果示意图
![plowing][5] fig. 第一次覆盖
![plowing finish][6] fig 全部覆盖完成

### 覆盖算法

>  ---翻译《Planning Algorithm》CH7 覆盖算法
举一个coverage planning覆盖规划的例子，试想一个自主运动的割草机，需要在一个有很多障碍物的地方工作，例如房屋、树木、车库，和复杂的边界。
什么样的zig-zag路径对于割草机是最好的？重覆盖的路程能最小化么？割草机停止和转弯的次数能最小么。
这样的应用的例子除了割草，还有自动工作，粉刷，吸尘器，采矿等。参见[217]综述 

> 即使在二维下，寻找覆盖的最优路径是NP难问题。问题简化后可以看做是Traveling Salesman Problem
旅行商问题。[36, 709] 因此，我们即使在$R^2$空间内也容忍近似，启发式的算法去解决覆盖问题。

> Boustrophedon decomposition 牛耕分解法
是把Cfree分解成cells，然后像牛耕地一样运动[222].
它假设机器人是$W=R^2$中的一个点，但是其有工具厚度E挂在机器人的两边，覆盖Cfree以E/2,这种方法常用在打印机减少打印转弯。
如果$C_{OBS}$是多边形，像6.2.2讨论的垂直分解，那个算法里有很多情况，在牛耕运动中只遇到第一种情况。
这使得分解出的cell数目少，即使是非凸的，也能很好的切成垂直的片，很适合于牛耕。原始的垂直方法也可以使用，但是多余的cell边缘会导致机器人不必要的重新定位。一个相似的方法是最优化机器人的转角[468].
---翻译《Planning Algorithm》CH7 覆盖算法
 

1. BSA
2. STC

# Bio-inspired Coverage Planning 

selected figures in our paper to submitt to IJARS 
![our methods][7]
![neurons activity][9]
![flow chart][8]

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



  [216]: H. Choset. Coverage of known spaces: The boustrophedon cellular decomposition.
Autonomous Robots, 9:247–253, 2000.
 [217]: H. Choset. Coverage for robotics – A surveyof recent results. Annals of Mathematics and Artificial Intelligence,31:113–126, 2001.


  [1]: https://wx3.sinaimg.cn/mw690/c7716318gy1fmho52e44nj20ad0dlmy5.jpg
  [2]: https://wx1.sinaimg.cn/mw690/c7716318gy1fmid7572c8j20wo0rtaf7.jpg
  [3]: https://wx2.sinaimg.cn/mw690/c7716318gy1fmidjl5pcuj2048061aa8.jpg
  [4]: https://wx2.sinaimg.cn/mw690/c7716318gy1fmidjl8hi8j20a8065aam.jpg
  [5]: https://wx1.sinaimg.cn/mw690/c7716318gy1fmidh3gfytj204e05udg0.jpg
  [6]: https://wx4.sinaimg.cn/mw690/c7716318gy1fmidh3ft16j20aa06vq3l.jpg
  [7]: https://wx1.sinaimg.cn/mw690/c7716318ly1fmido72oi7j20dv0c0jv3.jpg
  [8]: https://wx1.sinaimg.cn/mw690/c7716318ly1fmidougw8sj20hm0oljxd.jpg
  [9]: https://wx2.sinaimg.cn/mw690/c7716318ly1fmidpwhz1cj212v0c6wka.jpg