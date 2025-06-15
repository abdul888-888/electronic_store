#include "Inventory.h"
#include <iostream>

#include <SFML/Graphics.hpp>
//#include <iomanip>  

using namespace std;

bool Inventory::addProduct(const Product& product) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == product.getId()) {
            cout << "Product already exists!" << endl;
            return false;
        }
    }
    products.push(product);
    return true;
}

bool Inventory::removeProduct(const strings& productId) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == productId) {
            products.erase(products.begin() + i);
            return true;
        }
    }
    cout << "Product not found!" << endl;
    return false;
}

const Product* Inventory::getProduct(const strings& productId) const {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == productId) {
            return &products[i];
        }
    }
    return nullptr;
}

vectors<Product> Inventory::listAllProducts() const {
   
    return products;
}

vectors<Product> Inventory::listProductsByCategory(const strings& category) const {
    vectors<Product> result;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getCategory() == category) {
            result.push(products[i]);
        }
    }
    return result;
}

vectors<Product> Inventory::listProductsByPriceAndCompany(double minPrice, double maxPrice,
    const strings& company) const {
    vectors<Product> result;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getPrice() >= minPrice && products[i].getPrice() <= maxPrice &&
            products[i].getCompany() == company) {
            result.push(products[i]);
        }
    }
    return result;
}



#include <sstream> 
 
#include <cstdio>   
void Inventory::drawProductGrid(sf::RenderWindow& window, float startX, float startY, const sf::Font& font) const {

    const float itemWidth = 200.f;
    const float itemHeight = 250.f;
    const float padding = 20.f;

    float x = startX;
    float y = startY;

    for (const auto& product : products) {
       
        sf::RectangleShape card(sf::Vector2f(itemWidth, itemHeight));
        card.setPosition(x, y);
        card.setFillColor(sf::Color::White);
        card.setOutlineThickness(1.f);
        card.setOutlineColor(sf::Color(200, 200, 200));
        window.draw(card);

        
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(std::string(product.getName().c_str())); 
        nameText.setCharacterSize(16);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(x + 10.f, y + 10.f);
        window.draw(nameText);

       
        char priceBuffer[32];
        std::snprintf(priceBuffer, sizeof(priceBuffer), "$%.2f", product.getPrice());

        sf::Text priceText;
        priceText.setFont(font);
        priceText.setString(priceBuffer);
        priceText.setCharacterSize(18);
        priceText.setFillColor(sf::Color(0, 100, 0));
        priceText.setPosition(x + 10.f, y + itemHeight - 40.f);
        window.draw(priceText);

       

        // 4. Move to next position
        x += itemWidth + padding;
        if (x + itemWidth > window.getSize().x) {
            x = startX;
            y += itemHeight + padding;
        }
    }
}
 