#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

// PRODUCT MODEL FOR THE BRAND-AFFILIATED SPORTS STORE
struct Product {
    int id;
    string name, category, brand;
    double price;
    int stockQuantity;
};
struct Order {
    int id;
    string customer, product;
    int quantity;
    double total;
};

// SAFE INPUT FUNCTIONS
int readInt(const string& prompt) {
    string line; int value; char extra;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) exit(0);
        stringstream ss(line);
        if ((ss >> value) && !(ss >> extra)) return value;
        cout << "Invalid input. Enter a whole number.\n";
    }
}
double readDouble(const string& prompt) {
    string line; double value; char extra;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) exit(0);
        stringstream ss(line);
        if ((ss >> value) && !(ss >> extra) && isfinite(value)) return value;
        cout << "Invalid number.\n";
    }
}
string readText(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        if (!getline(cin, value)) exit(0);
        if (!value.empty()) return value;
        cout << "This field cannot be empty.\n";
    }
}

// LAB 1: THE SHRINKING ARCHIVE - shrink a heap array by one slot.
void pop_back_dynamic(int*& arr, int& size) {
    if (size <= 0 || arr == nullptr) return;
    int newSize = size - 1;
    int* smaller = (newSize > 0) ? new int[newSize] : nullptr;
    for (int i = 0; i < newSize; ++i) smaller[i] = arr[i];
    delete[] arr;
    arr = smaller;
    size = newSize;
}
void lab1() {
    cout << "\nLAB 1 - THE SHRINKING ARCHIVE\n";
    int size = 4;
    int* data = new int[size]{10, 20, 30, 40};
    cout << "Before shrinking (Size " << size << "): ";
    for (int i=0; i<size; ++i) cout << data[i] << " ";
    cout << "\n";
    pop_back_dynamic(data, size);
    cout << "After shrinking (Size " << size << "): ";
    for (int i=0; i<size; ++i) cout << data[i] << " ";
    cout << "\n";
    delete[] data;
}

// LAB 2: SINGLY LINKED LIST - getLastElement returns -1 if empty.
struct SingleNode {
    int data; SingleNode* next;
    explicit SingleNode(int v): data(v), next(nullptr) {}
};
class SinglyLinkedList {
    SingleNode* head = nullptr;
public:
    void insertAtEnd(int v) {
        SingleNode* n = new SingleNode(v);
        if (!head) { head=n; return; }
        SingleNode* cur=head;
        while (cur->next) cur=cur->next;
        cur->next=n;
    }
    int getLastElement() const {
        if (!head) return -1;
        SingleNode* cur=head;
        while (cur->next) cur=cur->next;
        return cur->data;
    }
    void display() const {
        SingleNode* cur=head;
        cout << "HEAD -> ";
        while (cur) { cout << cur->data << " -> "; cur=cur->next; }
        cout << "NULL\n";
    }
    ~SinglyLinkedList() {
        while (head) { SingleNode* n=head->next; delete head; head=n; }
    }
};
void lab2() {
    cout << "\nLAB 2 - THE LAST CAR LOCATOR\n";
    SinglyLinkedList train;
    train.insertAtEnd(10); train.insertAtEnd(20); train.insertAtEnd(30);
    train.display();
    cout << "Last element: " << train.getLastElement() << "\n";
    SinglyLinkedList empty;
    cout << "Empty list returns: " << empty.getLastElement() << "\n";
}

// LAB 3: DOUBLY LINKED LIST AND CIRCULAR LINKED LIST.
struct DoubleNode {
    int data; DoubleNode *next, *prev;
    explicit DoubleNode(int v): data(v), next(nullptr), prev(nullptr) {}
};
class DoublyLinkedList {
    DoubleNode *head=nullptr, *tail=nullptr;
public:
    void insertAtEnd(int v) {
        DoubleNode* n=new DoubleNode(v); n->prev=tail;
        if (!head) { head=tail=n; return; }
        tail->next=n; tail=n;
    }
    void printForward() const {
        DoubleNode* p=head; cout << "Forward: NULL <-> ";
        while(p) { cout << "[" << p->data << "] <-> "; p=p->next; }
        cout << "NULL\n";
    }
    void printBackward() const {
        DoubleNode* p=tail; cout << "Backward: NULL <-> ";
        while(p) { cout << "[" << p->data << "] <-> "; p=p->prev; }
        cout << "NULL\n";
    }
    ~DoublyLinkedList() {
        while(head) { DoubleNode* n=head->next; delete head; head=n; }
    }
};
struct CircularNode {
    int data; CircularNode* next;
    explicit CircularNode(int v): data(v), next(nullptr) {}
};
class CircularLinkedList {
    CircularNode *head=nullptr, *tail=nullptr;
public:
    void insertAtEnd(int v) {
        CircularNode* n=new CircularNode(v);
        if(!head) { head=tail=n; n->next=head; return; }
        tail->next=n; tail=n; tail->next=head;
    }
    void displayOneRound() const {
        if(!head) { cout << "Empty circular list\n"; return; }
        CircularNode* p=head; cout << "HEAD -> ";
        do { cout << p->data << " -> "; p=p->next; } while(p!=head);
        cout << "(back to HEAD)\n";
    }
    ~CircularLinkedList() {
        if(!head) return;
        tail->next=nullptr;
        while(head) { CircularNode* n=head->next; delete head; head=n; }
    }
};
void lab3() {
    cout << "\nLAB 3 - DOUBLY AND CIRCULAR LINKED LISTS\n";
    DoublyLinkedList d; d.insertAtEnd(10); d.insertAtEnd(20); d.insertAtEnd(30);
    d.printForward(); d.printBackward();
    CircularLinkedList c; c.insertAtEnd(1); c.insertAtEnd(2); c.insertAtEnd(3);
    cout << "Circular list: "; c.displayOneRound();
}

