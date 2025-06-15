#include "Product.h"

Product::Product() :price(0),stock(0)
{
    productId="";
    name="";
    description="";
    category="";
    company="";
   
}
//Product::Product(const strings& id, const strings& name, const strings& desc, double price,
//    const strings& category, const strings& platform, const strings& company, int stock)
//    : productId(id), name(name), description(desc), price(price), category(category),
//    platform(platform), company(company), stock(stock) {}

Product::Product(const strings& id, const strings& name, const strings& desc, double price,
    const strings& category, const strings& company, int stock,
    const std::string& texturePath)
    : productId(id), name(name), description(desc), price(price), category(category),
    company(company), stock(stock) {
    if (!texturePath.empty()) {
        loadTexture(texturePath);
    }
}

bool Product::updateStock(int quantity) {
    if (stock + quantity >= 0) {
        stock += quantity;
        return true;
    }
    return false;
}
strings Product::getId() const { return productId; }
strings Product::getName() const { return name; }
strings Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
strings Product::getCategory() const { return category; }
strings Product::getCompany() const { return company; }
int Product::getStock() const { return stock; }

// SFML Methods
bool Product::loadTexture(const std::string& path) {
    return productTexture.loadFromFile(path);
}

void Product::setupVisuals(sf::Font& font) {
    productSprite.setTexture(productTexture);

    
    if (productSprite.getGlobalBounds().width > 200) {
        float scale = 200.0f / productSprite.getGlobalBounds().width;
        productSprite.setScale(scale, scale);
    }

    nameText.setString(name.c_str());
    nameText.setFont(font);
    nameText.setCharacterSize(14);

    priceText.setString("$" + std::to_string(price));
    priceText.setFont(font);
    priceText.setCharacterSize(16);
    priceText.setFillColor(sf::Color::Green);
}

void Product::draw(sf::RenderWindow& window, float posX, float posY) {
    productSprite.setPosition(posX, posY);
    nameText.setPosition(posX, posY + productSprite.getGlobalBounds().height + 5);
    priceText.setPosition(posX, posY + productSprite.getGlobalBounds().height + 25);

    window.draw(productSprite);
    window.draw(nameText);
    window.draw(priceText);
}

bool Product::contains(sf::Vector2f mousePos) const {
    return productSprite.getGlobalBounds().contains(mousePos);
}

