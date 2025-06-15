#include "CreditCardPayment.h"
#include <iostream>
#include <string>

using namespace std;

CreditCardPayment::CreditCardPayment(double amount, const strings& cardNumber, const strings& expiryDate)
    : PaymentMethod("Credit Card", amount), cardNumber(cardNumber), expiryDate(expiryDate) {}

bool CreditCardPayment::processPayment() { return true; }

void CreditCardPayment::displayDetail() const {
    PaymentMethod::displayDetail();
    cout << "Card Number: ****-****-****-" << cardNumber
        << "\nExpiry: " << expiryDate << endl;
}
void CreditCardPayment::displayDetails(sf::RenderWindow& window, sf::Font& font, const sf::Vector2f& position) const {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    // Base payment details
    std::string details = "Payment Method: Credit Card\nAmount: $" + std::to_string(amount) + "\n";
    details += "Card Number: ****-****-****-" + std::string(cardNumber.c_str()) + "\n";
    details += "Expiry: " + std::string(expiryDate.c_str());

    text.setString(details);
    text.setPosition(position);
    window.draw(text);
}