#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
class Product {
private:
    int id;
    string name;
    int quantity;
    double price;
public:
    Product(int id, const string& name, int quantity, double price) : id(id), name(name), quantity(quantity), price(price) {}
    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void display() const {
        cout << left << setw(10) << id << setw(20) << name << setw(10) << quantity << setw(10) << price << endl;
    }
};
class Inventory {
private:
    vector<Product> products;
    Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.getId() == id) return &product;
        }
        return nullptr;
    }
public:
    void addProduct(int id, const string& name, int quantity, double price) {
        if (findProduct(id)) {
            cout << "Product with ID " << id << " already exists.\n";
        } else {
            products.emplace_back(id, name, quantity, price);
            cout << "Product added successfully!\n";
        }
    }
    void updateQuantity(int id, int newQuantity) {
        Product* product = findProduct(id);
        if (product) {
            product->setQuantity(newQuantity);
            cout << "Quantity updated successfully!\n";
        } else {
            cout << "Product with ID " << id << " not found.\n";
        }
    }
    void removeProduct(int id) {
        auto it = remove_if(products.begin(), products.end(), [id](const Product& p) { return p.getId() == id; });
        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Product removed successfully!\n";
        } else {
            cout << "Product with ID " << id << " not found.\n";
        }
    }
    void displayInventory() const {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        cout << "--------------------------------------------------------\n";
        for (const auto& product : products) {
            product.display();
        }
    }
};
int main() {
    Inventory inventory;
    int choice, id, quantity;
    double price;
    string name;
    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product Quantity\n";
        cout << "3. Remove Product\n";
        cout << "4. Display Inventory\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter Product ID: "; cin >> id;
                cout << "Enter Product Name: "; cin >> ws; getline(cin, name);
                cout << "Enter Quantity: "; cin >> quantity;
                cout << "Enter Price: "; cin >> price;
                inventory.addProduct(id, name, quantity, price);
                break;
            case 2:
                cout << "Enter Product ID: "; cin >> id;
                cout << "Enter New Quantity: "; cin >> quantity;
                inventory.updateQuantity(id, quantity);
                break;
            case 3:
                cout << "Enter Product ID: "; cin >> id;
                inventory.removeProduct(id);
                break;
            case 4:
                inventory.displayInventory();
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
