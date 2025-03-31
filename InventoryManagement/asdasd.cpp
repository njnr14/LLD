#include<bits/stdc++.h>
using namespace std;


class Product{
    private:
    static int prodUid;
    int prodId;
    int quantity;
    string prodName;
    string Type;

    public:

    Product(const string name ,int num,  const string type):prodId(prodUid++) , prodName(name), quantity(num) , Type(type){
        cout<<"Your new Product is added in Inventory successfully : \n";
        cout<<"Product Name : "<<prodName<<endl;
        cout<<"Product ID : "<<prodId<<endl;
        cout<<"Product quantity : "<<quantity<<endl;
        cout<<"Product Type : "<<Type<<endl;
    }
    void displayProductInfo(){
        cout<<"Product Name : "<<prodName<<endl;
        cout<<"Product ID : "<<prodId<<endl;
        cout<<"Product quantity : "<<quantity<<endl;
        cout<<"Product Type : "<<Type<<endl;
    }
    int getProductId(){
        return prodId;
    }
    int getProductQuantity(){
        return quantity;
    }
    string getProductType(){
        return Type;
    }
    string getProductName(){
        return Type;
    }
    bool updateQuantity(int n , bool add){
        if(add){
            quantity += n;
            return true;
        }
                
        if(quantity < n){
            cout<<"quantity is less than required amount \n";
            return false;
        }

        quantity -= n;
        return true;
    }
};



class Category {
    private:
    string categoryName;
    set<Product> categoryProducts;

    public:
    Category(string name){
        categoryName = name;
    }

    void addProduct(Product &prod){
        categoryProducts.insert(prod);
    }
    void displayAllProduct(){
        for(auto it : categoryProducts){
            it.displayProductInfo();
        }
    }

    bool updateProduct(Product &prod , int amount , bool isAdded){
        if(prod.updateQuantity(amount , isAdded)){
            cout<<"quantity updated successfully \n";
            prod.displayProductInfo();
            return true;
        }
        
        cout<<"Please enter valid amount \n";
        return false;
        
    }

    bool deleteProduct(Product &prod){
        if(categoryProducts.find(prod)!=categoryProducts.end()){
            cout<<"product do not exist"<<endl;
            return false;
        }

        
        categoryProducts.erase(prod);
        return true;
        
        
    }
    bool findProduct(Product &prod){
        return categoryProducts.find(prod)!=categoryProducts.end();
    }


};

class InvetoryManagement{
    private:
    unordered_map<string , Category> categoryMap ; // cateforyType-> Category object;

    public:
    InvetoryManagement(){};

    bool addCategory(string categoryName){
        if(categoryMap.find(categoryName)!=categoryMap.end()){
            cout<<"category already exist\n";
            return false;
        }

        Category temp(categoryName);
        categoryMap[categoryName] = temp;
        cout<<"category created\n";
        return true;
    }
    bool doCategoryexists(string name){
        return categoryMap.find(name) != categoryMap.end();
        
    }
    bool addProduct(Product &prod){
        if(!doCategoryexists(prod.getProductName())){
            Category c(prod.getProductType());
            c.addProduct(prod);
            return true;
        }

        Category c = categoryMap[prod.getProductType()];
        if(c.findProduct(prod)){
            cout<<"cant add already existing product \n";
            return false;
        }

        c.addProduct(prod);
    }
    bool updateProduct(Product &prod , int amount , bool isadded){
        if(!doCategoryexists(prod.getProductType())){
            cout<<"No product exist \n";
            return false;
        }
        Category c = categoryMap[prod.getProductName()];

        return c.updateProduct(prod , amount , isadded);
    }
    bool deleteProduct(Product &prod){
        if(!doCategoryexists(prod.getProductType())){
            cout<<"No product exist \n";
            return false;
        }
        Category c = categoryMap[prod.getProductName()];

        return c.deleteProduct(prod);
    }

    void displayCategoriesWithProduct(){
        for(auto it : categoryMap){
            cout<<"Category : "<<it.first<<endl;
            it.second.displayAllProduct();
        }
    }

};

int main(){
    return 0;
}