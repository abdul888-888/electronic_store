#include "PaymentMethod.h"
#include <iostream>

using namespace std;

PaymentMethod::PaymentMethod(const strings& type, double amount) : type(type), amount(amount) {}
PaymentMethod::~PaymentMethod() {}
void PaymentMethod::displayDetail() const {
    cout << "Payment Type: " << type << "\nAmount: $" << amount << endl;
}
strings PaymentMethod::getType() const { return type; }
double PaymentMethod::getAmount() const { return amount; }