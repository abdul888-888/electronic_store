#include "strings.h"

using namespace std;


strings::strings() {
    len = 0;
    cap = 0;
    Cs = nullptr;
}

strings::strings(const char* ptr) {
    int size = get_len(ptr);
    this->len = size;
    this->cap = size + 1;
    Cs = new char[cap];
    for (int i = 0; i < size; i++) {

        Cs[i] = ptr[i];
    }
    Cs[size] = '\0';
}


strings::strings(const strings& other) {
    this->len = other.len;
    this->cap = other.cap;
    Cs = new char[cap + 1];

    for (int i = 0; i < len; i++) {
        Cs[i] = other.Cs[i];
    }
    Cs[len] = '\0';
}

strings::strings(int n, char a) {
    this->len = n;
    this->cap = n;
    Cs = new char[n];
    for (int i = 0; i < n; i++) {
        Cs[i] = a;
    }
}

strings::~strings() {
    delete[] Cs;
}
int strings::get_len() const
{
    return len;
}
// Helper functions
int strings::get_len(const char arr[]) {
    int count = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        count++;
    }
    return count;
}

void strings::regrow() {
    char* new_ptr = new char[cap * 2 + 1];
    for (int i = 0; i < len; i++) {
        new_ptr[i] = Cs[i];
    }
    delete[] Cs;
    Cs = new_ptr;
    this->cap = cap * 2 + 1;
}

void strings::right_shift(int idx) {
    if (len == cap) {
        regrow();
    }
    for (int i = len; i > idx; i--) {
        Cs[i] = Cs[i - 1];
    }
    len++; //
    Cs[len] = '\0'; 
}
void strings::left_shift(char arr[], int& size, int idx) {
    for (int i = idx; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}

bool strings::search_s(char arr[], char var[]) {
    int size = get_len(var);
    int size_2 = get_len(arr);
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size_2; l++) {
            if (var[i] == arr[l]) {
                return true;
            }
        }
    }
    return false;
}

strings* strings::regrow_strings(int& count) {
    strings* new_ptr = new strings[count + 1];
    for (int i = 0; i < count; i++) {
        new_ptr[i] = this[i];
    }
    delete[] this;
    count++;
    return new_ptr;
}

// Assignment operator
strings& strings::operator=(const strings other) {

    if (this != &other) {  // Better self-assignment check
        delete[] Cs;
        len = other.len;
        cap = other.cap;
        Cs = new char[cap];
        for (int i = 0; i < len; i++) {  // Copy null terminator too
            Cs[i] = other.Cs[i];
        }
    }
    return *this;

}

// String operations
strings strings::insert_char(char a, int idx) {
    if (idx < 0 || idx > len) return *this; // Invalid index, return unchanged
    if (len == cap) {
        regrow();
    }
    right_shift(idx); 
    Cs[idx] = a;
    Cs[len] = '\0'; 
    return *this; 
}

strings strings::concat(const strings& s2) const {
    strings temp;
    temp.len = this->len + s2.len;
    temp.Cs = new char[temp.len];
    temp.cap = temp.len;

    for (int i = 0; i < len; i++) {
        temp.Cs[i] = Cs[i];
    }

    for (int i = 0, l = len; i < s2.len; i++, l++) {
        temp.Cs[l] = s2.Cs[i];
    }
    return temp;
}

strings& strings::append(const strings& s2) {
    for (int i = 0; i < s2.len; i++, len++) {
        if (s2.len > cap) {
            regrow();
        }
        Cs[len] = s2.Cs[i];
    }
    return (*this);
}

strings& strings::Trim() {
    bool flag = false;
    int count = 0;
    int idx = 0;
    int f = 0;
    for (int i = 0; i < len; i++) {
        if (Cs[i] != ' ' && Cs[i] != '\n' && Cs[i] != '\t') {
            flag = false;
            idx = i;
            break;
        }
        else {
            flag = true;
            count++;
        }
    }
    if (flag == false) {
        while (f < count) {
            left_shift(Cs, len, idx - 1);
            idx--;
            f++;
        }
    }

    for (int i = len - 1; i >= 0; i--) {
        if (Cs[i] != ' ' && Cs[i] != '\n') {
            flag = false;
            break;
        }
        else {
            flag = true;
            count++;
        }
    }
    if (flag == false) {
        idx = len;
        while (f < count) {
            left_shift(Cs, len, idx);
            idx--;
            f++;
        }
    }
    return *this;
}

