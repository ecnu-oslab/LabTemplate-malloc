/* random malloc and free */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"

/* IF YOU'RE TRYING TO DEBUG THE RANDOM TESTS
 *
 * you need to know that this file is compiled using your libmem.so,
 * and run with the following arguments:
 * random: <exe> 0 10 0
 * random2: <exe> 0 1000 1
 * random3: <exe> 0 100000 1
 * random4: <exe> 0 500000 1
 * random5: <exe> 0 2000000 0
 *
 */

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "random takes 3 arguments\n");
        exit(-1);
    }
    // psudeo-random seed
    unsigned int seed = atoi(argv[1]);

    // number of operations to perform
    long long n = atoll(argv[2]);

    // if true, write data into allocated memory
    bool writeData = atoi(argv[3]);

    // maximum number of concurrent allocations to track
    int max_allocs = 1000;

    // size for allocation request
    int min_alloc_size = 1;
    int max_alloc_size = 128;

    // allowed constant overhead
    int slack = 32;

    // max header size per allocation
    int header_size = 32;

    // request size up to 64+32, header up to 32 bytes
    int max_chunk_size = max_alloc_size + header_size;

    // most possible space, no more than max_allocs+1 unusable free chunks
    int region_size = max_allocs * max_chunk_size * 2 + max_chunk_size;

    void** ptr = calloc(sizeof(void*), max_allocs);
    int* size = calloc(sizeof(int), max_allocs);
    void** shadow = calloc(sizeof(void*), max_allocs);

    /*******************************************************************
    Please note that random() gives psudeo-random, not true random data.
    If the seed is set to the same value, the sequence generated by
    random() will be the same. Using psuedo-random number generators is
    a common testing technique.
    *******************************************************************/
    srandom(seed);

    assert(Mem_Init(region_size + slack) == 0);

    int slot;
    bool doAlloc;
    bool doWrite;

    long long i;

    for (i = 0; i < n; i++) {
        slot = random() % max_allocs;
        doAlloc = random() % 4;
        doWrite = writeData;

        if (!doAlloc || ptr[slot] != NULL) {
            if (ptr[slot] == NULL)
                ;  // assert(Mem_Free(ptr[slot]) == -1);
            else
                assert(Mem_Free(ptr[slot]) == 0);
            free(shadow[slot]);
            ptr[slot] = NULL;
            shadow[slot] = NULL;
        }

        if (doAlloc) {
            size[slot] = min_alloc_size +
                         (random() % (max_alloc_size - min_alloc_size + 1));
            ptr[slot] = Mem_Alloc(size[slot], M_BESTFIT);
            assert(ptr[slot] != NULL);
            if (doWrite) {
                shadow[slot] = malloc(size[slot]);
                int j;
                for (j = 0; j < size[slot]; j++) {
                    char data = random();
                    *((char*)(ptr[slot] + j)) = data;
                    *((char*)(shadow[slot] + j)) = data;
                }
            }
        }
    }

    if (writeData) {
        for (slot = 0; slot < max_allocs; slot++) {
            if (ptr[slot] != NULL) {
                assert(memcmp(ptr[slot], shadow[slot], size[slot]) == 0);
            }
        }
    }

    exit(0);
}