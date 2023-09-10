/* A C program which shows implementation of 
   Static Re-Reference Interval Prediction(RRIP) in High Perfomance Cache Replacement  */

#include <iostream>
#include <cstdlib>
#include <assert.h>
//#include "./lru/lru.h"

#include "func.h"

using namespace std;

int main()
{
    struct node_t **hash_RRIP;
    struct QNode **hash_LRU;
    long hashsize;
    HashTable *table;

    long cache_size, num_req, page, count_RRIP, count_LRU, count_check;
    /* 
       num_req is an overall number of requests
       page is a current request
       count_RRIP tracks a number of cache hits in RRIP replacement
       count_LRU tracks a number of cache hits in LRU replacement
       count_check tracks a number of cache hits in RRIP using simple hash(just array)
     */
    struct list_t *list;
    struct list_t *list_check;
    struct Queue *queue;

    //scanning
    while (!(cin >> cache_size) || (cache_size <= 0))
        cout << "Waiting for the cache size... It must be positive number\n" << endl;

    while (!(cin >>num_req) || (num_req <= 0))
        cout << "Waiting for the overall number of requests... It must be positive number\n" << endl;
         
    hashsize = num_req + 1;
    hash_RRIP = (struct node_t **)calloc(hashsize, sizeof(struct node_t *));
    //hash_LRU = calloc(hashsize, sizeof(struct QNode *));
    table = create_table();
    list = create_list(cache_size);
    list_check = create_list(cache_size);
    //queue = createQueue(cache_size);

    if ((hash_RRIP == NULL)  /*(hash_LRU == NULL)*/ || (table == NULL)
        || (list == NULL) || (list_check == NULL) || (queue == NULL)) {
        cerr << "Memory exhausted\n";
        abort();
    }

    count_LRU = 0;
    count_RRIP = 0;
    count_check = 0;

    //work begins...
    for (long i = 0; i < num_req; i++) {
        while ( !(cin >> page) || (page <= 0)) {
            printf
                ("Waiting for your request... It must be positive number\n");
        }

        if (hashsize - 1 < page) {
            //update_hash(&hashsize, page, hash_RRIP, hash_LRU);

            hash_RRIP =
                (struct node_t **) realloc(hash_RRIP,
                                    (page + 1) * sizeof(struct node_t *));
            for (long i = hashsize; i <= page; i++)
                hash_RRIP[i] = NULL;

            hash_LRU =
                (struct QNode **) realloc(hash_LRU, (page + 1) * sizeof(struct QNode *));
            for (long i = hashsize; i <= page; i++)
                hash_LRU[i] = NULL;

            if ((hash_RRIP == NULL) /*(hash_LRU == NULL)*/) {
                cerr << "Memory exhausted(during realloc)\n";
                abort();
            }

            hashsize = page + 1;
        }

        //count_LRU += lru(page, queue, hash_LRU);
        count_RRIP += replacement_RRIP(page, list, table);
        count_check += replacement_RRIP_cop(page, list_check, hash_RRIP);
    }

    assert((count_LRU >= 0) && (count_RRIP >= 0)
           && (count_check == count_RRIP)
           && "Something went wrong, code doesn't work correctly");

    print_results(count_RRIP, count_check, count_LRU);

    delete_list(list);
    delete_list(list_check);
    free_table(table);
    //delete_hashLRU(hash_LRU);
    delete_hashRRIP(hash_RRIP);
    //delete_queue(queue);

    return 0;
}