// LAB 4: BALANCED PARENTHESES USING STACK.
bool isBalanced(const string& expr) {
    stack<char> s;
    for(char ch: expr) {
        if(ch=='(') s.push(ch);
        else if(ch==')') {
            if(s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}
void lab4() {
    cout << "\nLAB 4 - BALANCED PARENTHESES CHECKER\n";
    for(const string& x: vector<string>{"(())", "(()", "())"})
        cout << x << " -> " << (isBalanced(x)?"Valid":"Invalid") << "\n";
}

// LAB 5 & LAB 6: BST INSERTION, TRAVERSALS, AND SEARCH.
struct BSTNode {
    int data; BSTNode *left, *right;
    explicit BSTNode(int v): data(v), left(nullptr), right(nullptr) {}
};
class BinarySearchTree {
    BSTNode* root=nullptr;
    BSTNode* insertRec(BSTNode* p,int v) {
        if(!p) return new BSTNode(v);
        if(v<p->data) p->left=insertRec(p->left,v);
        else if(v>p->data) p->right=insertRec(p->right,v);
        return p;
    }
    bool searchRec(BSTNode* p,int target) const {
        if(!p) return false;
        if(p->data==target) return true;
        if(target<p->data) return searchRec(p->left,target);
        return searchRec(p->right,target);
    }
    void in(BSTNode* p) const { if(p){in(p->left);cout<<p->data<<" ";in(p->right);} }
    void pre(BSTNode* p) const { if(p){cout<<p->data<<" ";pre(p->left);pre(p->right);} }
    void post(BSTNode* p) const { if(p){post(p->left);post(p->right);cout<<p->data<<" ";} }
    void clear(BSTNode* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }
public:
    void insert(int v) { root=insertRec(root,v); }
    bool search(int v) const { return searchRec(root,v); }
    void traversals() const {
        cout << "Inorder: "; in(root);
        cout << "\nPreorder: "; pre(root);
        cout << "\nPostorder: "; post(root); cout << "\n";
    }
    ~BinarySearchTree(){ clear(root); }
};
void lab5and6() {
    cout << "\nLAB 5 - BST / LAB 6 - SEARCH FINDER\n";
    BinarySearchTree bst;
    for(int v: vector<int>{50,30,70,20,40,60,80}) bst.insert(v);
    bst.traversals();
    cout << "Search 30: " << (bst.search(30)?"Found":"Not Found") << "\n";
    cout << "Search 90: " << (bst.search(90)?"Found":"Not Found") << "\n";
}

// LAB 7: BINARY SEARCH COMPARISON COUNTER.
int countBinarySteps(const int arr[], int size, int target) {
    int low=0, high=size-1, steps=0;
    while(low<=high) {
        int mid=low+(high-low)/2;
        ++steps;
        if(arr[mid]==target) return steps;
        if(target<arr[mid]) high=mid-1;
        else low=mid+1;
    }
    return steps;
}
void lab7() {
    cout << "\nLAB 7 - THE STEP-COUNTER SHOWDOWN\n";
    int data[]={2,5,8,12,16,23,38,56,72,91,100,105,110,120,130,140};
    cout << "Steps to find 110: " << countBinarySteps(data,16,110) << "\n";
}

// LAB 8: INSERTION SORT SCORES IN DESCENDING ORDER.
void rankLeaderboard(vector<int>& scores) {
    for(int i=1;i<(int)scores.size();++i) {
        int key=scores[i], j=i-1;
        while(j>=0 && scores[j]<key) { scores[j+1]=scores[j]; --j; }
        scores[j+1]=key;
    }
}
void lab8() {
    cout << "\nLAB 8 - LEADERBOARD RANKING ENGINE\n";
    vector<int> scores={450,1200,890,2300,150,990};
    rankLeaderboard(scores);
    for(size_t i=0;i<scores.size();++i)
        cout << "Rank #" << i+1 << ": " << scores[i] << " pts\n";
}
void runAllLabs() {
    lab1(); lab2(); lab3(); lab4(); lab5and6(); lab7(); lab8();
}

// E-COMMERCE PRODUCT DATA: 4 sports/apparel brands.
vector<Product> products={
    {101,"Air Force 1","Footwear","Nike",5500,10},
    {102,"Air Max 270","Footwear","Nike",6500,15},
    {103,"Dunk Low","Footwear","Nike",6000,8},
    {104,"Dri-FIT Shirt","Apparel","Nike",1200,20},
    {201,"Ultraboost","Footwear","Adidas",7200,9},
    {202,"Adicolor T-Shirt","Apparel","Adidas",1500,14},
    {301,"Suede Classic","Footwear","Puma",4200,6},
    {302,"Essentials Tee","Apparel","Puma",1300,11},
    {401,"Charged Assert","Footwear","Under Armour",3900,5}
};
queue<Order> checkoutQueue;
stack<string> adminHistory;
int nextOrderID=1;

void showProducts() {
    cout << "\nID   PRODUCT                 CATEGORY        BRAND           PRICE       STOCK\n";
    for(const Product& p:products)
        cout << left << setw(5)<<p.id << setw(24)<<p.name << setw(16)<<p.category
             << setw(16)<<p.brand << "PHP "<<setw(9)<<fixed<<setprecision(2)
             <<p.price<<p.stockQuantity<<"\n";
}
void filterBrand() {
    string brand=readText("Brand (Nike/Adidas/Puma/Under Armour): ");
    bool found=false;
    for(const Product& p:products) if(p.brand==brand) {
        cout<<p.id<<" | "<<p.name<<" | "<<p.brand<<" | PHP "<<p.price
            <<" | Stock "<<p.stockQuantity<<"\n"; found=true;
    }
    if(!found) cout<<"No products found. Check brand spelling and capitalization.\n";
}
void searchKeyword() {
    string key=readText("Search keyword: ");
    transform(key.begin(),key.end(),key.begin(),[](unsigned char c){return (char)tolower(c);});
    bool found=false;
    for(const Product& p:products) {
        string all=p.name+" "+p.category+" "+p.brand;
        transform(all.begin(),all.end(),all.begin(),[](unsigned char c){return (char)tolower(c);});
        if(all.find(key)!=string::npos) {
            cout<<p.id<<" | "<<p.name<<" | "<<p.brand<<" | PHP "<<p.price<<"\n"; found=true;
        }
    }
    if(!found) cout<<"No matching product.\n";
}
void filterPrice() {
    double lo=readDouble("Minimum price: "), hi=readDouble("Maximum price: ");
    if(lo<0 || hi<lo) {cout<<"Invalid price range.\n";return;}
    vector<Product> sorted=products;
    sort(sorted.begin(),sorted.end(),[](const Product&a,const Product&b){return a.price<b.price;});
    auto first=lower_bound(sorted.begin(),sorted.end(),lo,[](const Product&p,double v){return p.price<v;});
    auto last=upper_bound(sorted.begin(),sorted.end(),hi,[](double v,const Product&p){return v<p.price;});
    if(first==last) cout<<"No products in this price range.\n";
    for(auto it=first;it!=last;++it)
        cout<<it->id<<" | "<<it->name<<" | "<<it->brand<<" | PHP "<<it->price<<"\n";
}
void addProduct() {
    Product p{};
    p.id=readInt("Product ID: ");
    if(p.id<=0){cout<<"ID must be positive.\n";return;}
    for(const Product& x:products) if(x.id==p.id){cout<<"Duplicate ID.\n";return;}
    p.name=readText("Product name: ");
    p.category=readText("Category: ");
    p.brand=readText("Brand: ");
    p.price=readDouble("Price: ");
    p.stockQuantity=readInt("Stock quantity: ");
    if(p.price<0 || p.stockQuantity<0){cout<<"Price/stock cannot be negative.\n";return;}
    products.push_back(p); adminHistory.push("Added "+p.brand+" "+p.name);
    cout<<"Product added.\n";
}
void updateStock() {
    int id=readInt("Product ID: ");
    for(Product& p:products) if(p.id==id) {
        int n=readInt("New stock quantity: ");
        if(n<0){cout<<"Stock cannot be negative.\n";return;}
        p.stockQuantity=n; adminHistory.push("Updated stock for "+p.name);
        cout<<"Stock updated.\n";return;
    }
    cout<<"Product not found.\n";
}
void placeOrder() {
    string customer=readText("Customer name: ");
    int id=readInt("Product ID: ");
    for(Product& p:products) if(p.id==id) {
        int qty=readInt("Quantity: ");
        if(qty<=0 || qty>p.stockQuantity){cout<<"Invalid quantity or insufficient stock.\n";return;}
        Order o{nextOrderID++,customer,p.brand+" "+p.name,qty,p.price*qty};
        p.stockQuantity-=qty; checkoutQueue.push(o);
        cout<<"Order queued. Order #"<<o.id<<" Total PHP "<<fixed<<setprecision(2)<<o.total<<"\n";
        return;
    }
    cout<<"Product not found.\n";
}
void processOrder() {
    if(checkoutQueue.empty()){cout<<"No pending orders.\n";return;}
    Order o=checkoutQueue.front(); checkoutQueue.pop();
    cout<<"Processed FIFO order #"<<o.id<<" for "<<o.customer
        <<" | "<<o.product<<" | Qty "<<o.quantity<<" | PHP "
        <<fixed<<setprecision(2)<<o.total<<"\n";
}
void viewOrders() {
    if(checkoutQueue.empty()){cout<<"No pending orders.\n";return;}
    queue<Order> q=checkoutQueue;
    while(!q.empty()){Order o=q.front();q.pop();
        cout<<"#"<<o.id<<" | "<<o.customer<<" | "<<o.product
            <<" | Qty "<<o.quantity<<" | PHP "<<o.total<<"\n";}
}
void viewHistory() {
    if(adminHistory.empty()){cout<<"No admin activity.\n";return;}
    stack<string> s=adminHistory;
    while(!s.empty()){cout<<"- "<<s.top()<<"\n";s.pop();}
}
void sortCatalog() {
    sort(products.begin(),products.end(),[](const Product&a,const Product&b){return a.price<b.price;});
    showProducts();
}
void labsMenu() {
    int c;
    do {
        cout<<"\n===== LAB PRACTICE =====\n"
            <<"1 Lab 1 - Dynamic Array Shrinking\n"
            <<"2 Lab 2 - Singly Linked List Last Element\n"
            <<"3 Lab 3 - Doubly and Circular Linked Lists\n"
            <<"4 Lab 4 - Balanced Parentheses Stack\n"
            <<"5 Lab 5 - BST Insertion and Traversals\n"
            <<"6 Lab 6 - BST Search Finder\n"
            <<"7 Lab 7 - Binary Search Step Counter\n"
            <<"8 Lab 8 - Insertion Sort Leaderboard\n"
            <<"9 Run All Labs\n0 Back\n";
        c=readInt("Choose: ");
        switch(c){
            case 1:lab1();break; case 2:lab2();break; case 3:lab3();break;
            case 4:lab4();break; case 5:lab5and6();break; case 6:lab5and6();break;
            case 7:lab7();break; case 8:lab8();break; case 9:runAllLabs();break;
            case 0:break; default:cout<<"Invalid choice.\n";
        }
    }while(c!=0);
}

int main() {
    int choice;
    do {
        cout<<"\n====================================================\n"
            <<" BRAND-AFFILIATED SPORTS E-COMMERCE INVENTORY SYSTEM\n"
            <<"                    NIKE STORE\n"
            <<"====================================================\n"
            <<"1. View All Products\n"
            <<"2. Filter Products by Brand\n"
            <<"3. Search Products by Keyword\n"
            <<"4. Filter Products by Price Range\n"
            <<"5. Add Product (Admin)\n"
            <<"6. Update Product Stock (Admin)\n"
            <<"7. Place Customer Order\n"
            <<"8. Process Next Checkout Order (FIFO)\n"
            <<"9. View Pending Checkout Orders\n"
            <<"10. Sort Catalog by Price\n"
            <<"11. View Admin Action History (Stack)\n"
            <<"12. Demonstrate Labs 1-8\n"
            <<"0. Exit\n"
            <<"====================================================\n";
        choice=readInt("Enter your choice: ");
        switch(choice){
            case 1:showProducts();break;
            case 2:filterBrand();break;
            case 3:searchKeyword();break;
            case 4:filterPrice();break;
            case 5:addProduct();break;
            case 6:updateStock();break;
            case 7:placeOrder();break;
            case 8:processOrder();break;
            case 9:viewOrders();break;
            case 10:sortCatalog();break;
            case 11:viewHistory();break;
            case 12:labsMenu();break;
            case 0:cout<<"Thank you for using the store system.\n";break;
            default:cout<<"Invalid menu option.\n";
        }
    } while(choice!=0);
    return 0;
}
