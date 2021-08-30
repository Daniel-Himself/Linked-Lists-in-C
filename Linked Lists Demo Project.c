/* Written by Daniel Sharon and Leen Abo Zidan */
#include <stdio.h>
#include <stdlib.h>

typedef struct contestant_t Contestant;
struct contestant_t {
	long Id;
	char First_Name[30];
	char Last_Name[30];
	double duration;
	Contestant * next;
}*race_res;


void InsertNewContestant (Contestant * tmp);
void GetNewData();
void CompareContestant(Contestant race_res);
void freeRace(Contestant* race);
void PrintRace();
Contestant* getContestantbyID(long id);
int getContestantRank(long id);
void DeleteContestant(long id);


int main()
{
    /* Variables to activate the GetNewData+Insert functions according to the amount of contestants requested */
    int numOfContestants=0, i;

    /* ID of the contestant to be deleted */
    long idForFunction;


    printf("Enter the number of contestants in the race:\n");

    /* Error check to force the input to be of an int type */
    if(!scanf("%d", &numOfContestants))
    {
        printf("Input Error!");
        return 1;
    }

    /* Error check to enforce using a positive number of contestants for the program to function properly */
    if(numOfContestants<1)
    {
        printf("Input Error!\n");
        return 1;
    }
    for(i=0 ; i<numOfContestants ; i++)
    {
        GetNewData();
    }

    /* Print the linked list in its entirety */
    PrintRace();

    printf("Enter an ID of a contestant\n");

    /* Error check to force the input to be of a long int type */
    if(!scanf("%ld", &idForFunction))
    {
        printf("Input Error!");
        return 1;
    }

    /* This statement activates the contestant deletion sequence only if a valid ID has been entered,*/
    /* else it prints that there's no such contestant and the info of the 1st place */
    if((getContestantbyID(idForFunction) != NULL) && (getContestantRank(idForFunction) > 0))
    {
        printf("%ld %s %s finished at the time of %.2f and finish in place: %d\n", getContestantbyID(idForFunction)->Id, getContestantbyID(idForFunction)->First_Name, getContestantbyID(idForFunction)->Last_Name, getContestantbyID(idForFunction)->duration, getContestantRank(idForFunction));
        printf("Contestant %ld was deleted\n", getContestantbyID(idForFunction)->Id);
        printf("Printing the contestant after deleting (section 8):\n");

       /* This statement prints the info of the contestant that follows the deleted one if he exists, else it prints the info of the contestant in the 1st place */
        if(getContestantbyID(idForFunction)->next!=NULL)
        {
             printf("%ld %s %s finished at the time of %.2f and finish in place: %d\n", getContestantbyID(idForFunction)->next->Id, getContestantbyID(idForFunction)->next->First_Name, getContestantbyID(idForFunction)->next->Last_Name, getContestantbyID(idForFunction)->next->duration, getContestantRank(idForFunction));
        }
        else
        {
            /* Print the info of the contestant in the 1st place in case the last place has been deleted */
            printf("%ld %s %s finished at the time of %.2f and finish in place: 1\n", race_res->Id, race_res->First_Name, race_res->Last_Name, race_res->duration);
        }
        DeleteContestant(idForFunction);

    }
    else
        {
            printf("No Such Contestant\nThere is no such contestant in the race\n");
            printf("Printing the contestant after deleting (section 8):\n");
            printf("%ld %s %s finished at the time of %.2f and finish in place: 1\n", race_res->Id, race_res->First_Name, race_res->Last_Name, race_res->duration);
        }

    /* Print out the entire contestant list after either a successful or an unsuccessful deletion */
    printf("Printing the Race (section 9):\n");
    PrintRace();


    /* Free the dynamically allocated memory of the contestant list */
    freeRace(race_res);
    return 0;
}

