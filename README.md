# Train_Route
Data Structures with C Project Year 2016

The train is to have 15 bogeys. Each bogey contains one item to be dropped off at a certain destination.
The map and bogey details are to be entered by the user. The program then routes the train in an efficient path.

## File Structure
`train.c` contains the main program. First number of stations are taken using `getstation()`. Stations are then numbered from 0 to N-1, where N is the number of stations. 0 is the source station.
Next, a station map is to be created. All related functions lie in `station.h`. Map is stored as an adjacency matrix. 
Next, bogey details are input. All related functions lie in `bogey.h`.
Next route is created. All related functions lie in `route.h`, which in turn depends on `graph.h`, which has implementations of graph-related algorithms.

## Basic Algorithm
### getRoute()
This function creates the route, implemented as a linked list, and returns head node.
1.	Only the required stations are taken, based on bogey details. The `reqStations` array is used for this. `reqStations[i]` if `1` if `i` is a required station, `0` if `i` is not. 
2.	A subgraph is created using `createSubGraph()`.
3.	The source station is attached to the subgraph connecting to the nearest node in the subgraph
4.	A minimal spanning tree of this subgraph is made and stored as an adjacency matrix
5.	All leaf nodes are taken. A leaf node is a terminal station. `findLeaves()` does this job
6.	Route is created by the `createRoute()`
### createRoute()
1.	Initially `source = 0`.
2.	Loop until `leaves` is empty:
    1. Remove source from leaves, that is, `leaves[source] = 0`
    2. Find the nearest leaf to `source`
    3. Append shortest path to nearest leaf from `source` to `route`
    4. `source` = nearest leaf