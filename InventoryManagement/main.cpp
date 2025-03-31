#include <bits/stdc++.h>
using namespace std;

class Product {
private:
    static int prodUid;
    int prodId;
    int quantity;
    string prodName;
    string Type;

public:
    Product(const string& name, int num, const string& type)
        : prodId(prodUid++), prodName(name), quantity(num), Type(type) {
        cout << "Your new Product is added in Inventory successfully:\n";
        cout << "Product Name: " << prodName << endl;
        cout << "Product ID: " << prodId << endl;
        cout << "Product Quantity: " << quantity << endl;
        cout << "Product Type: " << Type << endl;
    }

    void displayProductInfo() const {
        cout << "Product Name: " << prodName << endl;
        cout << "Product ID: " << prodId << endl;
        cout << "Product Quantity: " << quantity << endl;
        cout << "Product Type: " << Type << endl;
    }

    int getProductId() const {
        return prodId;
    }

    int getProductQuantity() const {
        return quantity;
    }

    string getProductType() const {
        return Type;
    }

    string getProductName() const {
        return prodName;
    }

    bool updateQuantity(int n, bool add) {
        if (add) {
            quantity += n;
            return true;
        }
        if (quantity < n) {
            cout << "Quantity is less than required amount.\n";
            return false;
        }
        quantity -= n;
        return true;
    }

    // Define the < operator for set storage
    bool operator<(const Product& other) const {
        return prodId < other.prodId;
    }
};

// Initialize the static variable
int Product::prodUid = 1;

class Category {
private:
    string categoryName;
    set<Product> categoryProducts;

public:
    // ✅ Default constructor
    Category() : categoryName("") {}

    // ✅ Parameterized constructor
    Category(const string& name) : categoryName(name) {}

    void addProduct(const Product& prod) {
        categoryProducts.insert(prod);
    }

    void displayAllProduct() const {
        for (const auto& it : categoryProducts) {
            it.displayProductInfo();
        }
    }

    bool updateProduct(Product& prod, int amount, bool isAdded) {
        if (prod.updateQuantity(amount, isAdded)) {
            cout << "Quantity updated successfully.\n";
            prod.displayProductInfo();
            return true;
        }
        cout << "Please enter a valid amount.\n";
        return false;
    }

    bool deleteProduct(const Product& prod) {
        if (categoryProducts.find(prod) == categoryProducts.end()) {
            cout << "Product does not exist.\n";
            return false;
        }
        categoryProducts.erase(prod);
        return true;
    }

    bool findProduct(const Product& prod) const {
        return categoryProducts.find(prod) != categoryProducts.end();
    }
};


class InventoryManagement {
private:
    unordered_map<string, Category> categoryMap; // categoryType -> Category object

public:
    InventoryManagement() {}

    bool addCategory(const string& categoryName) {
        if (categoryMap.find(categoryName) != categoryMap.end()) {
            cout << "Category already exists.\n";
            return false;
        }

        categoryMap.emplace(categoryName, Category(categoryName));
        cout <<categoryName<< " Category created.\n";
        return true;
    }

    bool doesCategoryExist(const string& name) const {
        return categoryMap.find(name) != categoryMap.end();
    }

    bool addProduct(Product& prod) {
        if (!doesCategoryExist(prod.getProductType())) {
            this->addCategory(prod.getProductType());
        }

        // Use reference to modify existing category
        Category& c = categoryMap[prod.getProductType()];
        
        if (c.findProduct(prod)) {
            cout << "Cannot add an already existing product.\n";
            return false;
        }

        c.addProduct(prod);
        return true;
    }

    bool updateProduct(Product& prod, int amount, bool isAdded) {
        if (!doesCategoryExist(prod.getProductType())) {
            cout << "No product exists.\n";
            return false;
        }
        Category& c = categoryMap[prod.getProductType()];
        return c.updateProduct(prod, amount, isAdded);
    }

    bool deleteProduct(Product& prod) {
        if (!doesCategoryExist(prod.getProductType())) {
            cout << "No product exists.\n";
            return false;
        }
        Category& c = categoryMap[prod.getProductType()];
        return c.deleteProduct(prod);
    }

    void displayCategoriesWithProduct() const {
        for (const auto& it : categoryMap) {
            cout << "Category: " << it.first << endl;
            it.second.displayAllProduct();
        }
    }
};

// Main function
int main() {
    InventoryManagement inventory;

    // Creating categories
    inventory.addCategory("Electronics");
    inventory.addCategory("Grocery");

    // Adding products
    Product laptop("Laptop", 10, "Electronics");
    Product phone("Phone", 15, "Electronics");
    Product rice("Rice", 50, "Grocery");
    Product football("Football", 50, "sports");

    inventory.addProduct(laptop);
    cout<<endl;
    inventory.addProduct(phone);
    cout<<endl;
    inventory.addProduct(rice);
    cout<<endl;
    inventory.addProduct(football);
    
    // Display all products
    cout<<endl;
    inventory.displayCategoriesWithProduct();
    cout<<endl;
    
    // Updating quantity
    inventory.updateProduct(phone, 5, true);
    cout<<endl;
    inventory.updateProduct(rice, 60, false);
    cout<<endl;
    cout<<endl;
    
    // Deleting a product
    inventory.deleteProduct(phone);
    cout<<endl;
    
    // Display updated inventory
    inventory.displayCategoriesWithProduct();
    cout<<endl;

    return 0;
}
