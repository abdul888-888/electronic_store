#ifndef ORDER_H
#define ORDER_H


#include "forward_decls.h"
#include "vectors.h"
#include "Customer.h"
#include "Product.h"
#include "PaymentMethod.h"
#include <ctime>
#include "strings.h"
#include "random"

struct OrderItem {
    strings productId;
    int quantity;
    OrderItem();
    OrderItem(const strings& id, int qty);
};

class Order {
private:
    string orderId;
    const Customer* customer;
    vectors<OrderItem> items;
    //vectors<pair<strings, int>> items; 
    time_t orderDate;
    strings status;
    PaymentMethod* paymentMethod;
public:
    Order();
    
    Order(const Customer* customer, const vectors<CartItem>&items);
    ~Order();
    string getOrderId() const;
    void setPaymentMethod(PaymentMethod* method);
    void updateStatus(const strings& newStatus);
    double getOrderTotal(const vectors<Product>& products) const;
    //double getOrderTotal(const vectors<Product>& inventory) const;
    PaymentMethod* getPaymentMethod() const;
};

#endif