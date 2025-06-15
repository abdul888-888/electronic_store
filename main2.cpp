
#include <SFML/Graphics.hpp>
#include "user.h"
#include "Product.h"
#include "ShoppingCart.h"
#include "Inventory.h"
#include "Customer.h"
#include "Admin.h"
#include <iostream>
#include "vectors.h"
#include "strings.h"
#include "LoginManager.h"

// Function declarations
void initializeSampleInventory(Inventory& inventory);
void renderLoginScreen(sf::RenderWindow& window, const sf::Font& font);
void renderMessage(sf::RenderWindow& window, const sf::Font& font, const std::string& message);
void renderProductDetails(sf::RenderWindow& window, const sf::Font& font, const Product& product);
void renderCheckoutScreen(sf::RenderWindow& window, const sf::Font& font, const ShoppingCart& cart, const Inventory& inventory);

int main() {
    // Window setup
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Online Electronics Store");
    window.setFramerateLimit(60);

    // Font loading with multiple fallbacks
    sf::Font mainFont;
    const std::vector<std::string> fontPaths = {
        "arial.ttf",
        "fonts/arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    bool fontLoaded = false;
    for (const auto& path : fontPaths) {
        if (mainFont.loadFromFile(path)) {
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded) {
        std::cerr << "Warning: Using default font\n";
        
        mainFont.loadFromMemory(nullptr, 0);
    }

   
    Inventory inventory;
    initializeSampleInventory(inventory);

   
    Customer customer("moeed", "bscs", "000", Date(1, 1, 2023), Address());
    Admin admin("admin", "admin@", "123", Date(1, 1, 2020), Address(), "SuperAdmin");

   
    customer.initGUI(mainFont);
    admin.initGUI(mainFont);
    ShoppingCart cart;
    cart.initGUI(mainFont);

    // Application state
    enum class AppState {
        LOGIN,
        CUSTOMER_VIEW,
        ADMIN_VIEW,
        PRODUCTS,
        PRODUCT_DETAILS,
        CART,
        CHECKOUT,
        ORDER_CONFIRMATION,
        ADMIN_PRODUCT_MGMT
    } currentState = AppState::LOGIN;

    user* currentUser = nullptr;
    string statusMessage;
    LoginManager loginManager;
    loginManager.registerCustomer("moeed", "bscs", "000", Date(1, 1, 2023), Address());
    loginManager.registerAdmin("admin", "admin@", "123", Date(1, 1, 2020), Address(), "SuperAdmin");
    // Additional UI state variables
    Product* selectedProduct = nullptr;
    int selectedProductQuantity = 1;
    sf::Clock messageTimer;
    bool showMessage = false;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle text input for login
            if (currentState == AppState::LOGIN && event.type == sf::Event::TextEntered) {
                // Could implement text entry for username/password
            }

            switch (currentState) {
            case AppState::LOGIN:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::C) {
                        strings email, password;
                        //cout << "Enter email: ";
                        //cin >> email;
                        //cout << "Enter password: ";
                        //cin >> password;
                        email = "bscs";
                        password = "000";
                      
                        currentUser = loginManager.login(email, password);

                        if (currentUser) {
                            currentState = AppState::CUSTOMER_VIEW;
                            statusMessage = "Customer logged in";
                            showMessage = true;
                            messageTimer.restart();
                        }
                        else {
                            statusMessage = "Login failed!";
                            showMessage = true;
                            messageTimer.restart();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A) {
                        currentUser = &admin;
                        currentState = AppState::ADMIN_VIEW;
                        statusMessage = "Admin logged in";
                        showMessage = true;
                        messageTimer.restart();
                    }
                }
                break;

            case AppState::CUSTOMER_VIEW:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::P) {
                        currentState = AppState::PRODUCTS;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::LOGIN;
                        currentUser = nullptr;
                    }
                }
                
                if (currentUser) {
                    static_cast<Customer*>(currentUser)->handleEvent(event);
                }
                break;

            case AppState::ADMIN_VIEW:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::M) {
                        currentState = AppState::ADMIN_PRODUCT_MGMT;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::LOGIN;
                        currentUser = nullptr;
                    }
                }
                
                if (currentUser) {
                    static_cast<Admin*>(currentUser)->handleEvent(event, inventory);
                }
                break;

            case AppState::PRODUCTS:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::C) {
                        currentState = AppState::CART;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::CUSTOMER_VIEW;
                    }
                }
                // Handle product selection
              // Handle product selection
           // Handle product selection event handling
               
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {

                    
                    cout << "Mouse clicked at: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;

                   
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                  
                    const float itemWidth = 200.f;
                    const float itemHeight = 250.f;
                    const float padding = 20.f;
                    const float startX = 20.f;
                    const float startY = 100.f;

                    
                    float x = startX;
                    float y = startY;
                    bool productSelected = false;

                   
                    try {
                       const auto& products = inventory.listAllProducts();
                        cout << "Checking " << products.size() << " products..." << std::endl;

                        for (auto& product : products) {
                            sf::FloatRect productRect(x, y, itemWidth, itemHeight);

                            // Debug product bounds
                            cout << "Product at (" << x << "," << y << ") to ("
                                << x + itemWidth << "," << y + itemHeight << ")" << std::endl;

                            if (productRect.contains(mousePos)) {
                                cout << "Selected product: " << product.getName() << std::endl;
                                selectedProduct = &product;
                                selectedProductQuantity = 1;
                                currentState = AppState::PRODUCT_DETAILS;
                                productSelected = true;
                                break;
                            }

                           
                            x += itemWidth + padding;
                            if (x + itemWidth > window.getSize().x) {
                                x = startX;
                                y += itemHeight + padding;
                            }
                        }
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error accessing products: " << e.what() << std::endl;
                    }

                    if (!productSelected) {
                        cout << "No product selected at (" << mousePos.x << "," << mousePos.y << ")" << std::endl;
                    }
                }

                break;

            case AppState::PRODUCT_DETAILS:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::PRODUCTS;
                        selectedProduct = nullptr;
                    }
                    else if (event.key.code == sf::Keyboard::Add) {
                        selectedProductQuantity++;
                    }
                    else if (event.key.code == sf::Keyboard::Subtract) {
                        if (selectedProductQuantity > 1) selectedProductQuantity--;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        // Add to cart
                        strings quant = quant.IntToString(selectedProductQuantity);
                        if (selectedProduct) {
                            cart.addItem(selectedProduct->getId(), selectedProductQuantity);
                          /*  statusMessage = "Added " + quant+
                                " " + selectedProduct->getName() + " to cart";*/
                            showMessage = true;
                            messageTimer.restart();
                            currentState = AppState::PRODUCTS;
                            selectedProduct = nullptr;
                        }
                    }
                }
                break;

            case AppState::CART:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::PRODUCTS;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        currentState = AppState::CHECKOUT;
                    }
                }
                break;

            case AppState::CHECKOUT:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::CART;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        
                        currentState = AppState::ORDER_CONFIRMATION;
                        statusMessage = "Order placed successfully!";
                        showMessage = true;
                        messageTimer.restart();
                    }
                }
                break;

            case AppState::ORDER_CONFIRMATION:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        currentState = AppState::CUSTOMER_VIEW;
                    }
                }
                break;

            case AppState::ADMIN_PRODUCT_MGMT:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::ADMIN_VIEW;
                    }
                }
                break;
            }
        }

      
        window.clear(sf::Color(240, 240, 245));

        
        switch (currentState) {
        case AppState::LOGIN:
            renderLoginScreen(window, mainFont);
            break;

        case AppState::CUSTOMER_VIEW:
            if (currentUser) currentUser->drawDashboard(window);
            renderMessage(window, mainFont, "Press P to view products | ESC to logout");
            break;

        case AppState::ADMIN_VIEW:
            if (currentUser) currentUser->drawDashboard(window);
            renderMessage(window, mainFont, "Admin dashboard | M for product management | ESC to logout");
            break;

        case AppState::PRODUCTS:
        {
            inventory.drawProductGrid(window, 20.f, 100.f, mainFont);
            std::string message = "Press C to view cart (" + std::to_string(cart.getItems().size()) +
                " items) | ESC to go back";
            renderMessage(window, mainFont, message);
        }
        break;

        case AppState::PRODUCT_DETAILS:
            if (selectedProduct) {
                renderProductDetails(window, mainFont, *selectedProduct);
                renderMessage(window, mainFont,
                    "+/- to change quantity (Qty: " + std::to_string(selectedProductQuantity) +
                    ") | Enter to add to cart | ESC to go back");
            }
            break;

        case AppState::CART:
            cart.draw(window, inventory);
            renderMessage(window, mainFont, "Enter to checkout | ESC to return to products");
            break;

        case AppState::CHECKOUT:
            renderCheckoutScreen(window, mainFont, cart, inventory);
            renderMessage(window, mainFont, "Enter to confirm order | ESC to go back");
            break;

        case AppState::ORDER_CONFIRMATION:
            if (currentUser) currentUser->drawDashboard(window);
            {
                sf::Text confirmation("Order Confirmed!", mainFont, 36);
                confirmation.setFillColor(sf::Color::Green);
                confirmation.setPosition(350.f, 300.f);
                window.draw(confirmation);
            }
            renderMessage(window, mainFont, "Press Enter to return to dashboard");
            break;

        case AppState::ADMIN_PRODUCT_MGMT:
            {
            sf::Text title("Product Management", mainFont, 36);
            title.setFillColor(sf::Color(30, 30, 120));
            title.setPosition(350.f, 50.f);
            window.draw(title);
        }
        renderMessage(window, mainFont, "ESC to return to admin dashboard");
        break;
        }

        
        if (showMessage) {
            if (messageTimer.getElapsedTime().asSeconds() < 3.0f) {
                renderMessage(window, mainFont, statusMessage);
            }
            else {
                showMessage = false;
            }
        }

        window.display();
    }

    return EXIT_SUCCESS;
}

