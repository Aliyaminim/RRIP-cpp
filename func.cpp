/* A C++ file that includes realization of the functions used in
   Static Re-Reference Interval Prediction(RRIP) Cache Replacement */

#include <iostream>
#include <cstdlib>
#include <assert.h>
#include "func.h"
using namespace std;

static const int RRIPval_DIST = 3;
static const int RRIPval_LONG = 2;
static const int RRIPval_NEAR = 0;

struct node_t {
    struct node_t *next, *prev;
    long data;                  //the data stored in this Node
    unsigned value;             //the RRIP value stored by a 2-bit register per Node (details below)
};
/* An RRPV of 0 implies that a cache block is predicted to be re-referenced
   in the near-immediate future while RRPV of 3 implies that a cache 
   block is predicted to be re-referenced in the distant future. 
   An RRPV of 2 represents a long re-reference interval. 
   Quantitavely, RRIP predicts that blocks with small RRPVs are re-referenced sooner 
   than blocks with large RRPVs */

/* A List (a collection of Nodes in ascending order according to their RRIP) */
struct list_t {
    struct node_t *head, *fst_dist, *tail;
    /* head is a pointer to the head of the List
       fst_dist is a pointer to the first Node in the List with distant RRIP
       tail is a pointer to the tail of the List */
    long size;                  //total number of Nodes in List
    long full_nodes;            //number of filled Nodes in List
};

struct list_t *create_list(const long cache_size)
{
    struct list_t *list = (struct list_t*)calloc(1, sizeof(struct list_t));
    if (list == NULL) {
        cerr << "Memory exhausted\n";
        abort();
    }
    list->head = list->fst_dist = list->tail = NULL;
    list->size = cache_size;
    list->full_nodes = 0;

    return list;
}

/* A utility function to create a new List Node.
   The list Node will store the given 'data' */
static struct node_t *newNode(const long data)
{
    struct node_t *res = (struct node_t*)calloc(1, sizeof(struct node_t));
    if (res == NULL) {
        cerr << "Memory exhausted\n";
        abort();
    }
    res->next = res->prev = NULL;
    res->data = data;
    res->value = RRIPval_LONG;

    return res;
}

/* A utility function to check if List is empty */
static int isListEmpty(const struct list_t * list)
{
    assert((list != NULL) && "Code doesn't work correctly");
    return list->tail == NULL;
}

/* A utility function to check if there is slot available in memory */
static int isListFull(const struct list_t * list)
{
    assert((list != NULL) && "Code doesn't work correctly");
    return list->size == list->full_nodes;
}

void dequeue(struct node_t * node, struct list_t * list, HashTable * table)
{
    assert((list != NULL) && (table != NULL) && (node != NULL)
           && "Code doesn't work correctly");
    list->fst_dist = node->next;

    if (node != list->head)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node != list->tail)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;


    list->full_nodes--;
    ht_delete(table, node->data);
    free(node);
}

void enqueue(struct list_t * list, HashTable * table, const long data)
{
    assert((list != NULL) && (table != NULL)
           && "Code doesn't work correctly");
    struct node_t *curnode = newNode(data);

    if (isListFull(list)) {
        if (list->fst_dist == NULL) {
            int i = RRIPval_DIST - list->tail->value;
            struct node_t *tmp = list->head;

            for (; tmp != NULL;) {
                tmp->value += i;
                if ((tmp->value == 3) && (list->fst_dist == NULL)) {
                    list->fst_dist = tmp;
                }
                tmp = tmp->next;
            }
        }

        struct node_t *hlp = list->fst_dist->prev;
        dequeue(list->fst_dist, list, table);

        if (hlp != NULL) {
            if (hlp != list->tail)
                hlp->next->prev = curnode;
            else
                list->tail = curnode;
            hlp->next = curnode;
        } else {
            list->head->prev = curnode;
            list->head = curnode;
        }

        curnode->next = list->fst_dist;
        curnode->prev = hlp;

        list->full_nodes++;
        ht_insert(table, data, curnode);
    } else {
        if (isListEmpty(list)) {
            list->head = curnode;
        } else {
            list->tail->next = curnode;
            curnode->prev = list->tail;
        }
        list->tail = curnode;
        list->full_nodes++;
        ht_insert(table, data, curnode);
    }

}

void cache_hit(struct node_t * node, struct list_t * list)
{
    assert((list != NULL) && (node != NULL)
           && "Code doesn't work correctly");
    if (list->head == node) {
        node->value = RRIPval_NEAR;
        return;
    }

    if (list->fst_dist == node)
        list->fst_dist = node->next;

    if (list->tail == node) {
        node->prev->next = node->next; 
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next; 
    }

    node->prev = NULL;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    node->value = RRIPval_NEAR;
    return;
}

int replacement_RRIP(long page, struct list_t * list, HashTable * table)
{
    assert((list != NULL) && (table != NULL)
           && "Code doesn't work correctly");

    struct node_t *node = ht_search(table, page);

    if (node == NULL) {
        enqueue(list, table, page);
        return 0;
    } else {
        cache_hit(node, list);
        return 1;
    }
}

