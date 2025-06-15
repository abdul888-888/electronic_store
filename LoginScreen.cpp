#include "LoginScreen.h"
#include <iostream>
#include "strings.h"

LoginScreen::LoginScreen() {
    usernameInput = strings();
    passwordInput = strings();
    emailInput = strings();
    usernameActive = false;
    passwordActive = false;
    emailActive = false;
    currentMode = AuthMode::LOGIN;
}

void LoginScreen::init(sf::Font& font) {
    // Setup title
    titleText.setFont(font);
    titleText.setString("Welcome to Online Store");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(300.f, 50.f);

    // Setup input fields
    float fieldWidth = 400.f;
    float fieldHeight = 50.f;
    float startY = 150.f;
    float spacing = 70.f;

    usernameField.setSize(sf::Vector2f(fieldWidth, fieldHeight));
    usernameField.setPosition(300.f, startY);
    usernameField.setFillColor(sf::Color::White);
    usernameField.setOutlineThickness(2.f);
    usernameField.setOutlineColor(sf::Color::Black);

    passwordField.setSize(sf::Vector2f(fieldWidth, fieldHeight));
    passwordField.setPosition(300.f, startY + spacing);
    passwordField.setFillColor(sf::Color::White);
    passwordField.setOutlineThickness(2.f);
    passwordField.setOutlineColor(sf::Color::Black);

    emailField.setSize(sf::Vector2f(fieldWidth, fieldHeight));
    emailField.setPosition(300.f, startY + 2 * spacing);
    emailField.setFillColor(sf::Color(200, 200, 200)); // Grayed out for login mode
    emailField.setOutlineThickness(2.f);
    emailField.setOutlineColor(sf::Color::Black);

    // Setup action button
    actionButton.setSize(sf::Vector2f(200.f, 60.f));
    actionButton.setPosition(400.f, startY + 3 * spacing);
    actionButton.setFillColor(sf::Color(0, 150, 0)); // Green

    actionButtonText.setFont(font);
    actionButtonText.setCharacterSize(24);
    actionButtonText.setFillColor(sf::Color::White);
    actionButtonText.setString("LOGIN");
    actionButtonText.setPosition(475.f, startY + 3 * spacing + 15.f);

    // Setup mode switch text
    switchModeText.setFont(font);
    switchModeText.setCharacterSize(20);
    switchModeText.setFillColor(sf::Color::White);
    switchModeText.setString("Don't have an account? Click here to register");
    switchModeText.setPosition(350.f, startY + 4 * spacing);

    updateModeDisplay();
}

void LoginScreen::updateModeDisplay() {
    if (currentMode == AuthMode::LOGIN) {
        actionButtonText.setString("LOGIN");
        switchModeText.setString("Don't have an account? Click here to register");
        emailField.setFillColor(sf::Color(200, 200, 200)); // Gray out email field
        emailActive = false;
    }
    else {
        actionButtonText.setString("REGISTER");
        switchModeText.setString("Already have an account? Click here to login");
        emailField.setFillColor(sf::Color::White); // Enable email field
    }
}

