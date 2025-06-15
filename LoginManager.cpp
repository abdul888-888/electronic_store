#include "LoginManager.h"
#include <iostream>

using namespace std;

void LoginManager::registerCustomer(const strings& username, const strings& email,
    const strings& password, const Date& date, const Address& addr) {
    users.push(make_unique<Customer>(username, email, password, date, addr));
}

void LoginManager::registerAdmin(const strings& username, const strings& email,
    const strings& password, const Date& date, const Address& addr,
    const strings& accessLevel) {
    users.push(make_unique<Admin>(username, email, password, date, addr, accessLevel));
}

user* LoginManager::login(const strings& email, const strings& password) const {
    for (const auto& user : users) {
        if (user->validateLogin(email, password)) {
            if (dynamic_cast<Admin*>(user.get())) {
                cout << "Admin login successful!\n";
            }
            else {
                cout << "Customer login successful!\n";
            }
            return user.get();
        }
    }
    cout << "Login failed: invalid email or password!\n";
    return nullptr;
}