#ifndef STATION_H
#define STATION_H

// Funtion to add a valid edge to the adjacency matrix of the station map
void addEdge(int adjacencyMatrix[][15], int vertex1, int vertex2, int weight) 
{
    adjacencyMatrix[vertex1][vertex2] = weight;
    adjacencyMatrix[vertex2][vertex1] = weight;
}

// Checks validity of an edge. Returns 1 if edge already exists, 2 if invalid
// vertex or distance is entered and 0 if everything is valid
int checkEdge(int nodes, int matrix[][15], int vertex1, int vertex2, int weight) 
{
    int error;
    error =
        matrix[vertex1][vertex2] ? 1 : // Checking if edge already exists
        // Checking if vertices are valid
        vertex1 >= nodes || vertex2 >= nodes ? 2 : 
        vertex1 < 0 || vertex2 < 0 ? 2 :
        weight <= 0 ? 2 : //Checking if distance is positive
        vertex1 == vertex2 ? 2 : 0; //Checking for self-loops
    return error;
}

//Creates adjacencyMatrix of station map
void createStationMap(int nodes, int adjacencyMatrix[][15]) 
{
    int fromStation, toStation, distance, error;
    char dywtc[2];

    do 
    {
        //Enter Details
        printf("Enter From Station: ");
        scanf("%d", &fromStation);
        printf("Enter To Station: ");
        scanf("%d", &toStation);
        printf("Enter Distance: ");
        scanf("%d", &distance);

        //Display errors, if any
        error = 
            checkEdge(nodes, adjacencyMatrix, fromStation, toStation, distance);
        switch (error) 
        {
        case 1:
            printf("Edge already exists. Update(Y/n)? ");
            scanf("%s", dywtc);
            break;
        case 2:
            printf("Invalid Edge Entered\n");
            dywtc[0] = 'n';
            break;
        case 0:
            dywtc[0] = 'Y';
        }

        //Add edge
        if (dywtc[0] == 'Y' || dywtc[0] == 'y')
            addEdge(adjacencyMatrix, fromStation, toStation, distance);

        printf("Do you want to continue (Y/n)? ");
        scanf("%s", dywtc);
        printf("\n");
    } while (dywtc[0] == 'Y' || dywtc[0] == 'y');
}

//Displays the adjacency matrix of the station map
void displayStationMap(int nodes, int adjacencyMatrix[][15]) 
{
    int i, j;
    printf("Adjacency Matrix for Station Map:\n");
    for (i = 0; i < nodes; ++i) 
    {
        for (j = 0; j < nodes; ++j)
            printf("%d    ", adjacencyMatrix[i][j]);
        printf("\n");
    }
}

#endif
