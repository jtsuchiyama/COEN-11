#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRY struct entry

struct entry
{
	char name[20];
	int size;
	ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;

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
	ENTRY *p, *temp;
	char answer[20];
	int duplicate;
	if((temp=((ENTRY *) malloc(sizeof(ENTRY))))==NULL) // Allocates memory and sends error message if there is not enough memory
	{
		printf("Out of memory \n");
		return;
	}
	temp->next=NULL;
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
		strcpy(temp->name,answer); // Saves the name only after no duplicate is found
		printf("How big is the party \n");
		scanf("%d", &temp->size); // Saves input as size	
		if(head==NULL) // List is empty
		{
			head=temp;
			tail=temp;
		}
		else // Every other situation 
		{
			tail->next=temp;
			tail=temp;
		}
	}
}

void delete()
{
	int flag=0;
	ENTRY *p=head;
	ENTRY *q=head;
	int opening;
	if(p==NULL)
	{
		printf("The list is empty \n");
		return;
	}
	printf("What is the size of the opening \n");
	scanf("%d", &opening); // Grabs the size of the opening
	while(p!=NULL)
	{
		if(p->size<=opening) // Works if a party can fit in the availible space
			{
				opening-=p->size;
				flag=1;
				if(head==tail) // Only one party in the list
				{
					head=NULL;
					tail=NULL;
				}
				else if(p==head) // Party is at beginning
				{
					head=head->next;		
				}
				else if(p==tail) // Party is at the end
				{
					q->next=NULL;
					tail=q;
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
	if(flag==0)
		printf("No applicable party found under the entered size \n");
	return;
}

void list()
{
	ENTRY *p=head;
	if(p==NULL) // Checks if the list is empty
	{
		printf("The list is empty \n");
		return;
	}
	while(p!=NULL)
	{
		printf("Party %s for %d people \n", p->name, p->size);
		p=p->next;
	}
}	

void search_size()
{
	int answer;
	int flag=0;
	ENTRY *p=head;
	if(p==NULL) // Checks if the list is empty
	{
		printf("The list is empty \n");
		return;
	}
	printf("What size opening would you like to search for \n");
	scanf("%d", &answer); // Grabs the opening to search for
	while(p!=NULL)
	{
		if(p->size<=answer) // Only prints if the party size is less than or equal to the inputted value
		{
			printf("Party %s for %d people \n", p->name, p->size);
			flag=1;
		}
		p=p->next;
	} 	 
	if(flag==0) // Occurs if no applicable party found
		printf("No applicable party found under the entered size \n");
}

int check_duplicate(char* answer)
{
	ENTRY *p=head;
	while(p!=NULL)
	{
		if(strcmp(answer,p->name)==0) // Returns 1 if duplicate, returns 0 if no duplicate
			return 1;
		p=p->next;
	}	
	return 0;
}
