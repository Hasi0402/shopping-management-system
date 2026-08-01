
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>


#include "product.h"
#include "category.h"
#include "cart.h"

using namespace std;

class ShoppingApp {
private:
    unordered_map<int, Category*> categories;
    Cart cart;
    const string adminUser = "admin";
    const string adminPass = "1234";

    priority_queue<Category*, vector<Category*>, CompareCategory> categoryHeap;

public:

    void addCategory(int id, const string &name) {
        categories[id] = new Category(id, name);
        categoryHeap.push(categories[id]);
    }

    void rebuildHeap() {
        priority_queue<Category*, vector<Category*>, CompareCategory> newHeap;
        for (auto &p : categories)
            newHeap.push(p.second);
        categoryHeap = move(newHeap);
    }

    void addProductToCategory(int cid, Product* p) {
        if (categories.find(cid) != categories.end())
            categories[cid]->products.push_back(p);
    }
    
    void viewOrderHistory() {
    ifstream file("orders.txt");

    if (!file) {
        cout << "⚠ No order history found.\n";
        return;
    }

    cout << "\n===== 📜 ORDER HISTORY =====\n";

    string line;
    bool empty = true;

    while (getline(file, line)) {
        empty = false;
        cout << line << "\n";
    }

    if (empty)
        cout << "⚠ Order history is empty.\n";

    cout << "=============================\n";
}


    bool adminLogin() {
        string u, p;
        cout << "\n👮 Admin Login\nUsername: "; cin >> u;
        cout << "Password: "; cin >> p;
        if (u == adminUser && p == adminPass) {
            cout << "✅ Login successful!\n";
            //adminMenu();
            return true;
        } else { 
            cout << "❌ Invalid credentials!\n"; 
            return false; 
        }
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\n======= ADMIN MENU =======\n";
            cout << "1. View Categories\n2. Update Product Price\n3. View Orders\n0. Logout\nChoice: ";
            cin >> choice;
            switch(choice) {
                case 1: printCategories(false); break;
                case 2: updateProductPrice(); break;
                case 3: viewOrderHistory(); break;
                case 0: cout << "👋 Logged out.\n"; break;
                default: cout << "❌ Invalid choice\n";
            }
        } while(choice != 0);
    }

    void updateProductPrice(bool personalized=false) {
                printCategories(personalized);

        int cid; cout << "\nEnter Category ID: "; cin >> cid;
        if (categories.find(cid) == categories.end()) { cout << "❌ Invalid category\n"; return; }

        Category* c = categories[cid];
        if(c->products.empty()) { cout << "⚠ No products here\n"; return; }

        cout << "\nProducts:\n";
        for(size_t i=0;i<c->products.size();i++)
            cout << i+1 << ". " << c->products[i]->getName()
                 << " (₹" << c->products[i]->getPrice() << ")\n";

        int pid; cout << "Enter product number: "; cin >> pid;
        if(pid<1 || pid>(int)c->products.size()) { cout << "❌ Invalid product\n"; return; }
        double newPrice; cout << "Enter new price: ₹"; cin >> newPrice;
        c->products[pid-1]->updatePrice(newPrice);
    }

    void printCategories(bool personalized = true) {
        cout << "\n📂 Categories (" << (personalized ? "Personalized" : "Default") << " View):\n";

        if (personalized) {
            priority_queue<Category*, vector<Category*>, CompareCategory> temp = categoryHeap;
            vector<Category*> sortedCats;
            while (!temp.empty()) {
                sortedCats.push_back(temp.top());
                temp.pop();
            }

            for (auto c : sortedCats)
                cout << c->id << ". " << c->name << " (Priority: " << c->priority << ")\n";

        } else {
            vector<Category*> catList;
            for (auto &pair : categories)
                catList.push_back(pair.second);
            sort(catList.begin(), catList.end(), [](Category* a, Category* b) {
                return a->id < b->id;
            });
            for (auto c : catList)
                cout << c->id << ". " << c->name << " (Priority: " << c->priority << ")\n";
        }
    }

    void userViewCategories(bool personalized = true) {
        printCategories(personalized);

        int id; cout << "Enter Category ID (0 to cancel): "; cin >> id;
        if(id == 0) return;

        if (categories.find(id) == categories.end()) { 
            cout << "❌ Invalid\n"; 
            return; 
        }

        Category* c = categories[id];
        if (personalized) {
            c->priority++;
            rebuildHeap();
        }

        viewProducts(c);
    }

    void viewProducts(Category* c) {
        if (c->products.empty()) {
            cout << "⚠ No products available.\n";
            return;
        }

        cout << "\n🛍 Products in " << c->name << ":\n";
        for(size_t i=0;i<c->products.size();i++)
            cout << i+1 << ". " << c->products[i]->getName()
                 << " (₹" << c->products[i]->getPrice() << ")\n";

        int choice; cout << "Enter product number (0 to cancel): "; cin >> choice;
        if(choice==0) return;
        if(choice<1 || choice>(int)c->products.size()){ cout << "❌ Invalid\n"; return; }

        Product* p = c->products[choice-1]; 
        p->displayDetails();

        int showHist; cout << "Show price history? (1=Yes 0=No): "; cin >> showHist;
        if(showHist==1) p->displayPriceHistory();

        int add; cout << "Add to cart? 1=Yes 0=No: "; cin >> add;
        if(add==1){ int q; cout << "Quantity: "; cin >> q; cart.addToCart(p,q);}
    }

void userMenu() {

            int choice;
        do {
            cout << "\n======= USER MENU =======\n";
            cout << "1. View Categories (Personalized)\n2. View Categories (Default)\n3. View Cart\n4. Place Order\n0. Exit\nChoice: ";
            cin >> choice;
            switch(choice) {
                case 1: userViewCategories(true); break;
                case 2: userViewCategories(false); break;
                case 3: cart.viewCart(); break;
                case 4: cart.placeOrder(); break;
                case 0: cout << "👋 Thanks for shopping!\n"; break;
                default: cout << "❌ Invalid choice\n";
            }
        } while(choice!=0);
}
    void menu() {
        int loginChoice;
        
        do{
            cout << "\n====== LOGIN ======\n1. User Login\n2. Admin Login\n0.Exit\nChoice: "; 
        cin >> loginChoice;
        if(loginChoice==2) { if(adminLogin()) adminMenu(); //return; 
        }
        if(loginChoice == 1) userMenu();
        }while(loginChoice != 0);
        

    }
};