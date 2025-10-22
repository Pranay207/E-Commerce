#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PRODUCTS 10
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    char category[30];
    char price[20];
    char description[100];
} Product;

// Hash table with linear probing
Product hashTable[MAX_PRODUCTS];
bool used[MAX_PRODUCTS] = {false};

// Convert string to lowercase
void to_lowercase(char *str){
    for(int i=0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// Simple hash function
int hash(char *str){
    int sum = 0;
    for(int i=0; str[i]; i++)
        sum += str[i];
    return sum % MAX_PRODUCTS;
}

// Add product to hash table
void addProduct(Product p){
    int idx = hash(p.name);
    while(used[idx]) idx = (idx + 1) % MAX_PRODUCTS;
    hashTable[idx] = p;
    used[idx] = true;
}

// Search product
Product* searchProduct(char *name){
    char lower[MAX_NAME];
    strcpy(lower, name);
    to_lowercase(lower);

    int idx = hash(lower);
    int start = idx;
    do {
        if(used[idx]){
            char tmp[MAX_NAME];
            strcpy(tmp, hashTable[idx].name);
            to_lowercase(tmp);
            if(strcmp(tmp, lower) == 0) return &hashTable[idx];
        }
        idx = (idx + 1) % MAX_PRODUCTS;
    } while(idx != start);

    return NULL;
}

// Bloom filter
bool bloom[MAX_PRODUCTS];
void addBloom(char *name){
    int h1 = strlen(name) % MAX_PRODUCTS;
    int h2 = (name[0] + name[strlen(name)-1]) % MAX_PRODUCTS;
    bloom[h1] = true;
    bloom[h2] = true;
}
bool mayExist(char *name){
    int h1 = strlen(name) % MAX_PRODUCTS;
    int h2 = (name[0] + name[strlen(name)-1]) % MAX_PRODUCTS;
    return bloom[h1] && bloom[h2];
}

int main(){
    memset(bloom, 0, sizeof(bloom));

    Product products[MAX_PRODUCTS] = {
        {"Laptop", "Electronics", "$1000", "High-performance laptop"},
        {"Phone", "Electronics", "$500", "Smartphone with camera"},
        {"Headphones", "Electronics", "$50", "Noise-cancelling headphones"},
        {"Watch", "Accessories", "$150", "Smart watch"},
        {"Camera", "Electronics", "$700", "DSLR camera"},
        {"Shoes", "Fashion", "$80", "Running shoes"},
        {"Bag", "Fashion", "$60", "Leather bag"},
        {"Tablet", "Electronics", "$300", "10-inch tablet"},
        {"Keyboard", "Electronics", "$30", "Mechanical keyboard"},
        {"Mouse", "Electronics", "$25", "Wireless mouse"}
    };

    for(int i=0; i<MAX_PRODUCTS; i++){
        addProduct(products[i]);
        addBloom(products[i].name);
    }

    char query[MAX_NAME];
    fgets(query, MAX_NAME, stdin);
    query[strcspn(query, "\n")] = 0;

    if(mayExist(query)){
        Product *p = searchProduct(query);
        if(p){
            printf("✅ Product Found:\n");
            printf("Name: %s\nCategory: %s\nPrice: %s\nDescription: %s\n",
                   p->name, p->category, p->price, p->description);
        } else {
            printf("⚠️ Product not found (false positive from Bloom Filter)\n");
        }
    } else {
        printf("❌ Product definitely not in catalog.\n");
    }

    return 0;
}
