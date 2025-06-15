#ifndef USER_H
#define USER_H

#include "strings.h"
#include "date.h"
#include "address.h"
#include <SFML/Graphics.hpp>


class user {
    strings name;
    strings email;
    strings password;
    Date join_date;
    Address addr;

    sf::Text usernameText;
    sf::Text emailText;
    sf::RectangleShape logoutButton;
    sf::Text logoutText;
public:
    user();
    user(strings n, strings e, strings pass, Date d, Address a);
    user(const user& other);
    user& operator=(const user& other);
    virtual void displayDashboard() const;
    bool validateLogin(const strings& inputEmail, const strings& inputPassword) const;
    void updateEmail(const strings& newEmail);
    strings getName() const;
    strings getEmail() const;
    virtual ~user();

    virtual void initGUI(sf::Font& font);
    virtual void drawDashboard(sf::RenderWindow& window) const;
    virtual bool handleEvent(const sf::Event& event);

};

#endif