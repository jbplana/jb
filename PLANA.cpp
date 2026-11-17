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
            case 0:cout<<"Thank you for using the store system.\n";break;
            default:cout<<"Invalid menu option.\n";
        }
    } while(choice!=0);
    return 0;
}
