#include "address.h"
#include <iostream>

using namespace std;

Address::Address() : area(strings()), province(strings()), country(strings()), city(strings()) {}

Address::Address(strings area, strings province, strings country, strings city)
    : area(strings(area)), province(strings(province)), country(strings(country)), city(strings(city)) {}

void Address::print() {
    cout << area << " " << province << " " << country << " " << city << endl;
}

Address::Address(const Address& a)
{
    area = a.area;
    province = a.province;
    country = a.country;
    city = a.city;
}
Address Address::operator=(const Address& a) {
    if (&a != this) {
        area = a.area;
        province = a.province;
        country = a.country;
        city = a.city;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Address& ad) {
    os << ad.area << " " << ad.city << " " << ad.country << " " << ad.province;
    return os;
}

std::istream& operator>>(std::istream& is, Address& ad) {
    strings temp_area, temp_city, temp_country, temp_province;
    is >> temp_area >> temp_city >> temp_country >> temp_province;
    ad.area = temp_area;
    ad.city = temp_city;
    ad.country = temp_country;
    ad.province = temp_province;
    return is;
}