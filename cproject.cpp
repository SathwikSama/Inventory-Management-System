#include <iostream>
#include <vector>
#include <string>
#include <limits> // Include this header for numeric_limits

// Product Class
class Product {
private:
    std::string name;
    double price;
    int quantity;

public:
    // Constructor
    Product(std::string name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    // Getters and setters
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int quantity) { this->quantity = quantity; }

    // Methods to manage stock
    void addStock(int amount) { quantity += amount; }
    void removeStock(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
        } else {
            std::cout << "Not enough stock available!" << std::endl;
        }
    }

    // Method to calculate total value of the product
    double getTotalValue() const { return price * quantity; }

    // Virtual method for polymorphism
    virtual void displayProductDetails() const {
        std::cout << "Product: " << name << ", Price: " << price
                  << ", Quantity: " << quantity
                  << ", Total Value: " << getTotalValue() << std::endl;
    }
};

// Electronics Class (Inheriting from Product)
class Electronics : public Product {
private:
    int warrantyPeriod; // in months

public:
    Electronics(std::string name, double price, int quantity, int warrantyPeriod)
        : Product(name, price, quantity), warrantyPeriod(warrantyPeriod) {}

    // Overriding the display method
    void displayProductDetails() const override {
        Product::displayProductDetails();
        std::cout << "Warranty Period: " << warrantyPeriod << " months" << std::endl;
    }
};

// Inventory Class
class Inventory {
private:
    std::vector<Product*> products;

public:
    // Destructor to delete dynamically allocated memory
    ~Inventory() {
        for (Product* product : products) {
            delete product;
        }
    }

    // Methods to add, remove, and search products
    void addProduct(Product* product) {
        products.push_back(product);
    }

    Product* getProduct(int index) {
        if (index >= 0 && index < products.size()) {
            return products[index];
        }
        return nullptr; // Invalid index
    }

    // Method to get the total number of products
    int getProductCount() const {
        return products.size();
    }

    void displayInventory() const {
        std::cout << "\n--- Available Products ---\n";
        for (int i = 0; i < products.size(); i++) {
            std::cout << i + 1 << ". " << products[i]->getName() << "\n";
        }
    }

    void displayProductDetails(int productIndex) {
        Product* product = getProduct(productIndex);
        if (product) {
            product->displayProductDetails();
        } else {
            std::cout << "Invalid product selection!" << std::endl;
        }
    }

    void addStockToProduct(int productIndex, int numberOfProducts) {
        Product* product = getProduct(productIndex);
        if (product) {
            int oldQuantity = product->getQuantity(); // Store old stock quantity
            product->addStock(numberOfProducts);      // Add stock
            std::cout << "Stock added successfully! Updated Quantity of "
                      << product->getName() << ": "
                      << oldQuantity + numberOfProducts << std::endl; // Display total stock after adding
        } else {
            std::cout << "Invalid product selection!" << std::endl;
        }
    }

    void removeStockFromProduct(int productIndex, int numberOfProducts) {
        Product* product = getProduct(productIndex);
        if (product) {
            int oldQuantity = product->getQuantity(); // Store old stock quantity
            product->removeStock(numberOfProducts);  // Remove stock
            std::cout << "Stock removed successfully! Remaining Quantity of "
                      << product->getName() << ": "
                      << oldQuantity - numberOfProducts << std::endl; // Display remaining stock after removing
        } else {
            std::cout << "Invalid product selection!" << std::endl;
        }
    }
};

// Function to display the menu for operations
void displayOperationsMenu() {
    std::cout << "\n--- Operations ---\n";
    std::cout << "1. Fetch product data\n";
    std::cout << "2. Add new stock\n";
    std::cout << "3. Remove stock\n";
    std::cout << "4. Exit\n";
}

int main() {
    Inventory storeInventory;

    // Adding some initial products to the inventory
    storeInventory.addProduct(new Product("Laptop", 800.0, 10));
    storeInventory.addProduct(new Electronics("Smartphone", 600.0, 5, 24)); // 24 months warranty
    storeInventory.addProduct(new Product("Laptop Bag", 50.0, 15));
    storeInventory.addProduct(new Product("Wireless Mouse", 25.0, 20));
    storeInventory.addProduct(new Product("Mechanical Keyboard", 100.0, 8));

    int choice;
    int productChoice;
    int numberOfProducts;

    while (true) {
        // Display product list
        storeInventory.displayInventory();

        // Ask user to select a product
        std::cout << "\nEnter the product number to select: ";
        std::cin >> productChoice;
        productChoice--; // Convert to 0-based index

        // Validate the product selection
        if (productChoice < 0 || productChoice >= storeInventory.getProductCount()) {
            std::cout << "Invalid product selection! Please select a valid product.\n";
            continue;
        }

        // Show the operations menu
        displayOperationsMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear the input buffer before reading the next string
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Fetch product data
                storeInventory.displayProductDetails(productChoice);
                break;
            case 2: // Add new stock
                std::cout << "Enter the number of products to add: ";
                std::cin >> numberOfProducts;
                storeInventory.addStockToProduct(productChoice, numberOfProducts);
                break;
            case 3: // Remove stock
                std::cout << "Enter the number of products to remove: ";
                std::cin >> numberOfProducts;
                storeInventory.removeStockFromProduct(productChoice, numberOfProducts);
                break;
            case 4: // Exit
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}