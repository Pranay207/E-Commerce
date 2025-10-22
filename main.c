#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 100
#define MAX_LEN 100

typedef struct {
    int id;
    char name[MAX_LEN];
    float price;
    char category[MAX_LEN];
} Product;

Product products[MAX_PRODUCTS];
int product_count = 0;

// Convert string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

int main() {
    FILE *fp = fopen("products.txt", "r");
    if (!fp) {
        printf("❌ Could not open products.txt\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) && product_count < MAX_PRODUCTS) {
        char *token = strtok(line, ",");
        if (!token) continue;
        products[product_count].id = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(products[product_count].name, token);
        to_lowercase(products[product_count].name);

        token = strtok(NULL, ",");
        if (!token) continue;
        products[product_count].price = atof(token);

        token = strtok(NULL, ",\n");
        if (!token) continue;
        strcpy(products[product_count].category, token);

        product_count++;
    }
    fclose(fp);

    char query[MAX_LEN];
    printf("Enter product name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0; // remove newline
    to_lowercase(query);

    // Search products
    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].name, query) == 0) {
            printf("✅ Found: %s | ₹%.2f | %s\n", 
                products[i].name, products[i].price, products[i].category);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("❌ Product definitely not in catalog.\n");

    return 0;
}
