#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "product.h"
#include <stdbool.h>

#define TABLE_SIZE 100

typedef struct Node {
    Product product;
    struct Node *next;
} Node;

typedef struct {
    Node *table[TABLE_SIZE];
} HashTable;

void init_table(HashTable *ht);
void insert_product(HashTable *ht, Product p);
Product* search_product(HashTable *ht, const char *name);
unsigned int hash_func(const char *key);

#endif
