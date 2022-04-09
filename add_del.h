// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef ADD_DEL_H_
#define ADD_DEL_H_

#define uint unsigned int

int
validate_command(uint nr_arg, uint *idx1, uint *idx2);

doubly_linked_list_t *
add_deck(doubly_linked_list_t *pack);

void
del_deck(doubly_linked_list_t *pack, uint verif, uint deck_index);

void
del_card(doubly_linked_list_t *pack);

void
add_cards(doubly_linked_list_t *pack);

#endif  // ADD_DEL_H_
