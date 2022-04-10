// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "add_del.h"

#define uint unsigned int

void
print_symbol(char c)
{
    if (c == 3)
        printf("CLUB\n");
    else if (c == 2)
        printf("DIAMOND\n");
    else if (c == 1)
        printf("SPADE\n");
    else
        printf("HEART\n");
}

void
show_deck(doubly_linked_list_t *pack, uint deck_index, uint verif)
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

    dll_node_t *deck = dll_get_nth_node(pack, deck_index);
    dll_node_t *card = ((doubly_linked_list_t *)(deck->data))->head;

    printf("Deck %d:\n", deck_index);
    while (card != NULL) {
        if (card->data != NULL) {
            printf("\t%d ", ((card_t *)card->data)->value);
            print_symbol(((card_t *)card->data)->symbol);
        }

        card = card->next;
    }
}

void
show_all(doubly_linked_list_t *pack)
{
    uint buff1, buff2;
    if (validate_command(0, &buff1, &buff2) == 0) {
        printf("Invalid command. Please try again.\n");
        return;
    }
    dll_node_t *deck = pack->head;
    uint i = 0;

    while (deck != NULL) {
        show_deck(pack, i, 1);
        ++i;
        deck = deck->next;
    }
}
