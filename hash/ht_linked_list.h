/* A header file to a C++ program that includes functions for linked list in hash table*/

#ifndef HT_LINKED_LIST_H_
#define HT_LINKED_LIST_H_

/* A Hash table element structure, which contains long integer data (could be page number) 
   and Node_t chain pointer value */
typedef struct HtElem HtElem;

/* A Hash table, contains the pointer to array of HtElem pointers and pointer to 
   array of Node Hash table Linked list pointers */
typedef struct HashTable HashTable;

/* A Node Hash table Linked list, contains hash table element pointer of element and 
   Node Hash table Linked list pointer to next element */
typedef struct NodeHtLl NodeHtLl;

/* creates linked list for hash table, returns a pointer to the node of linked list */
NodeHtLl *ht_ll_create();

/* inserts a hash table element to hash table linked list, takes the pointers to 
    the NodeHtl list and HtElem element, returns NodeHtLl pointer */
NodeHtLl *ht_ll_insert(NodeHtLl * list, HtElem * elem);

/* removes an element from hash table linked list, takes the pointer to NodeHtLl list,
   returns HtElem pointer */
HtElem *ht_ll_remove(NodeHtLl * list);

/* simply frees hash table linked list, takes NodeHtLL list pointer */
void ht_ll_free(NodeHtLl * list);

#endif