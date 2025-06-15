#ifndef ADMIN_H
#define ADMIN_H


#include "user.h"
#include "Inventory.h"
#include <SFML/Graphics.hpp>


class Admin : public user {
    strings accessLevel;
    sf::Text adminTitle;
    sf::RectangleShape addProductButton;
    sf::RectangleShape removeProductButton;
public:
    Admin(const strings& name, const strings& email, const strings& password, const Date& joinDate,
        const Address& address, const strings& accessLevel);
    void displayDashboard() const;
    bool addProduct(Inventory& inventory, const Product& product) const;
    bool removeProduct(Inventory& inventory, const strings& productId) const;

    const sf::RectangleShape& getAddProductButton() const;
    const sf::RectangleShape& getRemoveProductButton() const;
    void initGUI(sf::Font& font);
    void drawDashboard(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event, Inventory& inventory);
};

#endif


