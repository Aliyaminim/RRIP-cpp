/* A C++ file that includes realization of the functions used in
   hash table */

#include <iostream>
#include <cstdlib>
#include <assert.h>
//#include "../lru/lru.h"
#include "ht_functions.h"

using namespace std;

struct HtElem {
    long data;
    struct node_t *value;
};

struct HashTable {
    HtElem **elems;
    NodeHtLl **overflow_list;
};

struct NodeHtLl {
    HtElem *elem;
    struct NodeHtLl *next;
};

long hash_function(const long data)
{
	return (data % modular);
}

NodeHtLl **create_overflow_list(const HashTable * table)
{
	assert(table != NULL);

	NodeHtLl **buckets = (NodeHtLl **) calloc(modular, sizeof(NodeHtLl *));
	if (buckets == NULL) {
		cerr << "Memory exhausted\n";
        abort();
    }
	return buckets;
}

void free_overflow_list(const HashTable * table)
{
	assert(table != NULL);

	NodeHtLl **buckets = table->overflow_list;
	for (int i = 0; i < modular; ++i)
		ht_ll_free(buckets[i]);
	free(buckets);
}

HtElem *create_elem(const long data, struct node_t * value)
{
	HtElem *elem = (HtElem *)calloc(1, sizeof(HtElem));
	if (elem == NULL) {
        fprintf(stderr, "Memory exhausted\n");
        abort();
    }
	elem->data = data;
	elem->value = value;

	return elem;
}

HashTable *create_table()
{
	HashTable *table = (HashTable *) calloc(1, sizeof(HashTable));
	table->elems = (HtElem **) calloc(modular, sizeof(HtElem *));

	if (table == NULL || table->elems == NULL) {
		cerr << "Memory exhausted\n";
        abort();
    }
	table->overflow_list = create_overflow_list(table);

	return table;
}

void free_table(HashTable * table)
{
	assert(table != NULL);

	for (int i = 0; i < modular; ++i) {
		HtElem *elem = table->elems[i];
		free(elem);
	}

	free_overflow_list(table);
	free(table->elems);
	free(table);
}

void solve_collision(const long index, HtElem * elem, HashTable * table)
{
	assert((elem != NULL) && (table != NULL));

	NodeHtLl *head = table->overflow_list[index];

	if (head == NULL) {
		head = ht_ll_create();
		head->elem = elem;
		table->overflow_list[index] = head;
		return;
	} else {
		table->overflow_list[index] = ht_ll_insert(head, elem);
		return;
	}
}

void ht_insert(HashTable * table, const long data, struct node_t * value)
{
	assert((table != NULL) && (value != NULL) && ("Code doesn't work correctly"));

	HtElem *elem = create_elem(data, value);

	unsigned long index = hash_function(data);

	HtElem *current_elem = table->elems[index];

	if (current_elem == NULL) {
		table->elems[index] = elem;
	} else {
		if (current_elem->data == data) {
			//is it vital?
		} else {
			solve_collision(index, elem, table);
			return;
		}
	}
}

struct node_t *ht_search(HashTable * table, const long data)
{
	assert(table != NULL);

	int index = hash_function(data);
	HtElem *elem = table->elems[index];
	NodeHtLl *head = table->overflow_list[index];

	

	while (elem != NULL) {
		if (elem->data == data)
			return elem->value;
		if (head == NULL)
			return NULL;
		elem = head->elem;
		head = head->next;
	}
	return NULL;
}

void ht_delete(HashTable * table, const long data)
{
	assert(table != NULL);

	int index = hash_function(data);
	HtElem *elem = table->elems[index];
	NodeHtLl *head = table->overflow_list[index];

	if (elem == NULL) {
		return;
	} else {
		if (head == NULL && elem->data == data) {
			//No collision chain
			table->elems[index] = NULL;
			free(elem);
			return;
		} else if (head != NULL) {
			//There is a collision chain
			if (elem->data == data) {
				free(elem);
				NodeHtLl *node = head;
				head = head->next;
		
				node->next = NULL;
				//
				table->elems[index] = create_elem(node->elem->data, node->elem->value);
				ht_ll_free(node);
				table->overflow_list[index] = head;
				return;
			}

			NodeHtLl *curr = head;
			NodeHtLl *prev = NULL;

			while (curr) {
				if (curr->elem->data == data) {
					if (prev == NULL) {
						//First element of the chain. Remove the chain
						//
						table->overflow_list[index] = head->next;
						head->next = NULL;
						ht_ll_free(head);
						return;
					} else {
						//Somewhere in the chain
						prev->next = curr->next;
						curr->next = NULL;
						ht_ll_free(curr);
						table->overflow_list[index] = head;
						return;
					}
				}
				//
				prev = curr;
				curr = curr->next;
			}

		}
	}
}