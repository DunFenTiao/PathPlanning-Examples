# Path Planning Examples

##information
author : jiayao 
date : 2017-12-13
##done
point to point path planner in exhausted way;
coverage path planner in exhausted way;(sprial direction template)
##todo
1. Point to Point path planner A star;
2. Point to Point path planner D star;
3. Spiral tree coverage in matlab upload;
4. Sprial tree coverage in c++ under ROS;
5. Spiral tree coverage in c++;
Bio-inspired CCPP in matlab upload;
Bio-inspried CCPP in c++ under ROS;
Bio-inspired CCPP in c++;

# File Organiztion
main files are in "coverage":
// coverage planner
1. coverage.cpp: coverage path planner 
// point to point planner
2. directGo.cpp : point to point path planner in exhausted way;
3. astar.cpp: point to point path planner 

easy examples in seperate files(each file has seperate main) :
1. Point to Point planning 
"p2pFreePrintMap.cpp":show map and path , 
"Point2PointFree.cpp":no map shows
2. Coverage planning: 
"CoverageOverLap.cpp": simple spiral coverage, if meets deadlocks, stop
"CoverageDirect.cpp": if meet deadlocks find a new point restart until finish coverage
"CoverageDirectP2P.cpp": if meet deadlocks go to new point by point-to-point planner then restart.
