#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NUM_OF_SETS 100
#define MAX_NUM_ROWS 5

typedef struct list
{
	int data;
	struct list* next;
}list;

//Fucntions prototype
list* create_list(int d);
list* add_to_front(int d, list* h);
list* array_to_list(int d[], int size);
void print_list(list* h, char *title);
void get_rand_numbers(int d[], int size);
void swap(int *xp, int *yp);
void bubbleSort(int d[], int size);
void print_space(int size);

int main()
{
	list list_of_rand_int;
	list* head = NULL;
	int rand_data[NUM_OF_SETS] = {0};
	int size = sizeof(rand_data)/sizeof(rand_data[0]);
	get_rand_numbers(&(*rand_data), size);
	head = array_to_list(rand_data, size);
	print_list(head, "------------Original, random list------------");
	bubbleSort(&(*rand_data), size);
	head = array_to_list(rand_data, size);
	printf("\n");
	print_list(head, "-----------------Sorted list-----------------");
	return 0;
}

//Function for creating a list with dinamic memory
list* create_list(int d)
{
	list* head = malloc(sizeof(list));
	head -> data = d;
	head -> next = NULL;
	return head;
}

//Fucntion to add to the next list value
list* add_to_front(int d, list* h)
{
	list* head = create_list(d);
	head -> next = h;
	return head;
}

//Function to create a list base on an array
list* array_to_list(int d[], int size)
{
	list* head = create_list(d[0]);
	int i;
	
	for(i = 1; i < size; i++)
		head = add_to_front(d[i], head);

	return head;
}

//Function to print the list with a title
void print_list(list* h, char *title)
{
	int rows = 0;
	printf("%s\n", title);
	while(h != NULL)
	{
		//If the rows is in the max number, then jump to another line and set the row to 1
		if(rows == MAX_NUM_ROWS)
		{
			rows = 1;
			printf("\n");
		}
		//If not, add another one to the row
		else rows++;

		printf("%d  ", h -> data );
		print_space(h -> data);

		h = h -> next;
	}
}

//Function to have spaces and a better look in console
void print_space(int size)
{
		//Depending on the order of the size is the number of spaces
		if     ((size <= 100000) && (size > 10000));
		else if((size <= 10000)  && (size > 1000)) printf(" ");
		else if((size <= 1000)   && (size > 100)) printf("  ");
		else if((size <= 100)    && (size > 10)) printf("   ");
		else printf("    ");
		printf(": ");
}

//Function to get random number
void get_rand_numbers(int d[], int size)
{
	srand(time(NULL));
	for(int i = 0; i < size; i++) d[i] = rand();
}

//Fucntion to swap variables
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
//Function to implement bubble sort 
void bubbleSort(int d[], int size) 
{ 
    int i, j; 
    for (i = 0; i < size-1; i++)
    for (j = 0; j < size-i-1; j++) 
        if (d[j] > d[j+1]) 
            swap(&d[j], &d[j+1]); 
} 