void initializeSampleInventory(Inventory& inventory) {
    inventory.addProduct(Product(strings("P100"), strings("iPhone 15"), strings("Latest model"), 699.99, strings("smartphone"), strings("apple"), 50));
    inventory.addProduct(Product(strings("P200"), strings("EliteBook"), strings("16GB RAM"), 1299.99, strings("laptop"), strings("hp"), 30));
    inventory.addProduct(Product(strings("P300"), strings("AirPods Pro"), strings("Noise cancelling"), 199.99, strings("airpods"), strings("audionic"), 100));
    inventory.addProduct(Product(strings("P400"), strings("iPad Pro"), strings("M1 chip"), 799.99, strings("tablet"), strings("apple"), 40));
    inventory.addProduct(Product(strings("P500"), strings("Galaxy S23"), strings("Android flagship"), 899.99, strings("smartphone"), strings("samsung"), 60));
}

void renderLoginScreen(sf::RenderWindow& window, const sf::Font& font) {
    sf::Text title("Electronics Store", font, 48);
    title.setFillColor(sf::Color(30, 30, 120));
    title.setPosition(350.f, 100.f);
    window.draw(title);

    sf::Text prompt("Press C for Customer, A for Admin", font, 24);
    prompt.setFillColor(sf::Color::Black);
    prompt.setPosition(350.f, 300.f);
    window.draw(prompt);
}

