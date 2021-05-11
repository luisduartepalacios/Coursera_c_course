#include <stdio.h>

#define MAX_DATE_FEB 	28
#define MAX_DATE_30	 	30
#define MAX_DATE_31  	31 	

typedef enum month
{
	jan,
	feb,
	mar,
	apr,
	may,
	jun,
	jul,
	aug,
	sep,
	oct,
	nov,
	dec,
} month;

typedef struct date
{
	month m;
	int d;
}date;

/*	Functions prototype	*/
void next_day(date Date);
void print_date(date Date, char is_next_day);
int get_max_date(date Date);

int main()
{	
	date the_day_is;

	//February 28
	the_day_is.m = feb;
	the_day_is.d = 28;

	print_date(the_day_is, 0);
	next_day(the_day_is);
	printf("\n");

	//March 14
	the_day_is.m = mar;
	the_day_is.d = 14;

	print_date(the_day_is, 0);
	next_day(the_day_is);
	printf("\n");

	//October 31
	the_day_is.m = oct;
	the_day_is.d = 31;

	print_date(the_day_is, 0);
	next_day(the_day_is);
	printf("\n");

	//December 31
	the_day_is.m = dec;
	the_day_is.d = 31;

	print_date(the_day_is, 0);
	next_day(the_day_is);

	return 0;
}

/*	Function to get max date of the month	*/
int get_max_date(date Date)
{
	int max_date = 0;
	
	//If the month is February the max day is 28
	if(Date.m == feb)							
	{
		max_date = MAX_DATE_FEB;
	}
	//If the month is even and is from January to July the max day is 31
	else if( (!(Date.m % 2)) && (Date.m < aug))	
	{
		max_date = MAX_DATE_31;
	}
	//If the month is odd and is from August to December the max day is 31
	else if( (Date.m % 2) && (Date.m >= aug))	
	{
		max_date = MAX_DATE_31;
	}
	//The rest of months should have a max day of 30
	else										
	{
		max_date = MAX_DATE_30;
	}
	
	return max_date;
}

/*	Function to print the date	*/
void print_date(date Date, char is_next_day)
{
	char *str;

	//Set the string for the month, if it's not between 1 to 12 would be UNDEFINE
	switch(Date.m)				
	{
		case jan:
			str = "January";
			break;
		case feb:
			str = "February";
			break;	
		case mar:
			str = "March";
			break;
		case apr:
			str = "April";
			break;	
		case may:
			str = "May";
			break;
		case jun:
			str = "June";
			break;
		case jul:
			str = "July";
			break;
		case aug:
			str = "August";
			break;	
		case sep:
			str = "September";
			break;
		case oct:
			str = "October";
			break;	
		case nov:
			str = "November";
			break;
		case dec:
			str = "December";
			break;
		default:
			str = "UNDEFINE";
	}

	//If the function is set is_next_day != 0, the function will print "The next date will be ", otherwise "The date is "
	if (is_next_day)						
	{
		printf("The next date will be ");
	}
	else
	{
		printf("The date is ");
	}

	// Print the entire pointer value until the end of the string, which is equal to \0
	while(*str != ('\0'))
	{
		printf("%c",*str++);
	}

	// At the end it prints the day
	printf(", %d\n", Date.d);
}

/*	Function to print the next day	*/
void next_day(date Date)
{
	int max_date = 0;
	date next_day;

	max_date = get_max_date(Date);

	// If the actual day is not the max day of the month we add a +1 to the day and stay in the same month, otherwise we set the day as 1 because we go to the next month
	if(Date.d < max_date)
	{
		next_day.d = Date.d + 1;
		next_day.m = Date.m;
	}
	else
	{
		next_day.d = 1;

		// If we are in the max date and in december, we should change to January
		if(Date.m == dec)
		{
			next_day.m = jan;
		}
		//If we are in the max date and it's not December, we should increase the month +1
		else
			{
				next_day.m = Date.m + 1;
			}
	}
	
	print_date(next_day, 1);
}