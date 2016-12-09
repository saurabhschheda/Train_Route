#ifndef BOGEY_H
#define BOGEY_H

struct Bogey 
{
    int bogeyID, itemID, station;
};

//Helper function to check if stations are vaild
int checkBogey(struct Bogey bogey, int nodes) 
{
    int error;
    error = bogey.station < 0 || bogey.station >= nodes ? 2 : 0;
    return error;
}

void enterBogeyDetails(struct Bogey train[15], int nodes) 
{
    int i;

    for (i = 0; i < 15;) 
    {
        train[i].bogeyID = i + 1;
        printf("Enter Bogey %d Details:\nEnter item ID: ", train[i].bogeyID);
        scanf("%d", &train[i].itemID);
        printf("Enter Station: ");
        scanf("%d", &train[i].station);

        if (checkBogey(train[i], nodes))
            printf("Invalid Station\n");
        
        else
            ++i;
        
        printf("\n");
    }
}

//Displays the bogey details
void displayBogeyDetails(struct Bogey train[15]) 
{
    int i;
    printf("Bogey Details:\nBogey\tItem\tStation\n");
    for (i = 0; i < 15; ++i)
    {
        printf("%d\t%d\t", train[i].bogeyID, train[i].itemID);
        printf("%d\n", train[i].station);
    }
}

#endif
