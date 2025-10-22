#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdbool.h>

#define BLOOM_SIZE 1000
#define NUM_HASHES 3

typedef struct {
    unsigned char bit_array[BLOOM_SIZE];
} BloomFilter;

void init_bloom(BloomFilter *bf);
void insert_bloom(BloomFilter *bf, const char *key);
bool search_bloom(BloomFilter *bf, const char *key);

#endif
