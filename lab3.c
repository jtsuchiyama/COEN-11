#include <stdio.h>
#include <string.h>

#define SIZE 10 // Amount of appointments
#define LENGTH 20 // Max length of a name

typedef struct entry
{
	char name[LENGTH];
	int size;
}ENTRY;

ENTRY nlist[SIZE];
int counter=0;

void insert();
void delete();
void list();
void search_size();
int check_duplicate(char* answer);

int main()
{
	while (1) 
	{
		int input;
		printf("Restaurant Waiting List \n Menu \n 1 - Insert \n 2 - Delete \n 3 - List \n 4 - Search Size \n 0 - Quit \n");
		scanf("%d", &input);
		switch(input)
		{
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			case 4:
				search_size();
				break;

			case 0:
				printf("Quitting... \n");
				return 0;
			default:
				printf("Invalid input \n");
				break;
		}
	}
}

void insert()
{
	int i;
	int flag=0;
	char answer[20];
	int amount;
	ENTRY *p = &nlist[counter];
	if(counter==10) // Checks if the waiting list is full
		printf("The waiting list is currently full. \n");
	else
	{
		printf("What is their name \n"); 
		scanf("%s", answer); // Grabs the name of the party
		flag=check_duplicate(answer); // Returns 1 if no duplicates found, returns 0 if a duplicate was found
		if (flag==1) // Only satisfied if there were no duplicates found 
		{
			printf("How many people are in that group \n");
			scanf("%d", &amount); // Grabs the size of the party
			if(amount==0) // Guarantees that the size of the party is greater than 0
				printf("There must be at least one person in a group\n");
			else
			{	
				strcpy(p->name, answer); // Only copies the party name once a proper group name and size is inputted
				p->size=amount; // Only copies the party size once a proper group name and size is inputted
				printf("The party under the name %s for %d has been put on the waiting list \n", p->name, p->size); // Visual representation of what happened
				counter++; // Updates the amount of parties
			}
		}
		else
			printf("There is already a party under that name \n");	
	}
}

void delete()
{
	int i, amount, j;
	ENTRY *p = nlist; 
	ENTRY *q = nlist;
	if(counter==0) // Checks if there are any parties on the waiting list 
		printf("There are no parties on the waiting list \n");
	else
	{
		printf("What is the size of the opening \n");
		scanf("%d", &amount); // Grabs the size of the opening
		if(amount==0) // Checks that the opening is bigger than zero
			printf("The opening must be bigger than zero \n");
		else
			for(i=0;i<counter;i++,p++) 
			{
				p = &nlist[i];
				if(amount>=p->size) // Finds a suitable group
				{
					printf("The party under %s for %d has been seated \n", p->name, p->size);
					amount-=p->size; 
					for(j=i+1;j<counter;j++) // Shifts the name
					{
						p = &nlist[j];
						q = &nlist[j-1];
						strcpy(q->name, p->name);
						q->size=p->size;
					}
					counter--; // Updates the amount of parties
					i--; // Accounts for the movement of the people
				}
				if(amount==0) // Breaks the loop if there are no spaces in the opening
					break; 
			}
	}
}

void list()
{
	int i;
	ENTRY *p = nlist;
	if(counter==0) // Checks if there are any parties on the waiting list
		printf("There are no parties on the waiting list \n");
	else
	{
		printf("LIST: \n");
		for(i=0; i<counter; i++,p++) // Lists the parties
		{
			if(counter>i)
				printf("Party #%d: %s for %d people \n", i+1, p->name, p->size);
			else
				printf("Party #%d: Free \n", i+1);
		}
	}	
}	

void search_size()
{
	int amount, i;
	ENTRY *p = nlist;
	if(counter==0) // Checks if there are any parties on the waiting list
		printf("There are no parties on the waiting list \n");
	else
	{
		printf("What party size do you want to search for? \n");
		scanf("%d", &amount); // Grabs the party size to search for
		for(i=0;i<counter;i++)
		{
			p = &nlist[i];
			if(p->size<=amount) // If the party size is less than the grabbed amount, it will list the party
				printf("Party #%d: %s for %d people \n", i+1, p->name, p->size);
		}
	}
	 
}

int check_duplicate(char* answer)
{
	int i;
	ENTRY *p = nlist;
	for(i=0;i<counter;i++, p++) // Loops through the listed parties
	{
		if((strcmp(answer,p->name))==0) 
			return 0; // Returns 0 if a duplicate is found
	}
	return 1; // Returns 1 if no duplicates are found
}
