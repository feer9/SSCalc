//
// Created by feer on 25/05/23.
//

#include "double_linked_lists.h"


dl_list_t *list_new_node(operation_t *data)
{
	dl_list_t* new = (dl_list_t*) malloc(sizeof (dl_list_t));
	if(new == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new->d = data;
	new->prev = new->next = NULL;

	return new;
}

int list_insert_node(dl_list_t *node, dl_list_t **_list)
{
	if (node == NULL || _list == NULL)
		return -1;

	dl_list_t *list = *_list;

	node->next = NULL;


	if( list == NULL ) {
		*_list = node;
		node->prev = NULL;
	}
	else
	{
		dl_list_t *last = list;
		while(last->next != NULL)
			last = last->next;
		last->next = node;
	}
	return 0;
}

int list_prepend_node(dl_list_t *node, dl_list_t **_list)
{
	if (node == NULL || _list == NULL)
		return -1;

	dl_list_t *list = *_list;

	if( list != NULL ) {
		while (list->prev != NULL)
			list = list->prev;
		list->prev = node;
	}

	node->prev = NULL;
	node->next = list;

	*_list = node;
	return 0;
}

void list_destroy(dl_list_t **_list)
{
	if (_list == NULL) return;

	dl_list_t *node = *_list;

	while(node->prev)
		node = node->prev;

	while(node)
	{
		dl_list_t *tmp = node;
		node = node->next;
		if(tmp->d)
			free(tmp->d);
		free (tmp);
	}
	*_list = NULL;
}