#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(const strings& username, const strings& email, const strings& password,const  Date& date,
    const Address& address) : user(username, email, password, date, address) {
    customerTitle = sf::Text();
    viewCartButton = sf::RectangleShape();
    checkoutButton = sf::RectangleShape();
}

void Customer::displayDashboard() const {
    cout << "Customer Dashboard\n";
    user::displayDashboard();
   // cout << "Shipping Address: " << shippingAddress << "\n";
    cout << "Items in cart: " << static_cast<int>(cart.getItems().size()) << "\n";
    cout << "Orders placed: " << static_cast<int>(orderHistory.size()) << "\n";
}

void Customer::setShippingAddress(const strings& address) {
    shippingAddress = address;
}

ShoppingCart& Customer::getCart() {
    return cart;
}

const ShoppingCart& Customer::getCart() const {
    return cart;
}

void Customer::addToOrderHistory(const Order& order) {
    orderHistory.push(order);
}

const vectors<Order>& Customer::getOrderHistory() const {
    return orderHistory;
}

void Customer::initGUI(sf::Font& font) {
    // Setup customer title
    customerTitle.setFont(font);
    customerTitle.setString("Welcome, " + getName());
    customerTitle.setCharacterSize(24);
    customerTitle.setFillColor(sf::Color(50, 150, 50)); // Green
    customerTitle.setPosition(20.f, 20.f);

    // Setup view cart button
    viewCartButton.setSize(sf::Vector2f(200.f, 45.f));
    viewCartButton.setPosition(50.f, 100.f);
    viewCartButton.setFillColor(sf::Color(70, 70, 200)); // Blue
    viewCartButton.setOutlineThickness(2.f);
    viewCartButton.setOutlineColor(sf::Color::White);

    // Setup checkout button
    checkoutButton.setSize(sf::Vector2f(200.f, 45.f));
    checkoutButton.setPosition(50.f, 160.f);
    checkoutButton.setFillColor(sf::Color(200, 100, 50)); // Orange
    checkoutButton.setOutlineThickness(2.f);
    checkoutButton.setOutlineColor(sf::Color::White);
}

// Draw the customer dashboard
void Customer::drawDashboard(sf::RenderWindow& window) {
    // Draw background
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(245, 245, 250)); // Very light gray
    window.draw(background);

    // Draw title
    window.draw(customerTitle);

    // Draw buttons
    window.draw(viewCartButton);
    window.draw(checkoutButton);

    // Draw button labels
    sf::Font font = *customerTitle.getFont();

    sf::Text cartLabel("View My Cart", font, 18);
    cartLabel.setPosition(75.f, 110.f);
    cartLabel.setFillColor(sf::Color::White);
    window.draw(cartLabel);

    sf::Text checkoutLabel("Proceed to Checkout", font, 16);
    checkoutLabel.setPosition(60.f, 170.f);
    checkoutLabel.setFillColor(sf::Color::White);
    window.draw(checkoutLabel);

    // Draw cart summary
    sf::Text cartSummary("Items in cart: " + std::to_string(cart.getItems().size()), font, 18);
    cartSummary.setPosition(300.f, 100.f);
    cartSummary.setFillColor(sf::Color::Black);
    window.draw(cartSummary);

    // Draw order history summary
    sf::Text orderSummary("Total orders: " + std::to_string(orderHistory.size()), font, 18);
    orderSummary.setPosition(300.f, 130.f);
    orderSummary.setFillColor(sf::Color::Black);
    window.draw(orderSummary);

    // Draw user info from base class
    user::drawDashboard(window);
}

// Handle SFML events
bool Customer::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y));

        if (viewCartButton.getGlobalBounds().contains(mousePos)) {
            cout << "View Cart button clicked\n";
            return true;  // Event handled
        }
        else if (checkoutButton.getGlobalBounds().contains(mousePos)) {
            cout << "Checkout button clicked\n";
            return true;  // Event handled
        }
    }
    return false;  // Event not handled
}