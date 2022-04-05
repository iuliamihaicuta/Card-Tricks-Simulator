// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef ADD_DEL_H_INCLUDED
#define ADD_DEL_H_INCLUDED

#define uint unsigned int

dll_node_t*
get_card_value(dll_node_t *card);

doubly_linked_list_t *
add_deck(doubly_linked_list_t *pack);

void
del_deck(doubly_linked_list_t *pack, uint verif);

void
del_card(doubly_linked_list_t *pack);

void
add_cards(doubly_linked_list_t *pack);

#endif