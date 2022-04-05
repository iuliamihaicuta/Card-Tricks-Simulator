#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

#define uint unsigned int

void
print_symbol(char c)
{
    if(c == 0)
        printf("CLUB\n");
    else if(c == 1)
        printf("DIAMOND\n");
    else if(c == 2)
        printf("SPADE\n");
    else
        printf("HEART\n");
}

void
show_deck(doubly_linked_list_t *pack, uint deck_index)
{
    if(deck_index >= pack->size) {
        printf("nu exista\n");
        return;
    }

    dll_node_t *deck = dll_get_nth_node(pack, deck_index);
    dll_node_t *card = ((doubly_linked_list_t *)(deck->data))->head;
    uint nr_cards = ((doubly_linked_list_t *)(deck->data))->size;

    printf("Deck %d:\n", deck_index);
    while (card != NULL) {
        printf("%d ", ((card_t *)card->data)->value);
        print_symbol(((card_t *)card->data)->symbol);

        card = card->next;
    }
}

void
show_all(doubly_linked_list_t *pack)
{
    dll_node_t *deck = pack->head;
    uint i = 0;

    while (deck != NULL) {
        show_deck(pack, i);
        ++i;
        deck = deck->next;
    }
}