void LoginScreen::draw(sf::RenderWindow& window) const {
    // Draw background
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(30, 30, 120)); // Dark blue background
    window.draw(background);

    // Draw title
    window.draw(titleText);

    // Draw input fields
    window.draw(usernameField);
    window.draw(passwordField);
    window.draw(emailField);

    // Draw labels
    sf::Text usernameLabel("Username:", *titleText.getFont(), 24);
    usernameLabel.setPosition(150.f, 160.f);
    usernameLabel.setFillColor(sf::Color::White);
    window.draw(usernameLabel);

    sf::Text passwordLabel("Password:", *titleText.getFont(), 24);
    passwordLabel.setPosition(150.f, 230.f);
    passwordLabel.setFillColor(sf::Color::White);
    window.draw(passwordLabel);

    sf::Text emailLabel("Email:", *titleText.getFont(), 24);
    emailLabel.setPosition(150.f, 300.f);
    emailLabel.setFillColor(sf::Color::White);
    window.draw(emailLabel);

    // Draw input text
    sf::Text usernameDisplay(usernameInput.c_str(), *titleText.getFont(), 24);
    usernameDisplay.setPosition(310.f, 160.f);
    usernameDisplay.setFillColor(sf::Color::Black);
    window.draw(usernameDisplay);

    // Draw password as asterisks
    int passwordLength = passwordInput.get_len(); // Fix: Use passwordInput
    strings passwordDisplay(passwordLength, '*');
    sf::Text passwordText(passwordDisplay.c_str(), *titleText.getFont(), 24);
    passwordText.setPosition(310.f, 230.f);
    passwordText.setFillColor(sf::Color::Black);
    window.draw(passwordText);

    // Draw email
    sf::Text emailDisplay(emailInput.c_str(), *titleText.getFont(), 24);
    emailDisplay.setPosition(310.f, 300.f);
    emailDisplay.setFillColor(currentMode == AuthMode::REGISTER ? sf::Color::Black : sf::Color(100, 100, 100));
    window.draw(emailDisplay);

    // Draw action button and mode switch text
    window.draw(actionButton);
    window.draw(actionButtonText);
    window.draw(switchModeText);
}
void LoginScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        // Set focus for input fields
        usernameActive = usernameField.getGlobalBounds().contains(mousePos);
        passwordActive = passwordField.getGlobalBounds().contains(mousePos);
        emailActive = (currentMode == AuthMode::REGISTER) && emailField.getGlobalBounds().contains(mousePos);

        // Update field outlines based on focus
        usernameField.setOutlineColor(usernameActive ? sf::Color::Blue : sf::Color::Black);
        passwordField.setOutlineColor(passwordActive ? sf::Color::Blue : sf::Color::Black);
        emailField.setOutlineColor(emailActive ? sf::Color::Blue : sf::Color::Black);

        // Handle mode switch
        if (switchModeText.getGlobalBounds().contains(mousePos)) {
            toggleMode();
        }
    }
    else if (event.type == sf::Event::TextEntered && (usernameActive || passwordActive || emailActive)) {
        // Handle text input
        if (event.text.unicode == '\b') { // Backspace
            if (usernameActive && usernameInput.get_len() > 0) {
                usernameInput.remove_at(usernameInput.get_len() - 1);
            }
            else if (passwordActive && passwordInput.get_len() > 0) {
                passwordInput.remove_at(passwordInput.get_len() - 1);
            }
            else if (emailActive && emailInput.get_len() > 0) {
                emailInput.remove_at(emailInput.get_len() - 1);
            }
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\r') { // Printable ASCII characters
            char ch = static_cast<char>(event.text.unicode);
            if (usernameActive && usernameInput.get_len() < 20) {
                usernameInput.insert_char(ch, usernameInput.get_len());
            }
            else if (passwordActive && passwordInput.get_len() < 20) {
                passwordInput.insert_char(ch, passwordInput.get_len());
            }
            else if (emailActive && emailInput.get_len() < 50) {
                emailInput.insert_char(ch, emailInput.get_len());
            }
        }
    }
}

void LoginScreen::toggleMode() {
    currentMode = (currentMode == AuthMode::LOGIN) ? AuthMode::REGISTER : AuthMode::LOGIN;
    clearFields();
    updateModeDisplay();
}

void LoginScreen::clearFields() {
    usernameInput.clear();
    passwordInput.clear();
    emailInput.clear();
    usernameActive = false;
    passwordActive = false;
    emailActive = false;
    usernameField.setOutlineColor(sf::Color::Black);
    passwordField.setOutlineColor(sf::Color::Black);
    emailField.setOutlineColor(sf::Color::Black);
}

strings  LoginScreen::getUsername() const { return usernameInput; }
strings  LoginScreen::getPassword() const { return passwordInput; }
strings  LoginScreen::getEmail() const { return emailInput; }