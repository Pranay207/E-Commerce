#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTS 20
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    char category[30];
    char price[20];
    char description[100];
    bool used;
} Product;

// Simple hash function
int hash(char *str, int size) {
    unsigned int hash = 0;
    while (*str)
        hash = (hash * 31) + *str++;
    return hash % size;
}

// Add product to hash table (with linear probing)
void addProduct(Product table[], Product p, int size) {
    int idx = hash(p.name, size);
    while (table[idx].used) {
        idx = (idx + 1) % size;
    }
    table[idx] = p;
    table[idx].used = true;
}

// Search product in hash table (with linear probing)
Product* searchProduct(Product table[], char *name, int size) {
    int idx = hash(name, size);
    int start = idx;
    do {
        if (table[idx].used && strcmp(table[idx].name, name) == 0)
            return &table[idx];
        idx = (idx + 1) % size;
    } while (idx != start);
    return NULL;
}

// Bloom Filter
bool bloom[MAX_PRODUCTS];

void addBloom(char *name) {
    int h1 = strlen(name) % MAX_PRODUCTS;
    int h2 = (name[0] + name[strlen(name)-1]) % MAX_PRODUCTS;
    bloom[h1] = true;
    bloom[h2] = true;
}

bool mayExist(char *name) {
    int h1 = strlen(name) % MAX_PRODUCTS;
    int h2 = (name[0] + name[strlen(name)-1]) % MAX_PRODUCTS;
    return bloom[h1] && bloom[h2];
}

int main() {
    Product catalog[MAX_PRODUCTS] = {0};
    memset(bloom, 0, sizeof(bloom));

    Product products[10] = {
        {"Laptop", "Electronics", "$1000", "High-performance laptop", false},
        {"Phone", "Electronics", "$500", "Smartphone with camera", false},
        {"Headphones", "Electronics", "$50", "Noise-cancelling headphones", false},
        {"Watch", "Accessories", "$150", "Smart watch", false},
        {"Camera", "Electronics", "$700", "DSLR camera", false},
        {"Shoes", "Fashion", "$80", "Running shoes", false},
        {"Bag", "Fashion", "$60", "Leather bag", false},
        {"Tablet", "Electronics", "$300", "10-inch tablet", false},
        {"Keyboard", "Electronics", "$30", "Mechanical keyboard", false},
        {"Mouse", "Electronics", "$25", "Wireless mouse", false}
    };

    // Add to hash table + bloom filter
    for (int i = 0; i < 10; i++) {
        addProduct(catalog, products[i], MAX_PRODUCTS);
        addBloom(products[i].name);
    }

    char query[MAX_NAME];
    printf("Enter product name to search: ");
    fgets(query, MAX_NAME, stdin);
    query[strcspn(query, "\n")] = 0;

    if (mayExist(query)) {
        Product *p = searchProduct(catalog, query, MAX_PRODUCTS);
        if (p)
            printf("\n✅ Product Found:\nName: %s\nCategory: %s\nPrice: %s\nDescription: %s\n",
                   p->name, p->category, p->price, p->description);
        else
            printf("\n⚠️ Product not found (false positive from Bloom Filter)\n");
    } else {
        printf("\n❌ Product not found\n");
    }

    return 0;
}
