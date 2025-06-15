#ifndef STRINGS_H
#define STRINGS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "date.h"

class strings {
private:
    int len;
    int cap;
    char* Cs;

public:
    strings();
    strings(const char* ptr);
    strings(const strings& other);
    strings(int n, char a);
    ~strings();
    int get_len() const;
    int get_len(const char arr[]);
    void regrow();
    void right_shift(int idx);
    void left_shift(char arr[], int& size, int idx);
    bool search_s(char arr[], char var[]);
    strings* regrow_strings(int& count);

    strings& operator=(const strings other);

    strings insert_char(char a, int idx);
    strings concat(const strings& s2) const;
    strings& append(const strings& s2);
    strings& Trim();
    strings& Triming();
    strings IntToString(int num);

    int find_first(char ch);
    int find_first_st(const strings& other, int count) const;
    int find_last(char ch);
    int find_last_st(const strings& other, int count) const;
    int* find_all(char ch, int& C, int array[]);
    int* find_all_st(const strings& other, int& C, int count, int array[]) const;

    void remove_at(int i);
    void insert_at(int i, char ch);
    void insert_at_st(int i, const strings sub, int& count);
    void remove_first(char ch);
    void remove_last(char ch);
    void remove_all(char ch);
    void clear();
    strings& toUpper();
    strings& toLower();

    int st_oi();

    strings* split(char delim, int& count) const;

    bool is_equal(const strings& M);
    bool is_less(const strings& M);
    bool is_greater(const strings& M);
    bool operator==(const strings& other) const;

    char& operator[](int i);
    const char operator[](int i) const;

    friend std::ostream& operator<<(std::ostream& os, const strings& str);
    friend std::istream& operator>>(std::istream& is, strings& str);

  //  strings operator+(const Date& s2);
    strings operator+(const strings& s2);
    friend strings operator+(const strings& s1, const strings& s2);

    operator sf::String() const {
        return sf::String(this->c_str());
    }

    // Ensure c_str() exists
    const char* c_str() const {
        // Return your internal char array
        return Cs; // Assuming 'Cs' is your internal char*
    }
    /*
    operator sf::String() const {
        return sf::String(this->c_str());
    }*/
   
   friend strings intToString(int num);

    void print();
};

int conv_int(char arr[]);

#endif