void renderMessage(sf::RenderWindow& window, const sf::Font& font, const std::string& message) {
    sf::Text text(message, font, 18);
    text.setFillColor(sf::Color(70, 70, 70));
    text.setPosition(20.f, window.getSize().y - 40.f);
    window.draw(text);
}

void renderProductDetails(sf::RenderWindow& window, const sf::Font& font, const Product& product) {
    // Background
    sf::RectangleShape background(sf::Vector2f(600.f, 400.f));
    background.setPosition(200.f, 150.f);
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(background);

    // Product name
    sf::Text name(product.getName(), font, 28);
    name.setFillColor(sf::Color::Black);
    name.setPosition(220.f, 170.f);
    window.draw(name);
    int pr=product.getPrice();
    strings price = price.IntToString(pr);
    // Product details
    sf::Text details("Price: $" + price + "\n" +
        "Category: " + product.getCategory() + "\n" +
        "Brand: " + product.getCompany() + "\n" +
        "Description: " + product.getDescription(), font, 18);
    details.setFillColor(sf::Color(70, 70, 70));
    details.setPosition(220.f, 220.f);
    window.draw(details);
}

void renderCheckoutScreen(sf::RenderWindow& window, const sf::Font& font, const ShoppingCart& cart, const Inventory& inventory) {
    // Background 
    sf::RectangleShape background(sf::Vector2f(600.f, 400.f));
    background.setPosition(200.f, 150.f);
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(background);

    // Title
    sf::Text title("Checkout", font, 28);
    title.setFillColor(sf::Color::Black);
    title.setPosition(220.f, 170.f);
    window.draw(title);

    // List items
    float yPos = 220.f;
    for (const auto& item : cart.getItems()) {
        const Product* product = inventory.getProduct(item.productId);
        strings q = q.IntToString(item.quantity);
        strings P=P.IntToString(product->getPrice() * item.quantity);
        if (product) {
            sf::Text itemText(product->getName() + " x " + q+
                " - $" + P, font, 16);
            itemText.setFillColor(sf::Color(70, 70, 70));
            itemText.setPosition(220.f, yPos);
            window.draw(itemText);
            yPos += 25.f;
        }
    }

    // Total
    sf::Text totalText("Total: $" + std::to_string(cart.getTotal(inventory)), font, 20);
    totalText.setFillColor(sf::Color(0, 100, 0));
    totalText.setPosition(220.f, yPos + 20.f);
    window.draw(totalText);

    // Payment prompt
    sf::Text paymentPrompt("Press Enter to confirm order", font, 18);
    paymentPrompt.setFillColor(sf::Color(70, 70, 70));
    paymentPrompt.setPosition(220.f, yPos + 60.f);
    window.draw(paymentPrompt);
}

