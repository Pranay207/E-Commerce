#include "bloom_filter.h"
#include <string.h>

static unsigned int hash1(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % BLOOM_SIZE;
}

static unsigned int hash2(const char *str) {
    unsigned int hash = 0;
    while (*str)
        hash = *str++ + (hash << 6) + (hash << 16) - hash;
    return hash % BLOOM_SIZE;
}

static unsigned int hash3(const char *str) {
    unsigned int hash = 1315423911;
    while (*str)
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    return hash % BLOOM_SIZE;
}

void init_bloom(BloomFilter *bf) {
    memset(bf->bit_array, 0, BLOOM_SIZE);
}

void insert_bloom(BloomFilter *bf, const char *key) {
    bf->bit_array[hash1(key)] = 1;
    bf->bit_array[hash2(key)] = 1;
    bf->bit_array[hash3(key)] = 1;
}

bool search_bloom(BloomFilter *bf, const char *key) {
    return (bf->bit_array[hash1(key)] &&
            bf->bit_array[hash2(key)] &&
            bf->bit_array[hash3(key)]);
}
