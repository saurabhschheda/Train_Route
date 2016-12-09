#ifndef ROUTE_H
#define ROUTE_H

#include <stdlib.h>
#include "graph.h"

struct Node
{
    int station, distance;
    struct Node *next;
};

void displayRoute(struct Node* route)
{
    struct Node* traverse = NULL;
    traverse = route;
    while(traverse) 
    {
        printf("Train goes to station %d\n", traverse -> station);
        traverse = traverse -> next;
    }
    printf("Train goes to station 0\n");
}

//utility function to Initialize every element of an array to 0
void clear(int array[], int size) 
{
    int i;
    for (i = 0; i < size; ++i)
        array[i] = 0;
}

void createMatrix(int parent[], int nodes, int graph[][15], int matrix[][15]) 
{
    int i, j;
    for (i = 0; i < nodes; ++i)
        clear(matrix[i], nodes);
    for (i = 1; i < nodes; ++i)
        addEdge(matrix, parent[i], i, graph[parent[i]][i]);
}

void findLeaves(int parent[], int leaves[], int size) 
{
    int i, j;
    leaves[0] = 1;    
    for(i = 1; i < size; ++i)
    {
        leaves[i] = 1;
        for(j = 1; j < size; ++j)
            if (parent[j] == i && i != j)
                leaves[i] = 0;
    } 
}

//Utility function to check if all elements of array is 0
int sumArray(int array[], int size) 
{
    int sum = 0, i;
    for(i = 0; i < size; ++i)
        sum += array[i];
    return sum;
}

int findNearestLeaf(int leaves[], int dist[], int size, int source)
{
    int i, smallLeaf = source;
    for (i = 0; i < size; ++i)
    {
        if (leaves[i] && dist[i] < dist[smallLeaf])
            smallLeaf = i;
    }
    return smallLeaf;
}

struct Node* createPath(int source, int destination, int parent[])
{
    struct Node *temp = NULL, *start = NULL;
    int currentStation = parent[destination];
    do 
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp -> station = currentStation;
        temp -> next = start;
        start = temp;
        temp = NULL;
        currentStation = parent[currentStation];    
    } while(currentStation != source);
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp -> station = currentStation;
    temp -> next = start;
    start = temp;
    temp = NULL;
    return start;
}

struct Node* updatePath(struct Node* oldPath, struct Node* newPath)
{
    struct Node *traverse = NULL;
    if (!oldPath) oldPath = newPath;
    else
    {
        traverse = oldPath;
        while(traverse -> next) traverse = traverse -> next;
        traverse -> next = newPath;
    }
    return oldPath;
}

struct Node* createRoute(int matrix[][15], int leaves[], int size) 
{
    struct Node *start = NULL, *newPath = NULL;
    int source = 0, destination, parent[size], dist[size];
    do
    {
        leaves[source] = 0;
        dijkstra(matrix, source, dist, parent, size);
        dist[source] = INT_MAX; //To prevent start to be nearest leaf
        destination = findNearestLeaf(leaves, dist, size, source);
        if (source == destination) destination = 0;
        newPath = createPath(source, destination, parent);
        start = updatePath(start, newPath);
        source = destination;
    } while(sumArray(leaves, size));
    return start;
}

struct Node* getRoute(struct Bogey train[15], int map[][15], int stations) 
{
    //parent array stores parent nodes in the graph
    //reqStations[i] is 1 if that station is to be visited, 0 otherwise
    int i, subgraph[15][15], dist[stations], reqStations[stations]; 
    int adjacencyMatrix[15][15], closestStation = 0, leaves[stations];
    int  parent[stations], j;

    clear(reqStations, stations);

    for (i = 0; i < 15; ++i)
        reqStations[train[i].station]++;

    //Create a subgraph of only the required stations
    createSubGraph(map, reqStations, stations, subgraph);
   
    //Attach source to subgraph
    dijkstra(map, 0, dist, parent, stations);
    dist[closestStation] = INT_MAX;
    for (i = 1; i < stations; ++i)
    {
        //Finding station closest to source in subgraph
        if (reqStations[i] && dist[closestStation] > dist[i])
            closestStation = i;
    }
    //Adding shortest path from 0 to closest station
    i = closestStation;
    while (i)
    {
        addEdge(subgraph, i, parent[i], map[i][parent[i]]);
        i = parent[i];
    }
    
    //Clearing parent to use in prim function
    for(i = 1; i < stations; ++i)
        parent[i] = -1;
        
    //And create an MST in the form of adjacency matrix for the subgraph
    prim(subgraph, parent, 0, stations);
    createMatrix(parent, stations, subgraph, adjacencyMatrix);
	
	//Find all leaf nodes
    findLeaves(parent, leaves, stations);

    //Remove all non-required leaves
    for(i = 0; i < stations; ++i) 
    	if (!reqStations[i] && i) leaves[i] = 0; 

    //Route consists of shortest paths to and from each leaf
    return createRoute(adjacencyMatrix, leaves, stations);
}

#endif
