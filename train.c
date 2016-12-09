/*A goods train has 15 bogeys. Each bogey has a certain item that must be
unloaded at a particular railway station. Implement a system in which the items
are delivered to the stations efficiently and send the goods train back to
source station*/

#include <stdio.h>
#include "station.h"
#include "bogey.h"
#include "route.h"

#define MAX 15

//Helper function to get the number of stations from user
int getStations() 
{
    int noOfStations;
    printf("Enter Number of Stations: ");
    scanf("%d", &noOfStations);

    if (noOfStations <= 1) 
    {
        printf("Invalid Number of Stations\n");
        noOfStations = getStations();
    }

    return noOfStations;
}

//Helper function to display all stations
void displayStations(int number) 
{
    int i;
    printf("Stations: ");
    for (i = 0; i < number; ++i) 
        printf("%d ", i);
}

void main() 
{
    int noOfStations = 0, i, j, map[MAX][MAX];
    struct Bogey train[MAX];

    //Initialising map to 0
    for (i = 0; i < MAX; ++i)
        for (j = 0; j < MAX; ++j)
            map[i][j] = 0;

    printf("=============== TRAIN OPTIMISATION ================\n");

    //Enter number of stations
    //noOfStations = getStations();
    noOfStations = 13;
    displayStations(noOfStations);
    printf("\nSource Station: 0\n\n");

    //Create Station Map
    printf("=============== CREATE STATION MAP ================\n");
    //createStationMap(noOfStations, map);
    addEdge(map, 0, 1, 7);
    addEdge(map, 1, 2, 2);
    addEdge(map, 2, 5, 9);
    addEdge(map, 2, 4, 8);
    addEdge(map, 1, 3, 5);    
    addEdge(map, 1, 6, 1);
    addEdge(map, 6, 7, 11);   
    addEdge(map, 7, 10, 19);    
    addEdge(map, 6, 8, 3);    
    addEdge(map, 10, 8, 9);
    addEdge(map, 8, 9, 6);
    addEdge(map, 9, 11, 4);
    addEdge(map, 9, 12, 5);
    displayStationMap(noOfStations, map);

    //Enter Bogey Details
    printf("=============== ENTER BOGEY DETAILS ===============\n");
    //enterBogeyDetails(train, noOfStations);
    for (i = 0; i < 4; ++i)
    {
        train[i].bogeyID = i + 1;
        train[i].itemID = i + 1;
        train[i].station = 5;
    }
    for (i = 4; i < 8; ++i)
    {
        train[i].bogeyID = i + 1;
        train[i].itemID = i + 1;
        train[i].station = 7;
    }
    for (i = 8; i < 12; ++i)
    {
        train[i].bogeyID = i + 1;
        train[i].itemID = i + 1;
        train[i].station = 10;
    }
    for (i = 12; i < 15; ++i)
    {
        train[i].bogeyID = i + 1;
        train[i].itemID = i + 1;
        train[i].station = 12;
    }
    displayBogeyDetails(train);

    //Route
    printf("====================== ROUTE ======================\n");
    displayRoute(getRoute(train, map, noOfStations));
}
