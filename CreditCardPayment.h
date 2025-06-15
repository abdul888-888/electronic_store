#ifndef CREDITCARDPAYMENT_H
#define CREDITCARDPAYMENT_H

#include "PaymentMethod.h"
#include <string>

class CreditCardPayment : public PaymentMethod {
    strings cardNumber;
    strings expiryDate;
public:
    CreditCardPayment(double amount, const strings& cardNumber, const strings& expiryDate);
    bool processPayment() override;
    //void displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const override;
    void displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const override;
    void displayDetail() const override;
};

#endif