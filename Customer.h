#ifndef CUSTOMER_H
#define CUSTOMER_H


#include "forward_decls.h"
#include "user.h"
#include "ShoppingCart.h"
#include "Order.h"
#include "vectors.h"

class Customer : public user {
private:
    strings shippingAddress;
    ShoppingCart cart;
    vectors<Order> orderHistory;

    sf::Text customerTitle;
    sf::RectangleShape viewCartButton;
    sf::RectangleShape checkoutButton;

public:
    Customer(const strings& username, const strings& email, const strings& password,const Date& date,
        const Address& address);
    void displayDashboard() const override;
    void setShippingAddress(const strings& address);
    ShoppingCart& getCart();
    const ShoppingCart& getCart()const;
    void addToOrderHistory(const Order& order);
    const vectors<Order>& getOrderHistory() const;

    void initGUI(sf::Font& font);
    void drawDashboard(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event) override;  
};

#endif