strings& strings::Triming() {
    return Trim();
}

strings strings::IntToString(int num) {
    while (num != 0) {
        if (len == cap) {
            regrow();
        }
        int n = num % 10;
        this->Cs[len] = n + '0';
        num /= 10;
        len++;
    }
    int tempLength = len;
    for (int i = 0; i < tempLength; i++) {
        int temp = Cs[i];
        Cs[i] = Cs[tempLength - 1];
        Cs[tempLength - 1] = temp;
        tempLength--;
    }
    Cs[len] = '\0';
    return *this;
}

// Search operations
int strings::find_first(char ch) {
    int idx = -1;
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            idx = i;
            break;
        }
    }
    return idx;
}

int strings::find_first_st(const strings& other, int count) const {
    bool flag = false;
    for (int i = 0; i < count; i++) {
        for (int l = 0; l < other.len; l++) {
            if (this[i].Cs[l] != other.Cs[l] && this[i].len != other.len) {
                flag = false;
                break;
            }
            else {
                flag = true;
            }
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

int strings::find_last(char ch) {
    int idx = -1;
    for (int i = len - 1; i >= 0; i--) {
        if (Cs[i] == ch) {
            idx = i;
            break;
        }
    }
    return idx;
}

int strings::find_last_st(const strings& other, int count) const {
    bool flag = false;
    for (int i = count - 1; i >= 0; i--) {
        for (int l = 0; l < other.len; l++) {
            if (this[i].Cs[l] != other.Cs[l] && this[i].len != other.len) {
                flag = false;
                break;
            }
            else {
                flag = true;
            }
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

int* strings::find_all(char ch, int& C, int array[]) {
    int* ptr = array;
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            C++;
            ptr[idx] = i;
            idx++;
        }
    }
    return ptr;
}

int* strings::find_all_st(const strings& other, int& C, int count, int array[]) const {
    bool flag = false;
    int* ptr = array;
    int idx = 0;

    for (int i = 0; i < count; i++) {
        for (int l = 0; l < other.len; l++) {
            if (this[i].Cs[l] != other.Cs[l] && this[i].len != other.len) {
                flag = false;
                break;
            }
            else {
                flag = true;
            }
        }
        if (flag) {
            ptr[idx] = i;
            idx++;
            C++;
        }
    }
    return ptr;
}

// Modification operations
void strings::remove_at(int i) {
    left_shift(Cs, len, i);
}

void strings::insert_at(int i, char ch) {
    right_shift(i);
    Cs[i] = ch;
}

void strings::insert_at_st(int i, const strings sub, int& count) {
    regrow_strings(count);
    right_shift(i);
    this[i] = sub;
}

void strings::remove_first(char ch) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            left_shift(Cs, len, i);
            break;
        }
    }
}

void strings::remove_last(char ch) {
    for (int i = len - 1; i >= 0; i--) {
        if (Cs[i] == ch) {
            left_shift(Cs, len, i);
            break;
        }
    }
}

void strings::remove_all(char ch) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            left_shift(Cs, len, i);
        }
    }
}

void strings::clear() {
    for (int i = 0; i < len; i++) {
        Cs[i] = '\0';
    }
}

strings& strings::toUpper() {
    for (int i = 0; i < len; i++) {
        if (Cs[i] >= 'a' && Cs[i] <= 'z') {
            Cs[i] = Cs[i] - 32;
        }
    }
    return *this;
}

strings& strings::toLower() {
    for (int i = 0; i < len; i++) {
        if (Cs[i] >= 'A' && Cs[i] <= 'Z') {
            Cs[i] = Cs[i] + 32;
        }
    }
    return *this;
}

