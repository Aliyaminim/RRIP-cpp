/* A header file to a C program that includes functions used in
   hash table  */

#ifndef HT_FUNCTIONS_H_
#define HT_FUNCTIONS_H_

#include "ht_linked_list.h"
#include "../func.h"


/* dimension of hash table, that's prime number */
const long modular = 11;

/* simple hash_function, takes long integer data, returns hash of data */
long hash_function(const long data);

/* creates overflow list for hash table, takes a pointer of hash table, 
   returns the pointer to array of hash table linked list nodes */
NodeHtLl **create_overflow_list(const HashTable * table);

/* fully frees the overflow list, takes a pointer of hash table */
void free_overflow_list(const HashTable * table);

/* creates a hash table element, takes long integer dat and node_t value, 
   returns the pointer to an hash table element */
HtElem *create_elem(const long data, struct node_t * value);

/* creates hash table, returns the pointer of hash table */
HashTable *create_table();

/* fully frees the hash table, takes the pointer of hash table */
void free_table(HashTable * table);

/* solves a collision of hash table with overflow list, takes long integer data, 
   the pointer to hash table element and the pointer to hash table */
void solve_collision(const long index, HtElem * elem, HashTable * table);

/* inserts an element to the hash table, takes the pointer to hash table, long integer data 
   and node_t (chain) pointer */
void ht_insert(HashTable * table, const long data, struct node_t * value);

/* searches an element in the hash table, takes a pointer and long integer data needed 
   to be looked for, returns a pointer of node_t if found, otherwise NULL */
struct node_t *ht_search(HashTable * table, const long data);

/* deletes and element from the hash table with reconnecting of the other elements, 
   takes a pointer to the hash table and long integer data needed to be deleted */
void ht_delete(HashTable * table, const long data);

#endif