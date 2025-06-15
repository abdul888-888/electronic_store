#ifndef PAYPALPAYMENT_H
#define PAYPALPAYMENT_H

#include "PaymentMethod.h"

class PayPalPayment : public PaymentMethod {
    strings email;
public:
    PayPalPayment(double amount, const strings& email);
    bool processPayment() override;
    void displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const override;
    void displayDetail() const override;
};


#endif