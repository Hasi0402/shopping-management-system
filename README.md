# Online Shopping System (Shopping Management System )

A C++ console-based Online Shopping System built to demonstrate how core **Data Structures** and **Object-Oriented Programming** concepts combine to simulate a real-world e-commerce experience.

## Overview

The system supports both **Admin** and **User** roles:

- **Admin** can log in, view all categories, update product prices, and view order history.
- **User** can browse categories (personalized or default order), view product details and price history, add items to a cart, view the cart, and place orders.

## Data Structures Used

| Data Structure | Used For | Why |
|---|---|---|
| **Unordered Map** (`unordered_map<int, Category*>`) | Mapping category IDs to Category objects | O(1) average lookup/insert/delete for fast category access |
| **Priority Queue / Max-Heap** (`priority_queue<Category*, vector<Category*>, CompareCategory>`) | Personalized category ordering | Categories viewed more often rise to the top; rebuilt whenever priority changes |
| **Vector** | Storing products per category, and each product's price history | Dynamic resizing and fast sequential access |
| **Stack** (`stack<CartItem>`) | Shopping cart | LIFO behavior for simple, fast add/checkout operations |

## Modules

- **Product** (`product.h`) – name, price, and price history; `updatePrice()`, `displayPriceHistory()`, `displayDetails()`
- **Category** (`category.h`) – id, name, priority, list of products; `CompareCategory` for heap ordering
- **Cart** (`cart.h`) – `addToCart()`, `viewCart()`, `placeOrder()` (writes order history to `orders.txt`)
- **ShoppingApp** (`app.h`) – central controller: admin login/menu, user menu, category/product browsing, price updates, order history

## Files

```
main.cpp      Entry point — seeds categories/products and launches the app
app.h         ShoppingApp class (menus, admin/user flows, category heap)
cart.h        Cart and CartItem classes (stack-based cart + order placement)
category.h    Category struct + heap comparator
product.h     Product class (price + price history)
```

## Build & Run

```bash
g++ -std=c++17 -o shopping_app main.cpp
./shopping_app
```

**Admin credentials:** `admin` / `1234`

## Sample Flow

1. Choose **User Login** → view categories (personalized ranks by how often you've viewed them).
2. Pick a category → view products → view price history → add to cart.
3. View cart → place order (saved to `orders.txt`).
4. As **Admin**, log in to update a product's price — it's recorded in that product's price history for transparency.

## Future Enhancements

- Persistent user data and login profiles
- Product search and filtering
- Product recommendation system
- Graphical user interface
