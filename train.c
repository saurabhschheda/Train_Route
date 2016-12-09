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
    noOfStations = getStations();
    
    //Create Station Map
    printf("=============== CREATE STATION MAP ================\n");
    createStationMap(noOfStations, map);
    displayStationMap(noOfStations, map);

    //Enter Bogey Details
    printf("=============== ENTER BOGEY DETAILS ===============\n");
    enterBogeyDetails(train, noOfStations);
    displayBogeyDetails(train);

    //Route
    printf("====================== ROUTE ======================\n");
    displayRoute(getRoute(train, map, noOfStations));
}
