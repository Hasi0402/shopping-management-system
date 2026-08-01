#include <queue>

using namespace std;


struct Category {
    int id;
    string name;
    int priority;  
    vector<Product*> products;

    Category(int i, string n) : id(i), name(n), priority(0) {}
};

struct CompareCategory {
    bool operator()(Category* a, Category* b) {
        if (a->priority == b->priority)
            return a->id > b->id;
        return a->priority < b->priority; 
    }
};