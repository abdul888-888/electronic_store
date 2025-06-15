#include "Order.h"
#include <iostream>

using namespace std;

OrderItem::OrderItem() = default;
OrderItem::OrderItem(const strings& id, int qty) : productId(id), quantity(qty) {}

Order::Order() :paymentMethod(nullptr), customer(nullptr) 
{
    string randomId = to_string(time(0)) + "-" + to_string(rand() % 10000);
    orderId = randomId;
}
Order::Order(const Customer* customer, const vectors<CartItem>& items)
    : customer(customer), orderDate(time(nullptr)), status("Pending"), paymentMethod(nullptr) {
    orderId = "ORD" + orderDate;
    for (const auto& item : items) {
        this->items.push({ item.productId,item.quantity });
    }
}

Order::~Order() 
{
    delete paymentMethod;
}

string Order::getOrderId() const
{
    return orderId;
}
void Order::setPaymentMethod(PaymentMethod* method)
{
    paymentMethod = method;
}
PaymentMethod* Order:: getPaymentMethod() const
{
    return paymentMethod;
}
void Order::updateStatus(const strings& newStatus) {
    status = newStatus;
    cout << "Order " << orderId << " status updated to: " << newStatus << endl;
}

//double Order::getOrderTotal(const vectors<Product>& inventory) const {
//    double total = 0.0;
//    for (size_t i = 0; i < items.size(); i++) {
//        for (size_t j = 0; j < inventory.size(); j++) {
//            if (inventory[j].getId() == items[i].productId) {
//                total += inventory[j].getPrice() * items[i].quantity;
//                break;
//            }
//        }
//    }
//    return total;
//}
double Order::getOrderTotal(const vectors<Product>& products) const {
    double total = 0.0;
    for (int i = 0; i < items.size(); ++i) {
        for (int j = 0; j < products.size(); ++j) {
            if (products[j].getId() == items[i].productId) {
                total += products[j].getPrice() * items[i].quantity;
                break;
            }
        }
    }
    return total;
}