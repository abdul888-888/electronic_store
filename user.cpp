#include "user.h"
#include <iostream>

using namespace std;

user::user() : name(""), email(""), password(""), join_date(Date()), addr(Address()) {}
user::user(strings n, strings e, strings pass, Date d, Address a)
    : name(strings(n)), email(strings(e)), password(strings(pass)), join_date(Date(d)), addr(Address(a)) {}
user::user(const user& other) : name(strings(other.name)), email(strings(other.email)),
password(strings(other.password)), join_date(Date(other.join_date)), addr(Address(other.addr)) {}
user& user::operator=(const user& other) {
    if (&other != this) {
        name = other.name;
        email = other.email;
        password = other.password;
        join_date = other.join_date;
        addr = other.addr;
    }
    return *this;
}
void user::displayDashboard() const {
    cout << "Username: " << name << "\n";
    cout << "Email: " << email << "\n";
    cout << "address" << addr << "\n";
}
bool user::validateLogin(const strings& inputEmail, const strings& inputPassword) const {
    return email == inputEmail && password == inputPassword;
}
void user::updateEmail(const strings& newEmail) {
    email = newEmail;
}
strings user::getName() const { return name; }
strings user::getEmail() const { return email; }
user::~user() {}

// Initialize GUI components
void user::initGUI(sf::Font& font) {
    // Set up username display
    usernameText.setFont(font);
    usernameText.setString("User: " + name);
    usernameText.setCharacterSize(20);
    usernameText.setFillColor(sf::Color::White);
    usernameText.setPosition(20.f, 20.f);

    // Set up email display
    emailText.setFont(font);
    emailText.setString("Email: " + email);
    emailText.setCharacterSize(18);
    emailText.setFillColor(sf::Color(200, 200, 200)); // Light gray
    emailText.setPosition(20.f, 50.f);

    // Set up logout button
    logoutButton.setSize(sf::Vector2f(120.f, 40.f));
    logoutButton.setPosition(650.f, 20.f);
    logoutButton.setFillColor(sf::Color(200, 50, 50)); // Red
    logoutButton.setOutlineThickness(2.f);
    logoutButton.setOutlineColor(sf::Color::White);

    // Logout button label
    logoutText.setFont(font);
    logoutText.setString("Logout");
    logoutText.setCharacterSize(18);
    logoutText.setFillColor(sf::Color::White);
    logoutText.setPosition(670.f, 28.f);
}
void user::drawDashboard(sf::RenderWindow& window) const {
    // Draw user info
    window.draw(usernameText);
    window.draw(emailText);

    // Draw logout button
    window.draw(logoutButton);
    window.draw(logoutText);

    // Draw join date if available
  
        sf::Text joinDateText;
        int day = join_date.get_day();
        int months = join_date.get_month();
        int years = join_date.get_year();
        strings date =date.IntToString(day);
        strings month = month.IntToString(months);
        strings year = year.IntToString(years);
        
        joinDateText.setFont(*usernameText.getFont());
        joinDateText.setString("Member since: " +date+month+year);
        joinDateText.setCharacterSize(16);
        joinDateText.setFillColor(sf::Color(180, 180, 180));
        joinDateText.setPosition(20.f, 80.f);
        window.draw(joinDateText);
    
}

// Handle SFML events
bool user::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y));

        if (logoutButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Logout requested for user: " << name << std::endl;
            return true; // Indicate logout request
        }
    }
    return false;
}

