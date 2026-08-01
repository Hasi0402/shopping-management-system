#include <stack>
#include <fstream>
#include <iomanip>
using namespace std;

class CartItem {
public:
    Product* prod;
    int qty;
    CartItem(Product* p, int q) : prod(p), qty(q) {}
};

class Cart {
private:
    stack<CartItem> items;
public:
    void addToCart(Product* p, int q) {
        items.push(CartItem(p, q));
        cout << "✅ Added " << p->getName() << " x" << q << " to cart\n";
    }

    void viewCart() {
        if (items.empty()) { cout << "🛒 Cart is empty\n"; return; }
        stack<CartItem> temp = items;
        double total = 0;
        cout << "\n--- 🛍 Your Cart ---\n";
        while (!temp.empty()) {
            auto &item = temp.top();
            cout << "  " << item.prod->getName() << " x" << item.qty
                 << " = ₹" << fixed << setprecision(2)
                 << item.prod->getPrice() * item.qty << "\n";
            total += item.prod->getPrice() * item.qty;
            temp.pop();
        }
        cout << "Total = ₹" << total << "\n";
    }

    void placeOrder() {
        if (items.empty()) { 
            cout << "🛒 Cart is empty\n"; 
            return; 
        }

        ofstream file("orders.txt", ios::app); 
        if (!file) {
            cout << "❌ Error opening orders.txt\n";
            return;
        }

        file << "\n===== NEW ORDER =====\n";

        stack<CartItem> temp = items;
        double total = 0;

        while (!temp.empty()) {
            auto &item = temp.top();
            double lineTotal = item.prod->getPrice() * item.qty;

            file << item.prod->getName()
                 << " x" << item.qty
                 << " = ₹" << fixed << setprecision(2) << lineTotal << "\n";

            total += lineTotal;
            temp.pop();
        }

        file << "Total = ₹" << fixed << setprecision(2) << total << "\n";
        file << "Status: Order placed successfully ✅\n";
        file << "=======================\n";

        file.close();

        cout << "✅ Order placed successfully! (Saved to orders.txt)\n";

        while (!items.empty()) items.pop();
    }
};