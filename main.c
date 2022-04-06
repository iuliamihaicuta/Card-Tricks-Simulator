#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "add_del.h"
#include "show.h"
#include "operation.h"

#define LEN_MAX 256
#define uint unsigned int

int main()
{
    doubly_linked_list_t *pack;
    pack = dll_create(sizeof(doubly_linked_list_t));
    char command[LEN_MAX];

    uint verif = 1;
    while (verif)
    {
        scanf("%s", command);
        if (strcmp(command, "ADD_DECK") == 0) {
            add_deck(pack);
        } else if (strcmp(command, "DEL_DECK") == 0) {
            del_deck(pack, 0);
        } else if (strcmp(command, "DEL_CARD") == 0) {
            del_card(pack);
        } else if (strcmp(command, "ADD_CARDS") == 0) {
            add_cards(pack);
        } else if (strcmp(command, "DECK_NUMBER") == 0) {
            printf("The number of decks is %d.\n", pack->size);
        } else if (strcmp(command, "DECK_LEN") == 0) {
            deck_len(pack);
        } else if (strcmp(command, "SHUFFLE_DECK") == 0) {
            shuffle_deck(pack);
        } else if (strcmp(command, "MERGE_DECKS") == 0) {
            merge_decks(pack);
        } else if (strcmp(command, "SPLIT_DECK") == 0) {
            split_deck(pack);
        } else if (strcmp(command, "REVERSE_DECK") == 0) {
            reverse_deck(pack);
        } else if (strcmp(command, "SHOW_DECK") == 0) {
            int index;
            scanf("%d", &index);
            show_deck(pack, index);
        } else if (strcmp(command, "SHOW_ALL") == 0) {
            show_all(pack);
        } else if (strcmp(command, "EXIT") == 0) {
            verif = 0;
        } else if (strcmp(command, "SORT_DECK") == 0) {
            sort_deck(pack);
        } else
            printf("Invalid command. Please try again.\n");
    }

    free_pack(&pack);

    return 0;
}