// Conversion
int strings::st_oi() {
    int sum = 0;
    int n;
    bool flag = false;

    for (int i = 0; i < len; i++) {
        if (Cs[i] == '-') {
            flag = true;
            i++;
        }
        n = Cs[i] - '0';
        sum = sum * 10;
        sum = sum + n;
    }
    if (flag) {
        sum = sum * -1;
    }
    return sum;
}

// Split operations
strings* strings::split(char delim, int& count) const {
    int idx_2 = 0;
    for (int i = 0; i < len; i++) {
        if (Cs[i] == delim) {
            count++;
            for (int l = i; Cs[l] == delim; l++) {
                idx_2 = l;
            }
            i = idx_2;
        }
    }

    strings* ptr = new strings[count];
    idx_2 = 0;

    for (int l = 0; l < count; l++) {
        int a = 0;
        for (int i = idx_2; i < len; i++) {
            if (Cs[i] == delim) {
                for (int l = i; Cs[l] == delim; l++) {
                    idx_2 = l;
                }
                idx_2++;
                break;
            }
            else {
                if (ptr[l].cap == ptr[l].len) {
                    ptr[l].regrow();
                }
                ptr[l].Cs[a] = Cs[i];
                a++;
                ptr[l].len = a;
            }
        }
    }
    return ptr;
}

// Comparison operations
bool strings::is_equal(const strings& M) {
    if (this->len != M.len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (Cs[i] != M.Cs[i]) {
            return false;
        }
    }
    return true;
}

bool strings::is_less(const strings& M) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] < M.Cs[i]) {
            return true;
        }
    }
    return false;
}

bool strings::is_greater(const strings& M) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] > M.Cs[i]) {
            return true;
        }
    }
    return false;
}
bool strings::operator==(const strings& other) const {

    if (len != other.len) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (Cs[i] != other.Cs[i]) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const strings& str) {
    os << str.Cs;
    return os;
}

std::istream& operator>>(std::istream& is, strings& str) {
    char buffer[1024];
    is >> buffer;
    str = strings(buffer);
    return is;
}
// Access operators
char& strings::operator[](int i) {
    if (i < 0 || i >= len) {
        
    }
    return Cs[i];
}

const char strings::operator[](int i) const {
    if (i < 0 || i >= len) {
        char dummy = '\0';
        return dummy;
    }
    return Cs[i];
}

// Concatenation operators
strings strings::operator+(const strings& s2) {
    strings temp;
    temp.len = this->len + s2.len;
    temp.Cs = new char[temp.len];
    temp.cap = temp.len;

    for (int i = 0; i < len; i++) {
        temp.Cs[i] = Cs[i];
    }

    for (int i = 0, l = len; i < s2.len; i++, l++) {
        temp.Cs[l] = s2.Cs[i];
    }
    return temp;
}

strings operator+(const strings& s1, const strings& s2) {
    strings temp;
    temp.len = s1.len + s2.len;
    temp.Cs = new char[temp.len];
    temp.cap = temp.len;

    for (int i = 0; i < s1.len; i++) {
        temp.Cs[i] = s1.Cs[i];
    }

    for (int i = 0, l = s1.len; i < s2.len; i++, l++) {
        temp.Cs[l] = s2.Cs[i];
    }
    return temp;
}

//strings strings::operator+(const Date& s2)
//{
//    strings temp;
//    int day = s2.get_day();
//    
//    
//}


// Output
void strings::print()
{
    for (int i = 0; i < len; i++)
    {
        cout << Cs[i] << "";
    }
}
strings intToString(int num) {
    // Handle the special case of 0
    if (num == 0) {
        return "0";
    }

    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num; 
    }

    strings result;
    while (num > 0) {
        strings digit = "0" + (num % 10);
        result = digit + result;
        num /= 10; 
    }

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}

// Non-member function
int conv_int(char arr[]) {
    int sum = 0;
    int n;
    bool flag = false;

    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == '-') {
            flag = true;
            i++;
        }
        n = arr[i] - 48;
        sum = sum * 10;
        sum = sum + n;
    }
    if (flag) {
        sum = sum * -1;
    }
    return sum;
}


