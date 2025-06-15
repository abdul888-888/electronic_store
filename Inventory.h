#ifndef INVENTORY_H
#define INVENTORY_H

#include "vectors.h"
#include "Product.h"
#include "strings.h"

class Inventory {
private:
    vectors<Product> products;
public:
    
    bool addProduct(const Product& product);
    bool removeProduct(const strings& productId);
    const Product* getProduct(const strings& productId) const;
    vectors<Product> listProductsByCategory(const strings& category) const;
    vectors<Product> listAllProducts() const;
    vectors<Product> listProductsByPriceAndCompany(double minPrice, double maxPrice, const strings& company) const;
    void drawProductGrid(sf::RenderWindow& window, float startX, float startY, const sf::Font& font) const;
};

#endif