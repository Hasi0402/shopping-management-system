#include <iostream>
#include "app.h"

using namespace std;

int main() {
    ShoppingApp app;

    string cats[10] = {"Electronics","Clothing","Books","Cosmetics","Furniture",
                       "Toys","Sports","Groceries","Accessories","Stationery"};
    for(int i=0;i<10;i++) app.addCategory(i+1,cats[i]);

    app.addProductToCategory(1,new Product("Smartphone",66000));
    app.addProductToCategory(1,new Product("Laptop",100000));
    app.addProductToCategory(1,new Product("Headphones",12500));

    app.addProductToCategory(2,new Product("T-shirt",2100));
    app.addProductToCategory(2,new Product("Jeans",3300));
    app.addProductToCategory(2,new Product("Sneakers",6600));

    app.addProductToCategory(3,new Product("Novel",1250));
    app.addProductToCategory(3,new Product("Comics",830));
    app.addProductToCategory(3,new Product("Notebook",415));

    app.addProductToCategory(4,new Product("Lipstick",1650));
    app.addProductToCategory(4,new Product("Perfume",4150));
    app.addProductToCategory(4,new Product("Foundation",2900));

    app.addProductToCategory(5,new Product("Sofa",58000));
    app.addProductToCategory(5,new Product("Chair",10000));
    app.addProductToCategory(5,new Product("Table",21000));

    app.addProductToCategory(6,new Product("Action Figure",2900));
    app.addProductToCategory(6,new Product("Toy Car",1650));
    app.addProductToCategory(6,new Product("Board Game",4150));

    app.addProductToCategory(7,new Product("Football",2500));
    app.addProductToCategory(7,new Product("Cricket Bat",5000));
    app.addProductToCategory(7,new Product("Yoga Mat",2100));

    app.addProductToCategory(8,new Product("Milk",250));
    app.addProductToCategory(8,new Product("Bread",165));
    app.addProductToCategory(8,new Product("Eggs",415));

    app.addProductToCategory(9,new Product("Watch",12500));
    app.addProductToCategory(9,new Product("Sunglasses",8300));
    app.addProductToCategory(9,new Product("Bag",6600));

    app.addProductToCategory(10,new Product("Pen",165));
    app.addProductToCategory(10,new Product("Marker",415));
    app.addProductToCategory(10,new Product("Notebook",830));

    app.menu();
    return 0;
}

