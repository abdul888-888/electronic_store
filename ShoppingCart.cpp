#include "ShoppingCart.h"
#include "Product.h" 
#include <iostream>
#include "Inventory.h"
#include <SFML/Graphics.hpp>


using namespace std;

void ShoppingCart::addItem(const strings& productId, int quantity) {
    for (size_t i = 0; i < items.size(); i++) {//check if item is in cart then it will simply increase quantiyty
        if (items[i].productId == productId) {
            items[i].quantity += quantity;
            return;
        }
    }
    items.push({ productId ,quantity });//else push new product in cart
}

void ShoppingCart::removeItem(const strings& productId, int quantity) {
    for (size_t i = 0; i < items.size(); ) {
        if (items[i].productId == productId) {
            if (items[i].quantity <= quantity) {
                items.erase(items.begin() + i);
            }
            else {
                items[i].quantity -= quantity;
                i++;
            }
            return;
        }
        else {
            i++;
        }
    }
    cout << "no such item  in cart! \n";
    return ;
}

void ShoppingCart::clear() {
    items.clear();
}

double ShoppingCart::getTotal(const Inventory& inventory) const {
    double total = 0.0;
    for (const auto& item : items) {
        if (const Product* product = inventory.getProduct(item.productId)) {
            total += product->getPrice() * item.quantity;
        }
    }
    return total;
}

double ShoppingCart::getTotal(const vectors<Product>& inventory) const {
    double total = 0.0;
    for (const auto& item : items) {
        for (const auto& product : inventory) {
            if (product.getId() == item.productId) {
                total += product.getPrice() * item.quantity;
                break;
            }
        }
    }
    return total;
}

const vectors<CartItem>& ShoppingCart::getItems() const {
    return items;
}


void ShoppingCart::display() {
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "item id" << items[i].productId << " " <<" quantity" << items[i].quantity;
    }
    cout << endl;
}


// Initialize GUI components
void ShoppingCart::initGUI(sf::Font& font) {
    // Title setup
    cartTitle.setFont(font);
    cartTitle.setString("YOUR CART");
    cartTitle.setCharacterSize(32);
    cartTitle.setFillColor(sf::Color(40, 40, 140));
    cartTitle.setPosition(50, 30);

    // Column headers
    headers[0].setFont(font);
    headers[0].setString("ITEM");
    headers[0].setCharacterSize(20);
    headers[0].setFillColor(sf::Color::Black);
    headers[0].setPosition(100, 90);

    headers[1].setFont(font);
    headers[1].setString("PRICE");
    headers[1].setCharacterSize(20);
    headers[1].setFillColor(sf::Color::Black);
    headers[1].setPosition(250, 90);

    headers[2].setFont(font);
    headers[2].setString("QTY");
    headers[2].setCharacterSize(20);
    headers[2].setFillColor(sf::Color::Black);
    headers[2].setPosition(400, 90);

    headers[3].setFont(font);
    headers[3].setString("TOTAL");
    headers[3].setCharacterSize(20);
    headers[3].setFillColor(sf::Color::Black);
    headers[3].setPosition(550, 90);

    // Checkout button
    buttons[0].setSize(sf::Vector2f(200, 50));
    buttons[0].setPosition(300, 500);
    buttons[0].setFillColor(sf::Color::Green);

    buttonLabels[0].setFont(font);
    buttonLabels[0].setString("CHECKOUT");
    buttonLabels[0].setCharacterSize(20);
    buttonLabels[0].setFillColor(sf::Color::White);
    buttonLabels[0].setPosition(400, 525);

    // Clear cart button
    buttons[1].setSize(sf::Vector2f(200, 50));
    buttons[1].setPosition(550, 500);
    buttons[1].setFillColor(sf::Color(200, 50, 50));

    buttonLabels[1].setFont(font);
    buttonLabels[1].setString("CLEAR CART");
    buttonLabels[1].setCharacterSize(20);
    buttonLabels[1].setFillColor(sf::Color::White);
    buttonLabels[1].setPosition(650, 525);

    // Total display
    totalDisplay.setFont(font);
    totalDisplay.setCharacterSize(24);
    totalDisplay.setFillColor(sf::Color::Black);
    totalDisplay.setPosition(550, 450);
}

void ShoppingCart::updateTotalDisplay(const Inventory& inventory) {
    totalDisplay.setString("TOTAL: $" + std::to_string(getTotal(inventory)));
}

// Draw the shopping cart
void ShoppingCart::draw(sf::RenderWindow& window, const Inventory& inventory) const {
    // Draw background
    window.clear(sf::Color(240, 240, 245));

    // Draw title and headers
    window.draw(cartTitle);
    for (const auto& header : headers) {
        window.draw(header);
    }

    // Draw items
    float y = 130;
    for (const auto& item : items) {
        if (const Product* product = inventory.getProduct(item.productId)) {
            sf::Text name(product->getName(), *cartTitle.getFont(), 18);
            name.setPosition(100, y);
            name.setFillColor(sf::Color::Black);
            window.draw(name);

            sf::Text price("$" + std::to_string(product->getPrice()), *cartTitle.getFont(), 18);
            price.setPosition(250, y);
            window.draw(price);

            sf::Text qty(std::to_string(item.quantity), *cartTitle.getFont(), 18);
            qty.setPosition(400, y);
            window.draw(qty);

            sf::Text total("$" + std::to_string(product->getPrice() * item.quantity),
         *cartTitle.getFont(), 18);
            total.setPosition(550, y);
            window.draw(total);

            y += 30;
        }
    }

  ;
    window.draw(totalDisplay);


    for (int i = 0; i < 2; i++) { 
        window.draw(buttons[i]);
        window.draw(buttonLabels[i]);
    }
}
int ShoppingCart::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        for (int i = 0; i < 2; i++) {
            if (buttons[i].getGlobalBounds().contains(mousePos)) {
                return i + 1; // 1 = checkout, 2 = clear
            }
        }
    }
    return 0;
}
