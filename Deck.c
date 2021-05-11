#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS_DECK 		5
#define NUM_MAX_SUIT		4
#define NUM_MAX_PIP			13
#define MAX_COMBINATIONS 	1000000

long random_number = 0;

typedef enum suit
{
	spades,		// 0
	heart,		// 1
	diamond,	// 2
	clubs,		// 3
}suit;

typedef struct card
{
	suit suit_value;
	short pip_value;
}card;

typedef enum deck_result
{
	NO_PAIR,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
}deck_result;

//Functions prototype
void shuffle_deck(card *deck_to_shuffle);
int get_kind(card *deck);
void print_kind(int num);

int main()
{
	card Deck[NUM_CARDS_DECK] = {0};

	short proba = 0;
	unsigned long no_pair = 0, one_pair = 0, two_pairs = 0, three_pairs = 0, four_pairs = 0, full_house = 0;

	//Loop for generating n combinations base on the macro MAX_COMBINATIONS
	for(unsigned long combination = 0; combination < MAX_COMBINATIONS; combination++)
	{
		shuffle_deck(&(*Deck));
		proba = get_kind(&(*Deck));

		//If you wan to see the result of the suffle get_kind(), uncomment the next line
		//print_kind(proba);

		//Add one for the variable that represent the result
		switch(proba)
		{
			case NO_PAIR:
					no_pair++;
					break;
			case ONE_PAIR:
					one_pair++;
					break;
			case TWO_PAIR:
					two_pairs++;
					break;
			case THREE_OF_A_KIND:
					three_pairs++;
					break;
			case FOUR_OF_A_KIND:
					four_pairs++;
					break;
			case FULL_HOUSE:
					full_house++;
					break;
			default:
					//Do nothing
					break;
		}
	}

	//Print the results
	printf("Percentage of NO_PAIR         in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)no_pair/MAX_COMBINATIONS);
	printf("Percentage of ONE_PAIR        in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)one_pair/MAX_COMBINATIONS);
	printf("Percentage of TWO_PAIR        in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)two_pairs/MAX_COMBINATIONS);
	printf("Percentage of THREE_OF_A_KIND in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)three_pairs/MAX_COMBINATIONS);
	printf("Percentage of FULL_HOUSE      in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)full_house/MAX_COMBINATIONS);
	printf("Percentage of FOUR_OF_A_KIND  in a combination of %lu = %lf\n", MAX_COMBINATIONS, (double)four_pairs/MAX_COMBINATIONS);

	return 0;
}

//This functions generate random cards to the deck
void shuffle_deck(card *deck_to_shuffle)
{
    srand(time(NULL) + random_number++);

    int index_1, index_2;

    //This loop generates random numbers for the suits and the pips
	for(int Card = 0; Card < NUM_CARDS_DECK; Card++)
	{
		deck_to_shuffle[Card].suit_value = rand() % NUM_MAX_SUIT;
		deck_to_shuffle[Card].pip_value = rand() % NUM_MAX_PIP;
	}

	//This loop checks that the same card was generate twice, if so the fucntions goes to a recursion until all the cards are different
	for(index_1 = 0; index_1 < NUM_CARDS_DECK; index_1++)
	{
		for(index_2 = index_1 + 1; index_2 < NUM_CARDS_DECK; index_2++)
		{
			if(deck_to_shuffle[index_1].pip_value == deck_to_shuffle[index_2].pip_value)
			{
				if(deck_to_shuffle[index_1].suit_value == deck_to_shuffle[index_2].suit_value) shuffle_deck(&(*deck_to_shuffle));
			}
		}
	}
}

int get_kind(card *deck)
{
	int pip_card[NUM_MAX_PIP] = {0},  same_cards[NUM_MAX_PIP] = {0};
	int index_1, index_2, result;
	int no_pair = 0, one_pair = 0, two_pairs = 0, three_pairs = 0, four_pairs = 0, full_house = 0;

	// This loop check if any card in the deck is equal
	for(index_1 = 0; index_1 < NUM_CARDS_DECK; index_1++)
	{
		for(index_2 = index_1 + 1; index_2 < NUM_CARDS_DECK; index_2++)
		{
			if(deck[index_1].pip_value == deck[index_2].pip_value)
			{
				pip_card[deck[index_1].pip_value]++;
			}
		}
	}

	//Loop to check the number of occurency
	for(int i = 0; i < NUM_MAX_PIP; i++)
	{
		if(!(pip_card[i] % 2)) pip_card[i]= ((double)pip_card[i] / 1.5);

		if (pip_card[i] == 1) same_cards[i] += pip_card[i];
		else if (pip_card[i] == 2) same_cards[i] += pip_card[i];
		else if (pip_card[i] == 3) same_cards[i] += pip_card[i];
		else if (pip_card[i] == 4) same_cards[i] += pip_card[i];

		if 		(same_cards[i] == 0) no_pair++;
		else if (same_cards[i] == 1) one_pair++;
		else if (same_cards[i] == 2) two_pairs++;
		else if (same_cards[i] == 3) three_pairs++;
		else if (same_cards[i] == 4) four_pairs++;
	}

	// If somenthing is TRUE, we set the no pair variable to 0
	if(one_pair || two_pairs || three_pairs ||four_pairs) no_pair = 0;
	//If none of the variables are 1, we set the no pair variable to 1
	else if((!one_pair) && (!two_pairs) && (!three_pairs) && (!four_pairs)) no_pair = 1;

	// Conditions for the full house
	if(one_pair && three_pairs)
	{
		no_pair = one_pair = two_pairs = three_pairs = four_pairs = 0;
		full_house = 1;
	}
	// Condition for more than 1 pair
	else if(one_pair >> 1)
	{
		two_pairs = one_pair - 1;
		one_pair = 0;
	}

	//Send the result
	if(one_pair) 			result = ONE_PAIR;
	else if(two_pairs) 		result = TWO_PAIR;
	else if(three_pairs) 	result = THREE_OF_A_KIND;
	else if(full_house) 	result = FULL_HOUSE;
	else if(four_pairs) 	result = FOUR_OF_A_KIND;
	else 					result = NO_PAIR;

	return result;
}

//This function helps to print the result of the get_kind() function
void print_kind(int num)
{
	switch(num)
	{
		case NO_PAIR:
			printf("RESULT - The result is NO PAIR\n");
			break;
		case ONE_PAIR:
			printf("RESULT - The result is ONE PAIR\n");
			break;
		case TWO_PAIR:
			printf("RESULT - The result is TWO PAIR\n");
			break;
		case THREE_OF_A_KIND:
			printf("RESULT - The result is THREE OF A KIND\n");
			break;
		case FULL_HOUSE:
			printf("RESULT - The result is FULL HOUSE\n");
			break;
		case FOUR_OF_A_KIND:
			printf("RESULT - The result is FOUR OF A KIND\n");
			break;
	}
}