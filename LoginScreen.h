#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <SFML/Graphics.hpp>
#include "strings.h"

class LoginScreen {
public:
    enum class AuthMode { LOGIN, REGISTER };

private:
    sf::Text titleText;
    sf::RectangleShape usernameField;
    sf::RectangleShape passwordField;
    sf::RectangleShape emailField;
    sf::Text actionButtonText;
    sf::Text switchModeText;
    sf::RectangleShape actionButton;
    strings usernameInput;
    strings passwordInput;
    strings emailInput;
    bool usernameActive;
    bool passwordActive;
    bool emailActive;
    AuthMode currentMode;

public:
    LoginScreen();
    void init(sf::Font& font);
    void updateModeDisplay();
    void draw(sf::RenderWindow& window) const;
    void handleEvent(const sf::Event& event);
    void toggleMode();
    void clearFields();
    const sf::RectangleShape& getActionButton() const { return actionButton; }
    AuthMode getCurrentMode() const { return currentMode; }
    strings getUsername() const;
    strings getPassword() const;
    strings getEmail() const;
};

#endif