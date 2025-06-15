//
//#include <iostream>
//#include <fstream>
//#include <ctime>
//#include "strings.h"
//#include "address.h"
//#include "date.h"
//#include "user.h"
//#include "ShoppingCart.h"
//#include "Admin.h"
//#include "Customer.h"
//#include "LoginManager.h"
//#include "Product.h"
//#include "Order.h"
//#include "PaymentMethod.h"
//#include "CreditCardPayment.h"
//#include "PayPalPayment.h"
//#include "Inventory.h"
//
//#include <SFML/Graphics.hpp>
//
//using namespace std;
//
//void displayProducts(const Inventory& inventory) {
//    cout << "\nAvailable Products:\n";
//    vectors<Product> products = inventory.listAllProducts();
//    if (products.empty()) {
//        cout << "No products available.\n";
//        return;
//    }
//    for (const auto& product : products) {
//        cout << "ID: " << product.getId().c_str() << ", Name: " << product.getName().c_str()
//            << ", Price: $" << product.getPrice() << ", Stock: " << product.stock << "\n";
//    }
//}
//
//void filterProductsByCategory(const Inventory& inventory, const strings& category) {
//    cout << "\nProducts in Category '" << category.c_str() << "':\n";
//    vectors<Product> products = inventory.listProductsByCategory(category);
//    if (products.empty()) {
//        cout << "No products in this category.\n";
//        return;
//    }
//    for (const auto& product : products) {
//        cout << "ID: " << product.getId().c_str() << ", Name: " << product.getName().c_str()
//            << ", Price: $" << product.getPrice() << ", Stock: " << product.getStock() << "\n";
//    }
//}
//
//void filterProductsByPriceRange(const Inventory& inventory, double minPrice, double maxPrice) {
//    cout << "\nProducts in Price Range ($" << minPrice << " - $" << maxPrice << "):\n";
//    vectors<Product> products = inventory.listAllProducts();
//    vector<Product> filtered;
//    for (const auto& product : products) {
//        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice) {
//            filtered.push_back(product);
//        }
//    }
//    if (filtered.empty()) {
//        cout << "No products in this price range.\n";
//        return;
//    }
//    for (const auto& product : filtered) {
//        cout << "ID: " << product.getId().c_str() << ", Name: " << product.getName().c_str()
//            << ", Price: $" << product.getPrice() << ", Stock: " << product.getStock() << "\n";
//    }
//}
//
//int main() {
//    strings username = "moeed", email = "bscs24140", password = "888";
//    strings area = "rehman garden", province = "punjab", country = "pakistan", city = "lahore";
//
//    Date date(11, 6, 2025);
//    Address addr(area, province, country, city);
//
//    LoginManager loginManager;
//    Inventory inventory;
//    Date currentDate(11, 6, 2025);
//
//   
//  
//    inventory.addProduct(Product(strings("P100"), strings("iphone15"), strings("Latest model"), 699.99, strings("smartphone"), strings("apple"), 50));
//    inventory.addProduct(Product(strings("P200"), strings("elitebook"), strings("16GB RAM"), 1299.99, strings("laptop"),  strings("hp"), 30));
//    inventory.addProduct(Product(strings("P300"), strings("airpodpro"), strings("Noise cancelling"), 199.99, strings("airpods"),  strings("audionic"), 100));
//    inventory.addProduct(Product(strings("P400"), strings("iphone16"), strings("Latest model"), 699.99, strings("smartphone"), strings("apple"), 50));
//    inventory.addProduct(Product(strings("P500"), strings("Macbook"), strings("16GB RAM"),2000.99, strings("laptop"), strings("hp"), 30));
//    inventory.addProduct(Product(strings("P600"), strings("audionic"), strings("Noise cancelling"), 599.99, strings("airpods"), strings("audionic"), 100));
//
//
//
//    loginManager.registerCustomer(username, email, password, date, addr);
//
//    int choice;
//    user* currentUser = nullptr;
//    const Product *p = nullptr;
//
//    while (true) {
//        cout << "\nOnline Store Menu:\n";
//        cout << "1. Register as Customer\n";
//        cout << "2. Register as Admin\n";
//        cout << "3. Login\n";
//        cout << "4. Exit\n";
//        cout << "5. Display Dashboard\n";
//        cout << "6. Add Item to Cart\n";
//        cout << "7. Remove Item from Cart\n";
//        cout << "8. View Cart Total\n";
//        cout << "9. Clear Cart\n";
//        cout << "10. Add Product\n";
//        cout << "11. Remove Product\n";
//        cout << "12. Logout\n";
//        cout << "13. View Available Products\n";
//        cout << "14. View Order History (Customer)\n";
//        cout << "15. Checkout (Customer)\n";
//        cout << "16. Filter Products by Category\n";
//        cout << "17. Filter Products by Price Range\n";
//        cout << "18. View Inventory Status (Admin)\n";
//        cout << "19. view cart\n";
//        cout << "Enter choice: ";
//        cin >> choice;
//        cin.ignore(); // Clear input buffer
//
//        switch (choice) {
//        case 1: { // Register Customer
//            strings username, email, password;
//            Address addr;
//            cout << "Enter username: ";
//            cin >> username;
//            cout << "Enter email: ";
//            cin >> email;
//            cout << "Enter password: ";
//            cin >> password;
//            cout << "Enter address (area city country province): ";
//            cin >> addr;
//            try {
//                loginManager.registerCustomer(username, email, password, currentDate, addr);
//                cout << "Customer registered successfully!\n";
//            }
//            catch (const exception& e) {
//                cout << "Registration failed: " << e.what() << endl;
//            }
//            break;
//        }
//        case 2: { // Register Admin
//            strings username, email, password, accessLevel;
//            Address addr;
//            cout << "Enter username: ";
//            cin >> username;
//            cout << "Enter email: ";
//            cin >> email;
//            cout << "Enter password: ";
//            cin >> password;
//            cout << "Enter address (area city country province): ";
//            cin >> addr;
//            cout << "Enter access level: ";
//            cin >> accessLevel;
//            loginManager.registerAdmin(username, email, password, date, addr, accessLevel);
//            cout << "Admin registered successfully!\n";
//            break;
//        }
//        case 3: { // Login
//            if (currentUser) {
//                cout << "Please logout first!\n";
//                break;
//            }
//            strings email, password;
//            cout << "Enter email: ";
//            cin >> email;
//            cout << "Enter password: ";
//            cin >> password;
//            currentUser = loginManager.login(email, password);
//            if (currentUser) {
//                cout << "Login successful! Welcome, " << currentUser->getName().c_str() << "!\n";
//            }
//            else {
//                cout << "Login failed! Invalid email or password.\n";
//            }
//            break;
//        }
//        case 4: // Exit
//            cout << "Exiting program...\n";
//            break;
//        case 5: { // Display Dashboard
//            if (currentUser) {
//                currentUser->displayDashboard();
//            }
//            else {
//                cout << "Please login first!\n";
//            }
//            break;
//        }
//        case 6: { // Add Item to Cart
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                strings productId;
//                int quantity;
//                cout << "Enter product ID: ";
//                cin >> productId;
//                cout << "Enter quantity: ";
//                cin >> quantity;
//                cin.ignore();
//                p = inventory.getProduct(productId);
//                if (p !=nullptr) {
//                    customer->getCart().addItem(productId, quantity);
//                    cout << "Item added to cart!\n";
//                    p->stock - quantity;
//                }
//                else {
//                    cout << "no such item available!\n";
//                    break;
//                }
//            }
//            else {
//                cout << "Only customers can add items to cart!\n";
//            }
//            break;
//        }
//        case 7: { // Remove Item from Cart ////view cart
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                strings productId;
//                int quantity;
//                cout << "Enter product ID: ";
//                cin >> productId;
//                cout << "Enter quantity: ";
//                cin >> quantity;
//                cin.ignore();
//                customer->getCart().removeItem(productId, quantity);
//                cout << "Item removed from cart!\n";
//            }
//            else {
//                cout << "Only customers can remove items from cart!\n";
//            }
//            break;
//        }
//        case 8: { // View Cart Total
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                double total = customer->getCart().getTotal(inventory);
//                cout << "Cart total: $" << total << "\n";
//            }
//            else {
//                cout << "Only customers can view cart total!\n";
//            }
//            break;
//        }
//        case 9: { // Clear Cart
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                customer->getCart().clear();
//                cout << "Cart cleared!\n";
//            }
//            else {
//                cout << "Only customers can clear cart!\n";
//            }
//            break;
//        }
//        case 10: { // Add Product
//            if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
//                strings id, name, desc, category, platform, company;
//                double price;
//                int stock;
//                cout << "Enter product ID: ";
//                cin >> id;
//                cout << "Enter name: ";
//                cin >> name;
//                cout << "Enter description: ";
//                cin >> desc;
//                cout << "Enter price: ";
//                cin >> price;
//                cin.ignore();
//                cout << "Enter category: ";
//                cin >> category;
//                cout << "Enter platform: ";
//                cin >> platform;
//                cout << "Enter company: ";
//                cin >> company;
//                cout << "Enter stock: ";
//                cin >> stock;
//                cin.ignore();
//                Product product(id, name, desc, price, category, company, stock);
//                if (admin->addProduct(inventory, product)) {
//                    cout << "Product added successfully!\n";
//                }
//                else {
//                    cout << "Failed to add product!\n";
//                }
//            }
//            else {
//                cout << "Only admins can add products!\n";
//            }
//            break;
//        }
//        case 11: { // Remove Product
//            if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
//                strings productId;
//                cout << "Enter product ID: ";
//                cin >> productId;
//                if (admin->removeProduct(inventory, productId)) {
//                    cout << "Product removed successfully!\n";
//                }
//                else {
//                    cout << "Failed to remove product!\n";
//                }
//            }
//            else {
//                cout << "Only admins can remove products!\n";
//            }
//            break;
//        }
//        case 12: { // Logout
//            if (currentUser) {
//                delete currentUser;
//                currentUser = nullptr;
//                cout << "Logged out successfully!\n";
//            }
//            else {
//                cout << "No user logged in!\n";
//            }
//            break;
//        }
//        case 13: { // View Available Products
//            displayProducts(inventory);
//            break;
//        }
//        case 14: { // View Order History (Customer)
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                cout << "\nOrder History:\n";
//                const vectors<Order>& orders = customer->getOrderHistory();
//                if (orders.empty()) {
//                    cout << "No orders placed yet.\n";
//                }
//                else {
//                    for (const auto& order : orders) {
//                        cout << "Order ID: " << order.getOrderId().c_str() << ", Total: $" << order.getOrderTotal(inventory.listAllProducts()) << "\n";
//                    }
//                }
//            }
//            else {
//                cout << "Only customers can view order history!\n";
//            }
//            break;
//        }
//        case 15: { // Checkout (Customer)
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
//                if (customer->getCart().getItems().size() == 0) { // Assuming size() for custom vector
//                    cout << "Cart is empty!\n";
//                    break;
//                }
//                int paymentChoice;
//                cout << "Select Payment Method:\n1. Credit Card\n2. PayPal\nEnter choice: ";
//                cin >> paymentChoice;
//                PaymentMethod* payment = nullptr;
//                if (paymentChoice == 1) {
//                    strings cardNumber, expiry;
//                    cout << "Enter card number: ";
//                    cin >> cardNumber;
//                    cout << "Enter expiry (MM/YY): ";
//                    cin >> expiry;
//                    payment = new CreditCardPayment(customer->getCart().getTotal(inventory), cardNumber, expiry);
//                }
//               else if (paymentChoice == 2) {
//                    strings email;
//                    cout << "Enter PayPal email: ";
//                    cin >> email;
//                    payment = new PayPalPayment (customer->getCart().getTotal(inventory), email);
//
//                }
//                else {
//                    cout << "Invalid payment method!\n";
//                    break;
//                }
//                if (payment) {
//                    
//                    vectors<CartItem> items = customer->getCart().getItems(); // Custom vector
//                    Order* order = new Order(customer, items); // Use corrected constructor
//                    order->setPaymentMethod(payment);
//                    if (order->getPaymentMethod()->processPayment()) {
//                        customer->addToOrderHistory(*order);
//                        customer->getCart().clear();
//                        cout << "Checkout successful! Order ID: " << order->getOrderId() << "\n";
//                        cout << "customer name " << customer->getName() << "\n";
//                    }
//                    else {
//                        cout << "Payment failed!\n";
//                    }
//                    delete order; // Cleaning up order 
//                }
//            }
//            else {
//                cout << "Only customers can checkout!\n";
//            }
//            break;
//        }
//        case 16: { // Filter Products by Category
//            strings category;
//            cout << "Enter category: ";
//            cin >> category;
//            filterProductsByCategory(inventory, category);
//            break;
//        }
//        case 17: { // Filter Products by Price Range
//            double minPrice, maxPrice;
//            cout << "Enter minimum price: ";
//            cin >> minPrice;
//            cout << "Enter maximum price: ";
//            cin >> maxPrice;
//            if (minPrice <= maxPrice) {
//                filterProductsByPriceRange(inventory, minPrice, maxPrice);
//            }
//            else {
//                cout << "Invalid price range!\n";
//            }
//            break;
//        }
//        case 18: { // View Inventory Status (Admin)
//            if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
//                cout << "\nInventory Status:\n";
//                vectors<Product> products = inventory.listAllProducts();
//                for (const auto& product : products) {
//                  //  strings name=
//                    cout << "ID: " << product.getId() << ", Name: " << product.getName().c_str()
//                        << ", Price: $" << product.getPrice() << ", Stock: " << product.getStock() << "\n";
//                }
//            }
//            else {
//                cout << "Only admins can view inventory status!\n";
//            }
//            break;
//        }
//        case 19: {//view cart
//            if (Customer* customer = dynamic_cast<Customer*>(currentUser))
//            {
//                customer->getCart().display();
//            }
//            break;
//        }
//        default:
//            cout << "Invalid choice! Please try again.\n";
//        }
//       
//
//        if (choice == 4) break;
//    }
//
//   
//    if (currentUser) {
//        delete currentUser;
//    }
//
//    return 0;
//}