// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED

#define uint unsigned int

typedef struct dll_node_t
{
    void* data;
    struct dll_node_t *prev, *next;
} dll_node_t;

typedef struct doubly_linked_list_t
{
    dll_node_t* head;
    uint data_size;
    uint size;
} doubly_linked_list_t;

typedef struct {
    uint value;
    char symbol;
} card_t;

dll_node_t*
new_node(uint data_size);

doubly_linked_list_t*
dll_create(uint data_size);

dll_node_t *
dll_get_nth_node(doubly_linked_list_t *l, uint n);

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n);

void 
dll_free_list(doubly_linked_list_t** pp_list);

void
dll_move_last(doubly_linked_list_t* list, uint n);

#endif