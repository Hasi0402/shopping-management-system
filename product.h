using namespace std;

class Product {
private:
    string name;
    double price;
    vector<double> priceHistory; 

public:
    Product(string n, double p) : name(n), price(p){}

    string getName() const { return name; }
    double getPrice() const { return price; }

    void updatePrice(double newPrice) {
        if (priceHistory.empty()) {
            priceHistory.push_back(price);
        }
        priceHistory.push_back(newPrice);
        price = newPrice;
        cout << "✅ Price updated successfully!\n";
    }

    void displayPriceHistory() {
        if (priceHistory.empty()) {
            cout << "ℹ No price updates for " << name << "\n";
            return;
        }

        cout << "\n💹 Price history for " << name << ":\n";
        cout << fixed << setprecision(2);

        cout << " ₹" << priceHistory[0] << " (Original)\n";

        for (size_t i = 1; i < priceHistory.size(); i++) {
            cout << "  ₹" << priceHistory[i] << "\n";
        }
    }

    void displayDetails() const {
        cout << fixed << setprecision(2);
        cout << "\n📦 Product: " << name << "\n";
        cout << "💰 Price: ₹" << price << "\n";
    }
};
