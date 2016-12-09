#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>

// A utility function to find the vertex with minimum distance value, from the 
// set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[], int nodes) 
{
    int min = INT_MAX, min_index, v;
    for (v = 0; v < nodes; v++) 
    {
        if (!sptSet[v] && dist[v] <= min) 
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[][15], int src, int dist[], int parent[], int nodes) 
{
    int i, count, temporary, permanant;
    int sptSet[nodes]; 
    // sptSet[i] will 1 if vertex i is included in shortest path tree or 
    // shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and sptSet[] as 0
    for (i = 0; i < nodes; i++) 
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = i;
    }
    dist[src] = 0;

    for (count = 0; count < nodes-1; count++) 
    {
        permanant = minDistance(dist, sptSet, nodes);
        sptSet[permanant] = 1;
        for (temporary = 0; temporary < nodes; temporary++)
        {
            if 
            (
                !sptSet[temporary] &&
                graph[permanant][temporary] &&
                dist[permanant] != INT_MAX &&
                dist[permanant] + graph[permanant][temporary] < dist[temporary]
            ) {
                dist[temporary] = dist[permanant] + graph[permanant][temporary];
                parent[temporary] = permanant;
            }
        }
    }
}

void createSubGraph(int graph[][15], int nodes[], int size, int subgraph[][15]) 
{
    int i, j, dist[size], parent[size], current, prev;

    //Clear the subgraph
    for (i = 0; i < 15; ++i)
        for (j = 0; j < 15; ++j)
            subgraph[i][j] = 0;

    for (i = 0; i < size; ++i)
    {
        for (j = i + 1; j < size; ++j)
        {
            //Considering only required vertices
            if (nodes[i] && nodes[j]) 
            {
                //If direct edge exists, add to subgraph
                if (graph[i][j])
                {
                    subgraph[i][j] = graph[i][j];
                    subgraph[j][i] = graph[j][i];
                }
                //Otherwise find the shortest path and add to subgraph
                else 
                {
                    dijkstra(graph, i, dist, parent, size);
                    current = j;
                    prev = parent[current];

                    while(current != i) 
                    {
                        subgraph[prev][current] = graph[prev][current];
                        subgraph[current][prev] = graph[current][prev];
                        current = prev;
                        prev = parent[current];
                    }
                }
            }
        }
    }
}

#endif
