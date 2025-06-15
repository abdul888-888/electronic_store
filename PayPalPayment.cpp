#include "PayPalPayment.h"
#include <iostream>

using namespace std;

PayPalPayment::PayPalPayment(double amount, const strings& email)
    : PaymentMethod("PayPal", amount), email(email) {}

bool PayPalPayment::processPayment() { return true; } 

void PayPalPayment::displayDetail() const {
    PaymentMethod::displayDetail();
    cout << "Email" << email<<"\n";
}

void PayPalPayment::displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    string details = "Payment Method: PayPal\nAmount: $" + std::to_string(amount) + "\n";
    details += "PayPal Email: " + string(email.c_str());

    text.setString(details);
    text.setPosition(position);
    window.draw(text);
}