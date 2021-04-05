#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRY struct entry
#define LIST struct list

struct entry
{
	char name[20];
	int size;
	ENTRY *next;
};

struct list
{
	ENTRY *head;
	ENTRY *tail;
};

LIST lists[4]={{NULL, NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};

void insert();
void delete();
void list();
void search_size();
int check_duplicate(char* answer);
void quit();

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
				quit();
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
	ENTRY *temp;
	char answer[20];
	int response;
	int duplicate;
	int which; // Determines which list temp is linked to
	if((temp=((ENTRY *) malloc(sizeof(ENTRY))))==NULL) // Allocates memory and sends error message if there is not enough memory
	{
		printf("Out of memory \n");
		return;
	}
	temp->next=NULL; // Ensures that the next for temp is not set to garbage data
	printf("What name is the party under \n");
	scanf("%s", answer); // Saves input to be checked by duplicate function
	duplicate=check_duplicate(answer); // Checks for duplicate
	if (duplicate==1)
	{
		printf("There is already a party under that name \n");
		free(temp);
		return;
	}
	else
	{
		printf("How big is the party \n");
		scanf("%d",&response);
		strcpy(temp->name,answer);
		temp->size=response;
		if(response==1||response==2) // Size is 1-2
		{
			which=0;
		}		
		else if(response==3||response==4) // Size is 3-4
		{
			which=1;
		}
		else if(response==5||response==6) //  Size is 5-6
		{
			which=2;
		}
		else if(response>6) // Size is greater than 6
		{
			which=3;
		}
		else // Size is invalid
		{
			printf("Invalid party size \n");
			return;
		}	
		if(lists[which].head==NULL) // List is empty
		{
			lists[which].head=temp;
			lists[which].tail=temp;
		}
		else // Every other situation 
		{
			lists[which].tail->next=temp;
			lists[which].tail=temp;
		}
	}
}

void delete()
{
	int i;
	ENTRY *p;
	ENTRY *q;
	int opening;
	printf("What is the size of the opening \n");
	scanf("%d", &opening); // Grabs the size of the opening
	for(i=0;i<4;i++) // Iterates through the different lists
	{
		p=q=lists[i].head;
		while(p!=NULL)
		{
			if(p->size<=opening) // Works if a party can fit in the availible space
			{
				opening-=p->size;
				if(lists[i].head==lists[i].tail) // Only one party in the list
				{
					lists[i].head=NULL;
					lists[i].tail=NULL;
				}
				else if(p==lists[i].head) // Party is at beginning
				{
					lists[i].head=lists[i].head->next;		
				}
				else if(p==lists[i].tail) // Party is at the end
				{
					q->next=NULL;
					lists[i].tail=q;
				}
				else // Party is in the middle
				{
					q->next=p->next;
				}
				printf("Party under %s for %d people was seated \n", p->name, p->size);
				free(p);
			}
		q=p;
		p=p->next;
		if(opening==0)
			return;
		}
	}	
	return;
}

void list()
{
	int i;
	ENTRY *p;
	for(i=0;i<4;i++) // Iterates through the lists
	{
		p=lists[i].head;
		if(i==0) // Traversing groups with 1-2 people
		{
			printf(" ----- \n Parties of 1-2 people: \n ----- \n");
		}
		else if(i==1) // Traversing groups with 3-4 people
		{
			printf(" ----- \n Parties of 3-4 people: \n ----- \n");
		}
		else if(i==2) // Traversing groups with 5-6 people
		{
			printf(" ----- \n Parties of 5-6 people: \n ----- \n");
		}
		else // Traversing groups with more than 6 people
		{
			printf(" ----- \n Parties of more than 6 people: \n ----- \n");
		}
		while(p!=NULL) 
		{
			printf("Party %s for %d people \n", p->name, p->size);
			p=p->next;
		}
	}
}	

void search_size()
{
	int answer; // Prevents from traversing an irrelevant list
	int which;
	ENTRY *p;
	int i;
	printf("What size opening would you like to search for \n");
	scanf("%d", &answer); // Grabs the opening to search for
	if(answer==1||answer==2) 
		which=0;
	else if(answer==3||answer==4)
		which=1;
	else if(answer==5||answer==6)
		which=2;
	else if(answer>6)
		which=3;
	else
	{
		printf("Invalid group size \n");
		return;
	}
	for(i=0;i<which+1;i++) // Iterates through the valid lists
	{
		p=lists[i].head;
		while(p!=NULL)
		{	
			if(p->size<=answer) // Only prints if the party size is less than or equal to the inputted value
			{
				printf("Party %s for %d people \n", p->name, p->size);
			}
			p=p->next;
		}	
	} 	 
}

int check_duplicate(char* answer)
{
	ENTRY *p;
	int i;
	for(i=0;i<4;i++) // Iterates through the lists
	{
		p=lists[i].head;
		while(p!=NULL)
		{
			if(strcmp(answer,p->name)==0) // Returns 1 if duplicate, returns 0 if no duplicate
				return 1;
			p=p->next;
		}
	}	
	return 0;
}

void quit()
{
	ENTRY *p;
	int i;
	for(i=0;i<4;i++) // Iterates through the lists
	{
		p=lists[i].head;
		while(p!=NULL)	
		{
			lists[i].head=lists[i].head->next;
			free(p);
			p=lists[i].head;
		}
	}
	printf("Memory freed \nQutting.... \n");	
}
