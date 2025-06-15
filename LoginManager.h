#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "vectors.h"
#include "user.h"
#include "Customer.h"
#include "Admin.h"
#include "memory"

class LoginManager {
private:
   // vectors<unique_ptr<user>> users;
    vectors<shared_ptr<user>> users;
  // vectors<user> *users;
public:
    void registerCustomer(const strings& username, const strings& email, const strings& password,
        const Date& date, const Address& addr);
    void registerAdmin(const strings& username, const strings& email, const strings& password,
        const Date& date, const Address& addr, const strings& accessLevel);
    user* login(const strings& email, const strings& password) const;
};

#endif