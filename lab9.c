#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define ENTRY struct entry

struct entry
{
	char name[20];
	int size;
	ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;
pthread_mutex_t mutex;

void insert(char* answer, int answer_size);
void delete();
void list();
void search_size();
int check_duplicate(char* answer);
void read_file();
void save_file();
void list_backward();
void name_backward();
void traverse_list();
void clear();
void *auto_save (void*);
void read_auto_saved(char*);
void binary();

int main(int argc, char* argv[])
{
	char answer[20];
	int answer_size;
	ENTRY *p = head;		
	pthread_t thr;
	pthread_mutex_init (&mutex, NULL);
	pthread_create(&thr, NULL, auto_save, (void*) argv[2]);
	if(argc==1)
	{
		printf("The name of the file is missing \n");
		return 1;
	}
	if(argc==2)
	{	
		printf("The name of the file is missing \n");
		return 1;
	}
	read_file(argv[1]);
	while (1) 
	{
		int input;
		printf("Restaurant Waiting List \n Menu \n 1 - Insert \n 2 - Delete \n 3 - List \n 4 - Search Size \n 5 - List Backwards \n 6 - List Each Name Backwards \n 7 - Read the autosave file \n 0 - Quit \n");
		scanf("%d", &input);
		switch(input)
		{
			case 1:
				printf("What name is the party under \n");
				scanf("%s", answer); // Saves input to be checked by the dupliate function
				if(check_duplicate(answer)==1) // Checks for duplicate
				{
					printf("There is already a party under that name \n");
					break;
				}
				else
				{
					printf("How big is the party \n");
					scanf("%d", &answer_size);
					insert(answer, answer_size);
				}
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
			case 5:
				p = head;
				list_backward(p);
				break;
			case 6:
				traverse_list();			
				break;
			case 7:
				binary();
				break;
			case 0:
				printf("Quitting... \n");
				pthread_cancel(thr);
				save_file();
				return 0;
			default:
				printf("Invalid input \n");
				break;
		}
	}
}

void insert(char* answer, int answer_size)
{
	ENTRY *temp;
	if((temp=((ENTRY*) malloc(sizeof(ENTRY))))==NULL) // Allocates memory and sends error message if there is not enough memory
	{
		printf("Out of memory \n");
		return;
	}
	temp->next=NULL;
	strcpy(temp->name,answer); // Saves the name only after no duplicate is found
	temp->size=answer_size;	
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

void read_file()
{
	char answer[20];
	int answer_size;
	FILE *fp;
	if((fp=fopen("data.txt","r"))==NULL) // Ensures that the file is properly opened
	{
		printf("File not found \n");
		return;
	}
	while(fscanf(fp, "%s\t%d \n", answer, &answer_size)==2) // Grabs the data from the list in the same format assuming that two values are grabbed
	{
		insert(answer, answer_size);
	}
	fclose(fp);
	return;	
}

void save_file()
{
	FILE *fp;
	ENTRY *p;
	if((fp=fopen("data.txt","w"))==NULL) // Ensures that the file is properly opened
	{
		printf("File not found \n");
		return;
	}
	p=head;
	while(p!=NULL) // Saves the list in this format assuming there is a value for the list
	{
		fprintf(fp, "%s\t%d \n", p->name, p->size);
		p=p->next; 
	}
	p=head;
	clear(p);
	return;
}

void clear(ENTRY *p)
{
	if(p==NULL) // Base case when at the end of the list
		return;
	else
	{
		clear(p->next);
		free(p);	
	}
}

void list_backward(ENTRY*p)
{
	if(p==NULL) // Base case when at the end of the list
		return;
	else
	{
		list_backward(p->next);
		printf("Party %s for %d people \n",p->name, p-> size);
	}
	return;
}

void name_backward(char *letter)
{
	if(*letter=='\0') // Base case when at the end of the word array
		return;
	else
	{
		name_backward(++letter);
		letter--;
		printf("%c",*letter);
	}
	return;
}

void traverse_list()
{
	ENTRY *p = head;
	char *letter = p->name;
	while(p!=NULL) // Traverses the loop for the backward naming
	{
		letter = p->name;
		printf("Party ");
		name_backward(letter);
		printf("\n");
		p=p->next;
	}
	return;
}

void *auto_save(void* arg)
{
	sleep(3);
	char* file_name;
	file_name = (char*) arg;
	FILE* fp;
	ENTRY *p;
	while(1)
	{
		pthread_mutex_lock(&mutex); // Prevents other threads from accessing during the autosave
		fp=fopen(file_name,"wb");
		if(fp==NULL) // Checks that the file is properly opened
		{
			printf("Writing  error \n");
			return 0;
		}
		p=head;
		while(p!=NULL)
		{
			fwrite(p,sizeof(ENTRY), 1, fp); // Writes to the auto-save file
			p=p->next;
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex); // Allows other threads to access since the autosaving is complete
		printf("Autosave complete \n");
		sleep(15);
	}
	return 0;
}

void binary()
{
	FILE *fp;
	ENTRY temp;
	pthread_mutex_lock(&mutex); // Prevents other threads from accessing while the reading is occuring
	fp=fopen("data.bin","rb");
	if(fp==NULL) // Checks that the file is properly opened
	{
		printf("Reading error \n");
		pthread_mutex_unlock(&mutex);
		return;
	}
	while(fread(&temp,sizeof(ENTRY), 1,fp)==1)
	{
		printf("Party %s of  %d people \n", temp.name, temp.size);
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex); // Allows other threads to access since the reading is complete
	return;
}