/* This function deletes the contestant with the ID given by the user input. Activates only for valid contestant ID's */
void DeleteContestant(long id)
{

    /* Pointers to three consecutive structs within the race_res list */
    Contestant* prev=race_res;
    Contestant* pointer=prev->next;
    Contestant* pointerNext=pointer->next;


    /* If the contestant to be deleted is in 1st place, delete him and set the list to start from 2nd place downwards */
    if(prev->Id==id)
    {
        race_res=pointer;
        free(prev);
        return;
    }

    /* Seek the ID of the contestant to be deleted in the 2nd place downwards*/
    while(pointer->Id != id)
    {
        prev=prev->next;
        pointer=pointer->next;
        pointerNext=pointerNext->next;
    }

    /* Once found, delete him from the contestant list */
    prev->next=pointerNext;
    free(pointer);


}



/* This functions points to the struct holding the info of the contestant corresponding to the ID given by the user input */
Contestant* getContestantbyID(long id)
{
    /* A pointer to the beginning of the contestant list */
    Contestant* pointer=race_res;

    /* Loop to scan the list until the struct containing the requested ID is found, then return it */
    while(pointer!=NULL)
    {
        if(pointer->Id==id)
        {
            return pointer;
        }
        pointer=pointer->next;
    }
    return pointer;

}

int getContestantRank(long id)
{
    /* A variable to follow the contestant to be checked in the loop below */
    int position=1;

    /* A pointer to the beginning of the contestant list */
    Contestant* head=race_res;

    /* Loop to scan the list until the struct containing the requested ID is found, then return its position (rank) */
    while(head!=NULL)
    {
        if(head->Id==id)
        {
            return position;
        }
        position++;
        head=head->next;
    }
    return -1;

}

/* This function receives a temporary struct from the GetNewData function and sorts it in a linked list by race duration in ascending order */
void InsertNewContestant (Contestant * tmp)
{
    /* A pointer to a Contestant struct to be given a pointed to the beginning of the race list in the 'else' statement below */
    Contestant* pointer;

    /* If the list is empty, place the temporary contestant as the first one in the list */
    if(race_res==NULL)
    {
        race_res=tmp;
    }

    else
    {
        pointer=race_res;

        /* A statement to position the second given temp contestant */
        if(pointer->next==NULL)
        {
            if(tmp->duration<=pointer->duration)
            {
                tmp->next=pointer;
                race_res=tmp;
            }
            else
            {
                pointer->next=tmp;
                tmp->next=NULL;
            }
        }

        /* These statements will position a third contestant in the right position and also the ones to follow */
        else
        {
            if(tmp->duration<pointer->duration)
            {
                race_res=tmp;
                tmp->next=pointer;
                return;
            }
            while(pointer->next!=NULL && pointer->next->duration < tmp->duration)
            {
                pointer = pointer ->next ;

            }

            tmp ->next = pointer->next ;
            pointer->next = tmp ;
        }
    }
}


/* This function receives data to be put into a Contestant struct and then forward it to be sorted in the contestant list*/
void GetNewData()
{
    /* A pointer to a struct, dynamically assigned memory of one "Contestant" type struct */
    Contestant *temp;
    if( (temp = (Contestant*)malloc(sizeof(Contestant))) == NULL )
    {
        printf("Allocation Error!\n");
        free(temp);
        exit(1);
    }

    /* Scan contestant info and store it inside the temporary struct */
    printf("Enter the contestant's first name:\n");
    scanf("%s", temp->First_Name);
    printf("Enter the contestant's last name:\n");
    scanf("%s", temp->Last_Name);
    printf("Enter the contestant's ID:\n");
    scanf("%ld", &temp->Id);
    printf("Enter the contestant's time in the race:\n");
    scanf("%lf", &temp->duration);

    /*Forward the temporary struct to the function that will sort it in the race list */
    InsertNewContestant (temp);

}

/* This functions frees the dynamically allocated memory of each struct within the linked list */
void freeRace(Contestant* race)
{
    if(race != NULL)
    {
        freeRace(race->next);
        free(race);
    }
}

/* This function prints out the current contestant list */
void PrintRace()
{
    /* Variable to follow the position of the printed contestant in the race */
    int position=1;

    /* A pointer to the beginning of the contestant race list */
    Contestant* head=race_res;

    /* Loop to print each contestant from the first one until the last one that is followed by NULL */
    while(head!=NULL)
    {
        printf("%ld %s %s finished at the time of %.2f and finish in place: %d\n",head->Id, head->First_Name, head->Last_Name, head->duration, position);
        position++;
        head=head->next;
    }
}
