#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash_func(const char *key) {
    unsigned int hash = 0;
    while (*key)
        hash = (hash * 31) + *key++;
    return hash % TABLE_SIZE;
}

void init_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;
}

void insert_product(HashTable *ht, Product p) {
    unsigned int index = hash_func(p.name);
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->product = p;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

Product* search_product(HashTable *ht, const char *name) {
    unsigned int index = hash_func(name);
    Node *curr = ht->table[index];
    while (curr) {
        if (strcmp(curr->product.name, name) == 0)
            return &curr->product;
        curr = curr->next;
    }
    return NULL;
}
