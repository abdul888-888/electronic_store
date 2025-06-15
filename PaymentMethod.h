// PaymentMethod.h
#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

#include "strings.h"
#include <SFML/Graphics.hpp> // Include for sf::RenderWindow, sf::Font, sf::Vector2f

class PaymentMethod {
protected:
    strings type;
    double amount;
public:
    PaymentMethod(const strings& type, double amount);
    virtual ~PaymentMethod();
    virtual  bool processPayment() = 0;
    virtual void displayDetail() const ;
    virtual void displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const = 0;
    strings getType() const;
    virtual double getAmount() const;// Provide default implementation if not pure virtual
};

#endif