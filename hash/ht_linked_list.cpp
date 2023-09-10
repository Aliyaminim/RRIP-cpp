/* A C file that includes realization of the functions used in
   double linked list for hash table */

#include <iostream>
#include <cstdlib>
#include <assert.h>
//#include "../lru/lru.h"
#include "ht_linked_list.h"

using namespace std;

struct NodeHtLl {
    HtElem *elem;
    struct NodeHtLl *next;
};


NodeHtLl *ht_ll_create()
{
	NodeHtLl *list = (NodeHtLl *) calloc(1, sizeof(NodeHtLl));
    if (list == NULL) {
        cerr << "Memory exhausted\n";
        abort();
    }
	return list;
}

NodeHtLl *ht_ll_insert(NodeHtLl * list, HtElem * elem)
{
    assert(elem != NULL && "Code doesn't work correctly");

	if (!list) {
		NodeHtLl *head = ht_ll_create();
		head->elem = elem;
		head->next = NULL;
		list = head;
		return list;
	} else if (list->next == NULL) {
		NodeHtLl *node = ht_ll_create();
		node->elem = elem;
		node->next = NULL;
		list->next = node;
		return list;
	}

	NodeHtLl *temp = list;
	while (temp->next->next) {
		temp = temp->next;
	}

	NodeHtLl *node = ht_ll_create();
	node->elem = elem;
	node->next = NULL;
	temp->next->next = node;

	return list;
}

HtElem *ht_ll_remove(NodeHtLl * list)
{
	if (!list)
		return NULL;
	if (!list->next)
		return NULL;
	NodeHtLl *node = list->next;
	NodeHtLl *temp = list;
	temp->next = NULL;
	list = node;
	HtElem *it = NULL;
	temp->elem = it;
	//free(temp->elem->value);
	free(temp->elem);
	free(temp);
	return it;
}

void ht_ll_free(NodeHtLl * list)
{
	NodeHtLl *temp = list;
	while (list) {
		temp = list;
		list = list->next;
		free(temp->elem);
		free(temp);
	}
}