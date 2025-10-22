#include <stdio.h>
#include <string.h>
#include "bloom_filter.h"
#include "hash_table.h"

int main() {
    BloomFilter bf;
    HashTable ht;
    init_bloom(&bf);
    init_table(&ht);

    Product p1 = {101, "Laptop", 55000.0, "Electronics"};
    Product p2 = {102, "Mobile", 15000.0, "Electronics"};
    Product p3 = {103, "Shoes", 2500.0, "Fashion"};

    insert_bloom(&bf, p1.name);
    insert_bloom(&bf, p2.name);
    insert_bloom(&bf, p3.name);

    insert_product(&ht, p1);
    insert_product(&ht, p2);
    insert_product(&ht, p3);

    char query[100];
    printf("Enter product name to search: ");
    scanf("%s", query);

    if (search_bloom(&bf, query)) {
        Product *result = search_product(&ht, query);
        if (result)
            printf("\n✅ Found: %s | ₹%.2f | %s\n", result->name, result->price, result->category);
        else
            printf("\n⚠️ False Positive: Product not found.\n");
    } else {
        printf("\n❌ Product definitely not in catalog.\n");
    }

    return 0;
}
