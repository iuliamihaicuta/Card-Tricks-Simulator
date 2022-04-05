#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

#define uint unsigned int

dll_node_t*
new_node(uint data_size)
{
    dll_node_t *node = (dll_node_t *)malloc(sizeof(*node));

    node->data = malloc(data_size);

    node->next = NULL;
    node->prev = NULL;

    return node;
}

doubly_linked_list_t*
dll_create(uint data_size)
{
    doubly_linked_list_t *list = (doubly_linked_list_t *)malloc(sizeof(doubly_linked_list_t));

    list->size = 0;
    list->head = NULL;
    list->data_size = data_size;

    return list;
}

dll_node_t *
dll_get_nth_node(doubly_linked_list_t *l, uint n)
{
    dll_node_t *tmp = l->head;
    if (n > l->size)
        n = l->size;
    
    for(uint i = 0; i < n; ++i)
        tmp = tmp->next;
    
    return tmp;
}

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    if ( n > list->size)
        n = list->size;

    dll_node_t *node = new_node(sizeof(data));
    memcpy(node->data, data, sizeof(*data));

    if(list->size == 0) {
        list->head = node;
    } else if(n == 0) {
        node->next = list->head;
    
        list->head = node;
    } else {
        dll_node_t *tmp = dll_get_nth_node(list, n);
        
        node->next = tmp;
        node->prev = tmp->prev;
        tmp->prev->next = node;
        tmp->prev = node;
    }

    (list->size)++;
}

dll_node_t *
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t *node, *prev;

    if (!list || !list->head) {
        return NULL;
    }

    /* n >= list->size - 1 inseamna eliminarea nodului de la finalul listei. */
    if (n > list->size - 1) {
        n = list->size - 1;
    }

    node = list->head;
    prev = NULL;
    while (n > 0) {
        prev = node;
        node = node->next;
        --n;
    }

    if (prev == NULL) {
        /* Adica n == 0. */
        list->head = node->next;
    } else {
        prev->next = node->next;
    }

    list->size--;

    return node;
}

void
dll_move_last(doubly_linked_list_t* list, uint n)
{
    dll_node_t *node = dll_remove_nth_node(list, n);
    dll_node_t *tail = dll_get_nth_node(list, list->size - 1);

    node->prev = tail;
    tail->next = node;
    node->next = list->head;
    list->head->prev = node;

    (list->size)++;
}

void
dll_free_list(doubly_linked_list_t** pp_list)
{
    dll_node_t* node;

    if (!pp_list || !*pp_list) {
        return;
    }

    while ((*pp_list)->size > 0) {
        node = dll_remove_nth_node(*pp_list, 0);
        free(node->data);
        node->data = NULL;
        free(node);
        node = NULL;
    }

    free(*pp_list);
    *pp_list = NULL;
}