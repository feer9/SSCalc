//
// Created by feer on 25/05/23.
//

#ifndef SSCALC_DOUBLE_LINKED_LISTS_H
#define SSCALC_DOUBLE_LINKED_LISTS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct operation;
typedef struct operation operation_t;

typedef struct dl_list_t {
	operation_t *d;

	struct dl_list_t *prev, *next;
} dl_list_t;

// create new node, returning newly alloc'd memory
dl_list_t *list_new_node(operation_t *data);

// inserts "node" to the end of "_list"
int list_insert_node(dl_list_t *node, dl_list_t **_list);

// put "node" at the beginning of "_list"
int list_prepend_node(dl_list_t *node, dl_list_t **_list);

// delete all elements of "_list"
void list_destroy(dl_list_t **_list);



#endif //SSCALC_DOUBLE_LINKED_LISTS_H
