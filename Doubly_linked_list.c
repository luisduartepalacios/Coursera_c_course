#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NUM_ELEMENTS 200

typedef struct list
{
	int data;
	struct list* next;
	struct list* prev;
}list;

//Fucntions prototypes
void push(struct list** head_ref, int new_data);
void insertAfter(struct list* prev_list, int new_data);
void insertBefore(struct list** head_ref, struct list* next_list, int new_data);
void append(struct list** head_ref, int new_data);
void printList(struct list* the_list);
void removeDuplicateList(struct list* head);

int main()
{
	int counter = 0;
	srand(time(NULL) + counter++);

	struct list* head = NULL;

	//Create random numbers until NUM_ELEMENTS
	for(int i =0; i < NUM_ELEMENTS; i++)
	{
		push(&head, rand() % 49);
	}

	printf("\n------------------------------ORIGINAL LIST-------------------------------");
	printList(head);

	removeDuplicateList(head);

	printf("\n--------------------------REMOVED DUPLICATE LIST--------------------------");
	printList(head);


	return 0;
}

void push(struct list** head_ref, int new_data)
{
	//Allocate list
	struct list* new_list = (struct list*)malloc(sizeof(struct list));

	//Insert the data in
	new_list -> data = new_data;

	//Make next of new list as head and previous as NULL
	new_list -> next = (*head_ref);
	new_list -> prev = NULL;

	//Change prev of head list to new list
	if((*head_ref) != NULL)	(*head_ref) -> prev = new_list;

	//Move the head to point to the new list
	(*head_ref) = new_list;
}

void insertAfter(struct list* prev_list, int new_data)
{
	//Check if the given prev_list is NULL
	if(prev_list == NULL)
	{
		printf("The previous list is NULL");
		return;
	}

	//Allocate new list
	struct list* new_list = (struct list*)malloc(sizeof(struct list));

	//Put in the data
	new_list -> data = new_data;
	//Make next of new list as next of prev_list
	new_list -> next = prev_list -> next;
	//Make the next of prev_list as new_list
	prev_list -> next = new_list;
	//Make prev_list as previous of new_list
	new_list -> prev = prev_list;

	//Change previous of new_list's next list
	if(new_list -> next != NULL) new_list -> next -> prev = new_list;
}

void insertBefore(struct list** head_ref, struct list* next_list, int new_data)
{
	//Check if the given next_list is NULL
	if(next_list == NULL)
	{
		printf("The next list is NULL");
		return;
	}

	//Allocate new list
	struct list* new_list = (struct list*)malloc(sizeof(struct list));

	//Put in the data 
	new_list -> data = new_data;
	//Make prev of new list as prev of next_list
	new_list -> prev = next_list -> prev;
	//Make the prev of next_list as new_list
	next_list -> prev = new_list;
	//Make next_list as next of new_list
	new_list -> next = next_list;

	//Change next of new_list's previous list, otherwise if the prev of new_list is NULL, it will be the new head list
	if (new_list -> prev != NULL)	new_list -> prev -> next = new_list;
	else							(*head_ref) = new_list;
}

void append(struct list** head_ref, int new_data)
{
	//Allocate list
	struct list* new_list = (struct list*)malloc(sizeof(struct list));

	struct list* last_list = *head_ref;

	//Put the data into the list
	new_list -> data = new_data;

	//The new list becomes the last list
	new_list -> next = NULL;

	//If linked list is empty, the new list is the head
	if(*head_ref == NULL)
	{
		new_list -> prev = NULL;
		*head_ref = new_list;
		return;
	}

	//Else traverse till the last list
	while(last_list -> next != NULL)	last_list = last_list -> next;
	
	//Change the next of last list
	last_list -> next = new_list;

	//Make last list as previous of new list
	new_list -> prev = last_list;

	return;
}

// This function prints contents of linked list starting rom the given list
void printList(struct list* the_list)
{
	struct list* last_list;
	printf("\n-----------------------------FOWARD DIRECTION-----------------------------\n");
	while(the_list != NULL)
	{
		printf(" %d ", the_list -> data);
		last_list = the_list;
		the_list = the_list -> next;
	}

	printf("\n");
}

void removeDuplicateList(struct list* head) 
{  
    //List current will point to head  
    struct list *current, *index, *temp;  
      
    //Checks whether list is empty  
    if(head == NULL) 
    {  
        return;  
    }  
    else 
    {  
        //Initially, current will point to head 
        for(current = head; current != NULL; current = current->next) 
            //index will point to list next to current  
            for(index = current->next; index != NULL; index = index->next) 
                if(current->data == index->data) 
                {  
                    //Store the duplicate list in temp  
                    temp = index;  
                    //index's previous list will point to list next to index thus, removes the duplicate list  
                    index->prev->next = index->next;  
                    if(index->next != NULL)  index->next->prev = index->prev;  
                    //Delete duplicate list by making temp to NULL  
                    temp = NULL;  
                } 
    }  
}  