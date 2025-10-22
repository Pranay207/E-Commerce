# 🛍️ E-Commerce Product Catalog Search Engine (C Project)

## 📘 Overview
This project implements a **product search engine** using **Bloom Filters** and **Hash Tables** in C to optimize search performance.

### ⚙️ Features
- Fast probabilistic search using Bloom Filter
- Exact lookup verification using Hash Table
- Reduces false lookups & improves performance

### 🧠 Data Structures
- **Bloom Filter** → Fast membership check (probabilistic)
- **Hash Table** → Exact data retrieval (chaining)

### 🏗️ Project Structure
```
ecommerce-search/
├── include/
│   ├── bloom_filter.h
│   ├── hash_table.h
│   └── product.h
├── src/
│   ├── bloom_filter.c
│   ├── hash_table.c
│   ├── main.c
├── data/
│   └── products.txt
├── Makefile
└── README.md
```

### 🚀 Run Instructions
```bash
make
make run
```

### 🧩 Example Output
```
Enter product name to search: Mobile
✅ Found: Mobile | ₹15000.00 | Electronics
```

### 🧮 Concepts Used
- Hashing & Chaining
- Bloom Filter Bit Array
- String Hashing
- Memory-efficient probabilistic search
