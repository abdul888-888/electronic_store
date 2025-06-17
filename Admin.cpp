#include "Admin.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

Admin::Admin(const strings& name, const strings& email, const strings& password, const Date& joinDate,
    const Address& address, const strings& accessLevel)
    : user(name, email, password, joinDate, address), accessLevel(accessLevel) 
{
    adminTitle = sf::Text();
    addProductButton = sf::RectangleShape();
    removeProductButton = sf::RectangleShape();
}

void Admin::displayDashboard() const {
    cout << "Admin Dashboard\n";
    user::displayDashboard();
    cout << "Access Level: " << accessLevel << "\n";
}

bool Admin::addProduct(Inventory& inventory, const Product& product) const {
    return inventory.addProduct(product);
}

bool Admin::removeProduct(Inventory& inventory, const strings& productId) const {
    return inventory.removeProduct(productId);
}

const sf::RectangleShape& Admin::getAddProductButton() const {
    return addProductButton;
}

const sf::RectangleShape& Admin::getRemoveProductButton() const {
    return removeProductButton;
}


void Admin::initGUI(sf::Font& font) {
    
    adminTitle.setFont(font);
 
    adminTitle.setCharacterSize(24);
    adminTitle.setFillColor(sf::Color(0, 100, 200)); // Dark blue
    adminTitle.setPosition(20.f, 20.f);

    
    addProductButton.setSize(sf::Vector2f(250.f, 50.f));
    addProductButton.setPosition(50.f, 100.f);
    addProductButton.setFillColor(sf::Color(50, 200, 50)); // Green
    addProductButton.setOutlineThickness(2.f);
    addProductButton.setOutlineColor(sf::Color::White);

 
    removeProductButton.setSize(sf::Vector2f(250.f, 50.f));
    removeProductButton.setPosition(50.f, 170.f);
    removeProductButton.setFillColor(sf::Color(200, 50, 50)); // Red
    removeProductButton.setOutlineThickness(2.f);
    removeProductButton.setOutlineColor(sf::Color::White);
}

//  admin dashboard
void Admin::drawDashboard(sf::RenderWindow& window) {
    
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(240, 240, 245)); // Light gray-blue
    window.draw(background);

    
    window.draw(adminTitle);

   
    window.draw(addProductButton);
    window.draw(removeProductButton);

    // Draw button labels
    sf::Font font = *adminTitle.getFont();

    sf::Text addLabel("Add New Product", font, 18);
    addLabel.setPosition(75.f, 115.f);
    addLabel.setFillColor(sf::Color::White);
    window.draw(addLabel);

    sf::Text removeLabel("Remove Product", font, 18);
    removeLabel.setPosition(75.f, 185.f);
    removeLabel.setFillColor(sf::Color::White);
    window.draw(removeLabel);

  
    user::drawDashboard(window);
}

// Handle SFML events
bool Admin::handleEvent(const sf::Event& event, Inventory& inventory) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y));

        if (addProductButton.getGlobalBounds().contains(mousePos)) {
            cout << "Add Product button clicked\n";
        
        }
        else if (removeProductButton.getGlobalBounds().contains(mousePos)) {
         
            cout << "Remove Product button clicked\n";
            
        }
        return true;
    }
    return false;
}
