#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

#define LEN_MAX 256
#define uint unsigned int

char
validate_command()
{
    char c, ok = 0;
    scanf("%c", &c);

    while(c != '\n') {
        if(c != ' ')
            ok = 1;
        scanf("%c", &c);
    }
    return ok;
}

dll_node_t*
get_card_value(dll_node_t *card)
{
    char symbol[LEN_MAX];
    int value;
    scanf("%d%s", &value, symbol);
    if (value < 0 || value > 14)
        value = 15;

    ((card_t *)(card->data))->value = (uint)value;

    if (strcmp(symbol, "HEART") == 0)
        ((card_t *)(card->data))->symbol = 3;
    else if (strcmp(symbol, "SPADE") == 0)
        ((card_t *)(card->data))->symbol = 2;
    else if (strcmp(symbol, "DIAMOND") == 0)
        ((card_t *)(card->data))->symbol = 1;
    else if (strcmp(symbol, "CLUB") == 0)
        ((card_t *)(card->data))->symbol = 0;
    else
       ((card_t *)(card->data))->value = 15;

    return card;
}

void read_cards(uint n)
{
    dll_node_t *card = new_node(sizeof(card_t));

    for(uint i = 0; i < n; ++i)
        card = get_card_value(card);

    free(card->data);
    free(card);
}

doubly_linked_list_t *
add_deck(doubly_linked_list_t *pack)
{
    uint nr_cards;
    scanf("%d", &nr_cards);

    if(validate_command() != 0) {
        printf("Invalid command\n");
        return pack;
    }
    
    dll_node_t *new_deck = new_node(sizeof(doubly_linked_list_t));
    free(new_deck->data);
    new_deck->data = dll_create(sizeof(card_t));

    dll_node_t *card = new_node(sizeof(card_t));
    ((doubly_linked_list_t *)(new_deck->data))->size = 0;

    card = get_card_value(card);
    while(((card_t *)(card->data))->value == 15) {
        card = get_card_value(card);
        printf("The provided card is not a valid one.\n");
    }
    ++(((doubly_linked_list_t *)(new_deck->data))->size);
    ((doubly_linked_list_t *)(new_deck->data))->head = card;

    for (uint i = 0; i < nr_cards - 1; ++i) {

        dll_node_t *new_card = new_node(sizeof(card_t));
        new_card = get_card_value(new_card);
        if(((card_t *)(new_card->data))->value == 15) {
            new_card = get_card_value(new_card);
            printf("The provided card is not a valid one.\n");
        }

        card->next = new_card;
        new_card->prev = card;

        card = card->next;
        ((doubly_linked_list_t *)(new_deck->data))->size++;
    }

    if(pack->size == 0)
        pack->head = new_deck;
    else {
        dll_node_t *deck = pack->head;

        while(deck->next != NULL)
            deck = deck->next;
        deck->next = new_deck;
    }
    (pack->size)++;

    printf("The deck was successfully created with %d cards.\n", nr_cards);
    return pack;
}

void
del_deck(doubly_linked_list_t *pack, uint verif)
{
    uint deck_index;
    if (verif == 0) {
        scanf("%d", &deck_index);

        if(deck_index >= pack->size) {
            printf("The provided index is out of bounds for the deck list.\n");
            return;
        }
    } else {
        deck_index = verif;
    }

    dll_node_t *deck = dll_remove_nth_node(pack, deck_index);
    dll_free_list((doubly_linked_list_t **)(&(deck->data)));
    
    free(deck);
    deck = NULL;

    if(verif == 0)
        printf("The deck %d was successfully deleted.\n", deck_index);

}

void
del_card(doubly_linked_list_t *pack)
{
    uint deck_index, card_index;
    scanf("%d%d", &deck_index, &card_index);
    
    if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    
    doubly_linked_list_t *deck = 
        ((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

    if(card_index >= deck->size) {
        printf("The provided index is out of bounds for deck %d.\n", deck_index);
        return;
    }

    if(deck->size == 1) {
        del_deck(pack, deck_index);
    } else {
        dll_node_t *card = dll_remove_nth_node(deck, card_index);

        free(card->data);
        free(card);
    }

    printf("The card was successfully deleted from deck %d.\n", deck_index);
}

void
add_cards(doubly_linked_list_t *pack)
{
    uint deck_index, nr_cards;
    scanf("%d%d", &deck_index, &nr_cards);

    if(deck_index >= pack->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    
    doubly_linked_list_t *deck = 
        ((doubly_linked_list_t *)(dll_get_nth_node(pack, deck_index)->data));

    dll_node_t *card = dll_get_nth_node(deck, deck->size - 1);
    
    for(uint i = 0; i < nr_cards; ++i) {
        dll_node_t *new_card = new_node(sizeof(card_t));
        new_card = get_card_value(new_card);

        card->next = new_card;
        new_card->prev = card;

        card = card->next;
        (deck->size)++;
    }
    printf("The cards were successfully added to deck %d.\n", deck_index);
}

