// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

#define LEN_MAX 256
#define uint unsigned int

// check that the command is entered correctly
int
validate_command(uint nr_arg, uint *idx1, uint *idx2)
{
	char line[LEN_MAX];
	fgets(line, LEN_MAX, stdin);

	line[strlen(line) - 1] = '\0';

	// divides the line into arguments and checks their number
	char *buff;
	buff = strtok(line, " ");
	if (buff == NULL) {
		if (nr_arg == 0)
			return 1;
		return 0;
	} else if (nr_arg == 0) {
		return 0;
	}

	*idx1 = atoi(buff);

	buff = strtok(NULL, " ");
	if (buff == NULL) {
		if (nr_arg == 1)
			return 1;
		return 0;
	} else if (nr_arg == 1) {
		return 0;
	}

	*idx2 = atoi(buff);

	buff = strtok(NULL, " ");
		if (buff != NULL)
			return 0;

	return 1;
}

// get the card values
card_t
get_card_value()
{
	card_t card;
	char symbol[LEN_MAX];
	int value;

	char line[LEN_MAX];
	fgets(line, LEN_MAX, stdin);

	line[strlen(line) - 1] = '\0';

	// read the attributes of the card and see if they are correct
	char *buff;
	buff = strtok(line, " ");
	if(buff == NULL) {
		card.value = 15;
		return card;
	}
	value = atoi(buff);

	buff = strtok(NULL, " ");
	if(buff == NULL) {
		card.value = 15;
		return card;
	}
	strcpy(symbol, buff);

	buff = strtok(NULL, " ");
	if(buff != NULL) {
		card.value = 15;
		return card;
	}


	if (value < 0 || value > 14)
		value = 15;

	card.value = (uint)value;

	// give each symbol the corresponding number
	if (strcmp(symbol, "HEART") == 0)
		card.symbol = 0;
	else if (strcmp(symbol, "SPADE") == 0)
		card.symbol = 1;
	else if (strcmp(symbol, "DIAMOND") == 0)
		card.symbol = 2;
	else if (strcmp(symbol, "CLUB") == 0)
		card.symbol = 3;
	else
	   card.value = 15;

	return card;
}

// add a deck at the end of the package
doubly_linked_list_t *
add_deck(doubly_linked_list_t *pack)
{
	uint nr_cards, buff;

	if (validate_command(1, &nr_cards, &buff) == 0) {
		printf("Invalid command. Please try again.\n");
		return pack;
	}

	doubly_linked_list_t *new_deck = dll_create(sizeof(card_t));

	// adds cards to the package
	card_t card;
	for(uint i = 0; i < nr_cards; ++i) {
		card = get_card_value();
		while (card.value == 15) {
			card = get_card_value();
			printf("The provided card is not a valid one.\n");
		}

		dll_add_nth_node(new_deck, new_deck->size, (void *)&card);
	}


	// adds deck to the package
	dll_add_nth_node(pack, pack->size, new_deck);
	free(new_deck);

	printf("The deck was successfully created with %d cards.\n", nr_cards);
	return pack;
}

/* deletes a deck from the pack
verif == 1 if the function is called from del_card */
void
del_deck(doubly_linked_list_t *pack, uint verif, uint deck_index)
{
	if (verif == 0) {
		uint buff;
		if (validate_command(1, &deck_index, &buff) == 0) {
			printf("Invalid command. Please try again.\n");
			return;
		}

		if (deck_index >= pack->size) {
			printf("The provided index is out of bounds for the deck list.\n");
			return;
		}
	}

	// the deck is removed from the pack and the freed
	dll_node_t *deck = dll_remove_nth_node(pack, deck_index);

	if(deck != NULL && deck->data != NULL) {
		dll_free_list((doubly_linked_list_t **)(&(deck->data)));
	}

	free(deck);
	deck = NULL;

	if (verif == 0)
		printf("The deck %d was successfully deleted.\n", deck_index);
}

// delete a card from a specified package
void
del_card(doubly_linked_list_t *pack)
{
	// read the command and check if the index is out of bounds
	uint deck_index, card_index;
	if (validate_command(2, &deck_index, &card_index) == 0) {
		printf("Invalid command. Please try again.\n");
		return;
	}

	if (deck_index >= pack->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	doubly_linked_list_t *deck =
		((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	if (card_index >= deck->size) {
		printf("The provided index is out of bounds for deck %d.\n", deck_index);
		return;
	}

	// if the deck has only one item, it is deleted
	if (deck->size == 1) {
		del_deck(pack, 1, deck_index);
	} else {
		// remove the card and free the memory
		dll_node_t *card = dll_remove_nth_node(deck, card_index);

		if(card != NULL) {
			if(card->data != NULL)
				free(card->data);
			free(card);
		}
	}

	printf("The card was successfully deleted from deck %d.\n", deck_index);
}

// add cards to a specific package
void
add_cards(doubly_linked_list_t *pack)
{
	// read the command and check if the index is out of bounds
	uint deck_index, nr_cards;
	if (validate_command(2, &deck_index, &nr_cards) == 0) {
		printf("Invalid command. Please try again.\n");
		return;
	}

	if (deck_index >= pack->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	doubly_linked_list_t *deck =
		((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	// read the cards and see if they are valid
	card_t card;
	for(uint i = 0; i < nr_cards; ++i) {
		card = get_card_value();
		while (card.value == 15) {
			card = get_card_value();
			printf("The provided card is not a valid one.\n");
		}

		dll_add_nth_node(deck, deck->size, (void *)&card);
	}

	printf("The cards were successfully added to deck %d.\n", deck_index);
}

