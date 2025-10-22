#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloom_filter.h"
#include "hash_table.h"

#define MAX_LINE 256

int main() {
    BloomFilter bf;
    HashTable ht;
    init_bloom(&bf);
    init_table(&ht);

    FILE *fp = fopen("data/products.txt", "r");
    if (!fp) {
        printf("❌ Could not open products.txt\n");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        Product p;
        char *token = strtok(line, ",");
        if (!token) continue;
        p.id = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(p.name, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        p.price = atof(token);

        token = strtok(NULL, ",\n");
        if (!token) continue;
        strcpy(p.category, token);

        // Insert into Bloom filter & hash table
        insert_bloom(&bf, p.name);
        insert_product(&ht, p);
    }
    fclose(fp);

    char query[100];
    printf("Enter product name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0; // Remove newline

    // Case-insensitive search
    char query_lower[100];
    for(int i=0; query[i]; i++) query_lower[i] = tolower(query[i]);
    query_lower[strlen(query)] = 0;

    int found_in_bloom = 0;
    for(int i=0; i<strlen(query); i++) query[i] = tolower(query[i]); // lowercase for bloom
    if (search_bloom(&bf, query)) found_in_bloom = 1;

    if (found_in_bloom) {
        Product *result = search_product(&ht, query);
        if (result)
            printf("\\n✅ Found: %s | ₹%.2f | %s\\n", result->name, result->price, result->category);
        else
            printf("\\n⚠️ False Positive: Product not found.\\n");
    } else {
        printf("\\n❌ Product definitely not in catalog.\\n");
    }

    return 0;
}

