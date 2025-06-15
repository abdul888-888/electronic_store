#ifndef ADDRESS_H
#define ADDRESS_H

#include "strings.h"

class Address {
    strings area;
    strings province;
    strings country;
    strings city;
public:
    Address();
    Address(strings area, strings province, strings country, strings city);
    void print();
    Address(const Address& a);
    Address operator=(const Address& a);

    friend std::ostream& operator<<(std::ostream& os, const Address& ad);
    friend std::istream& operator>>(std::istream& is, Address& ad);
};

#endif