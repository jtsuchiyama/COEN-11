#include <stdio.h>
#include <string.h>

char name[10][20];
int size [10];
int counter=0;
void insert();
void delete();
void list();

int main()
{
	while (1) 
	{
		int input;
		printf("Restaurant Waiting List \n Menu \n 1 - Insert \n 2 - Delete \n 3 - List \n 0 - Quit \n");
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
	if(counter==10) // Checks if the waiting list is full
		printf("The waiting list is currently full. \n");
	else
	{
		printf("What is their name \n"); 
		scanf("%s", answer); // Grabs the name of the party
		for(i=0;i<10;i++) // This loop checks if there are duplicate names
		{
			if(strcmp(answer,name[i])==0)
			{
				printf("There is already a party under that name \n");
				flag=1;
				break;
			}
		}
		if (flag==0) // Only satisfied if there were no duplicates found 
		{
			printf("How many people are in that group \n");
			scanf("%d", &amount); // Grabs the size of the party
			if(amount==0) // Guarantees that the size of the party is greater than 0
				printf("There must be at least one person in a group\n");
			else
			{
				strcpy(name[counter], answer); // Only copies the party name once a proper group name and size is inputted
				size[counter]=amount; // Only copies the party size once a proper group name and size is inputted
				printf("The party under the name %s for %d has been put on the waiting list \n", name[counter], size[counter]); // Visual representation of what happened
				counter++; // Updates the amount of parties
			}
		}	
	}
}

void delete()
{
	int i, amount, j; 
	if(counter==0) // Checks if there are any parties on the waiting list 
		printf("There are no parties on the waiting list \n");
	else
	{
		printf("What is the size of the opening \n");
		scanf("%d", &amount); // Grabs the size of the opening
		if(amount==0) // Checks that the opening is bigger than zero
			printf("The opening must be bigger than zero \n");
		else
			for(i=0;i<counter;i++) 
			{
				if(amount>=size[i]) // Finds a suitable group
				{
					printf("The party under %s for %d has been seated \n", name[i], size[i]);
					amount-=size[i]; 
					for(j=i+1;j<counter;j++) // Shifts the name
					{
						strcpy(name[j-1], name[j]);
						size[j-1]=size[j];
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
	if(counter==0) // Checks if there are any parties on the waiting list
		printf("There are no parties on the waiting list \n");
	else
	{
		printf("LIST: \n");
		for(i=0; i<counter; i++) // Lists the parties
		{
			if(counter>i)
				printf("Party #%d: %s for %d people \n", i+1, name[i], size[i]);
			else
				printf("Party# %d: Free \n", i+1);
		}
	}	
}	
