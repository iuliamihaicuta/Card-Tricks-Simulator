#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "add_del.h"

#define uint unsigned int
#define MIN(a,b) (((a)<(b))?(a):(b))

void
shuffle_deck(doubly_linked_list_t *pack)
{
	uint deck_index, buff;
	if(validate_command(1, &deck_index, &buff) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
	
	doubly_linked_list_t *deck = 
	    ((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	if(deck->size < 2) {
		printf("The deck %d was successfully shuffled.\n", deck_index);
		return;
	}

	dll_node_t *node = deck->head;
	dll_node_t *tail = dll_get_nth_node(deck, deck->size - 1);
	uint mid = deck->size / 2 - 1;

	tail->next = node;
	node->prev = tail;

	node = dll_get_nth_node(deck, mid);
	deck->head = node->next;
	node->next->prev = NULL;
	node->next = NULL;

	printf("The deck %d was successfully shuffled.\n", deck_index);
}

void
reverse_deck(doubly_linked_list_t *pack)
{
	uint deck_index, buff;
	if(validate_command(1, &deck_index, &buff) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

	doubly_linked_list_t *deck = 
	    ((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	if(deck->size >= 2)
		for(uint i = 1; i < deck->size; ++i)
			dll_move_last(deck, deck->size - 1 - i);

	printf("The deck %d was successfully reversed.\n", deck_index);
}

void
merge_decks(doubly_linked_list_t *pack)
{
	uint deck_index1, deck_index2;
    if(validate_command(2, &deck_index1, &deck_index2) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	if(deck_index1 >= pack->size || deck_index2 >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

	dll_node_t *deck1 = dll_remove_nth_node(pack, deck_index1);
	dll_node_t *deck2;

	if(deck_index1 < deck_index2)
		deck2 = dll_remove_nth_node(pack, deck_index2 - 1);
	else 
		deck2 = dll_remove_nth_node(pack, deck_index2);

	doubly_linked_list_t *new_deck = dll_create(sizeof(card_t));

    dll_node_t *card1 = ((doubly_linked_list_t *)(deck1->data))->head;
    dll_node_t *card2 = ((doubly_linked_list_t *)(deck2->data))->head;

	while (card1 || card2) {
		if (card1 != NULL) {
			dll_add_nth_node(new_deck, new_deck->size, card1->data);
			card1 = card1->next;
		}

		if (card2 != NULL) {
			dll_add_nth_node(new_deck, new_deck->size, card2->data);
			card2 = card2->next;
		}

	}

	dll_free_list((doubly_linked_list_t **)(&(deck1->data)));
	free(deck1);

	dll_free_list((doubly_linked_list_t **)(&(deck2->data)));
	free(deck2);

	dll_add_nth_node(pack, pack->size, new_deck);
	free(new_deck);

	printf("The deck %d and the deck %d were successfully merged.\n", deck_index1, deck_index2);
}

void
deck_len(doubly_linked_list_t *pack)
{
	uint deck_index, buff;
	if(validate_command(1, &deck_index, &buff) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
	
	doubly_linked_list_t *deck = 
	    ((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	printf("The length of deck %d is %d.\n", deck_index, deck->size);
}

void
deck_number(doubly_linked_list_t *pack)
{
	uint buff1, buff2;
	if(validate_command(0, &buff1, &buff2) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	printf("The number of decks is %d.\n", pack->size);
}

void
split_deck(doubly_linked_list_t *pack)
{
	uint deck_index, split_index;
    if(validate_command(2, &deck_index, &split_index) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

    if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

	if(split_index == 0) {
		printf("The deck %d was successfully split by index %d.\n", deck_index, split_index);
		return;
	}
	
	dll_node_t *deck = dll_get_nth_node(pack, deck_index);

	dll_node_t *new_deck = new_node(sizeof(doubly_linked_list_t));
	free(new_deck->data);
	new_deck->data = dll_create(sizeof(card_t));

    if(pack->size != deck_index + 1) {
        deck->next->prev = new_deck;
        new_deck->next = deck->next;
        deck->next = new_deck;
        new_deck->prev = deck;
    } else {
        deck->next = new_deck;
        new_deck->prev = deck;
    }

	dll_node_t *card = dll_get_nth_node((doubly_linked_list_t *)(deck->data), split_index);
	card->prev->next = NULL;
	card->prev = NULL;
	((doubly_linked_list_t *)(new_deck->data))->head = card;
	((doubly_linked_list_t *)(new_deck->data))->size = 
        ((doubly_linked_list_t *)(deck->data))->size - split_index;
	((doubly_linked_list_t *)(deck->data))->size = split_index;

    (pack->size)++;

	printf("The deck %d was successfully split by index %d.\n", deck_index, split_index);
}

void
sort_deck(doubly_linked_list_t *pack)
{
	uint deck_index, buff;
	if(validate_command(1, &deck_index, &buff) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }

	if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

	doubly_linked_list_t *deck = 
	((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

	if(deck->head == NULL)
	return;

	dll_node_t *i, *j;

	for(i = deck->head; i->next != NULL; i = i->next) {
	    for(j = i->next; j != NULL; j = j->next) {
	        if(((card_t *)i->data)->value > ((card_t *)j->data)->value) {
	            int tmp = ((card_t *)i->data)->value;
                    ((card_t *)i->data)->value = ((card_t *)j->data)->value;
                    ((card_t *)j->data)->value = tmp;
	            }
	        }
	    }

	for(i = deck->head; i->next != NULL; i = i->next) {
        for(j = i->next; j != NULL; j = j->next) {
            if(((card_t *)i->data)->symbol > ((card_t *)j->data)->symbol) {
                int tmp = ((card_t *)i->data)->symbol;
                ((card_t *)i->data)->symbol = ((card_t *)j->data)->symbol;
                ((card_t *)j->data)->symbol = tmp;
            }
        }
	}

	printf("The deck %d was successfully sorted.\n", deck_index);  
}

void
free_pack(doubly_linked_list_t **pack)
{
	dll_node_t *deck;

	while((*pack)->size > 0) {
		deck = dll_remove_nth_node(*pack, 0);
		dll_free_list((doubly_linked_list_t **)(&(deck->data)));

		free(deck);
		deck = NULL;
	}
	dll_free_list(pack);
}