static void dequeue_cop(struct node_t * node, struct list_t * list, struct node_t ** hash)
{
    assert((list != NULL) && (hash != NULL) && (node != NULL)
           && "Code doesn't work correctly");

    list->fst_dist = node->next;

    if (node != list->head)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node != list->tail)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;


    list->full_nodes--;
    hash[node->data] = NULL;
    free(node);
}

static void enqueue_cop(struct list_t * list, struct node_t ** hash, const long data)
{
    assert((list != NULL) && (hash != NULL)
           && "Code doesn't work correctly");
    struct node_t *curnode = newNode(data);

    if (isListFull(list)) {
        if (list->fst_dist == NULL) {
            int i = 3 - list->tail->value;
            struct node_t *tmp = list->head;

            for (; tmp != NULL;) {
                tmp->value += i;
                if ((tmp->value == 3) && (list->fst_dist == NULL)) {
                    list->fst_dist = tmp;
                }
                tmp = tmp->next;
            }
        }

        struct node_t *hlp = list->fst_dist->prev;
        dequeue_cop(list->fst_dist, list, hash);

        if (hlp != NULL) {
            if (hlp != list->tail)
                hlp->next->prev = curnode;
            else
                list->tail = curnode;
            hlp->next = curnode;
        } else {
            list->head->prev = curnode;
            list->head = curnode;
        }

        curnode->next = list->fst_dist;
        curnode->prev = hlp;

        list->full_nodes++;
        hash[data] = curnode;
    } else {
        if (isListEmpty(list)) {
            list->head = curnode;
        } else {
            list->tail->next = curnode;
            curnode->prev = list->tail;
        }
        list->tail = curnode;
        list->full_nodes++;
        hash[data] = curnode;
    }

}

int replacement_RRIP_cop(long page, struct list_t * list, struct node_t ** hash)
{
    assert((list != NULL) && (hash != NULL)
           && "Code doesn't work correctly");

    struct node_t *node = hash[page];

    if (node != NULL) {
        cache_hit(node, list);
        return 1;
    } else {
        enqueue_cop(list, hash, page);
        return 0;
    }
}

void print_list(const struct list_t * list)
{
    assert((list != NULL) && "Code doesn't work correctly");

    struct node_t *head = list->head;

    while (head != NULL) {
        printf("%ld(%d) ", head->data, head->value);
        head = head->next;
    }

    printf("\n");
    return;
}

void delete_list(struct list_t * list)
{
    assert((list != NULL) && "Code doesn't work correctly");
    struct node_t *next;
    struct node_t *top = list->head;

    while (top != NULL) {
        next = top->next;
        free(top);
        top = next;
    }

    free(list);
}

void delete_hashRRIP(struct node_t ** hash_RRIP)
{
    assert((hash_RRIP != NULL) && "Code doesn't work correctly");
    free(hash_RRIP);
}

void print_results(const long count_RRIP, const long count_check, const long count_LRU) 
{
    cout << "Number of cache hits:\nfor RRIP " << count_RRIP << " (" << count_check 
         << ")\nfor LRU " << count_LRU << "\n" << endl;

    if ((count_LRU > count_RRIP) && (count_LRU != 0)) {
        cout << "Suprisingly LRU has performed better...\n" << count_LRU - count_RRIP 
             << " more cache hits\n" << endl;
        
    }

    if ((count_RRIP > count_LRU) && (count_RRIP != 0)) {
        cout << "RRIP has performed better!!\n" << count_RRIP - count_LRU 
             << " more cache hits\n" << endl;
    }

    if ((count_RRIP == count_LRU) && (count_RRIP != 0)) {
        cout << "Got the same results\n" << endl; 
    }


    if ((count_LRU == 0) && (count_RRIP == 0)) {
        cout << "OMG, no cache hits at all...\n" << endl; 
    }
}

/*void update_hash(long *phashsize, const long page, struct node_t ** hash_RRIP,
                 struct QNode ** hash_LRU)
{
    assert((hash_RRIP != NULL) && (hash_LRU != NULL) && (phashsize != NULL)
           && "Code doesn't work correctly");

    struct node_t **tmp1 =
        (struct node_t **) realloc(hash_RRIP, (page + 1) * sizeof(struct node_t *));
    for (long i = *phashsize; i <= page; i++)
        hash_RRIP[i] = NULL;

    struct QNode **tmp2 =
        (struct QNode **) realloc(hash_LRU, (page + 1) * sizeof(struct QNode *));
    for (long i = *phashsize; i <= page; i++)
        hash_LRU[i] = NULL;

    if ((tmp1 == NULL) || (tmp2 == NULL)) {
        fprintf(stderr, "Memory exhausted(during realloc)\n");
        abort();
    }

    hash_RRIP = tmp1;
    hash_LRU = tmp2;

    *phashsize = page + 1;
}*/