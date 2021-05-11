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
