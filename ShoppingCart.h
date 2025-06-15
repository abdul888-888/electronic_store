#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H



#include "forward_decls.h"
#include "vectors.h"
#include "strings.h"
#include <SFML/Graphics.hpp>


struct CartItem {
    strings productId;
   // strings productName;
    int quantity;
};

class ShoppingCart {
private:
    vectors<CartItem> items;

    sf::Text totalText;
    sf::RectangleShape checkoutButton;
    sf::RectangleShape continueShoppingButton;
    sf::Text cartTitle;
    sf::Text headers[4];       // For ITEM, PRICE, QTY, TOTAL
    sf::RectangleShape buttons[2]; // Checkout and Clear buttons
    sf::Text buttonLabels[2];  // Button text
    sf::Text totalDisplay;
public:
    void addItem(const strings& productId, int quantity);
    void removeItem(const strings& productId, int quantity);
    void clear();
    double getTotal(const Inventory& inventory) const;
    double getTotal(const vectors<Product>& inventory) const;
    const vectors<CartItem>& getItems() const;

    void display();
   
    void updateTotalDisplay(const Inventory& inventory);

    void initGUI(sf::Font& font);
    void draw(sf::RenderWindow& window, const Inventory& inventory) const;
    int handleEvent(const sf::Event& event);
    
};

#endif