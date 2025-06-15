#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
using namespace std;

template <class T>
class vectors {
private:
    T* data;
    size_t len;
    size_t cap;

    void double_capacity() {
        int new_cap = cap == 0 ? 2 : cap * 2;
        T* new_ptr = new T[new_cap];
        for (int i = 0; i < len; ++i) {
            new_ptr[i] = data[i]; 
        }
        delete[] data;
        data = new_ptr;
        cap = new_cap;
    }
    friend class Iterator;

public:
  
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        int to_index(const vectors<T>& vec) const {
            return ptr - vec.data;
        }

        T& operator*() { return *ptr; }
        const T& operator*() const { return *ptr; } // Const version
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator+(int offset) const { return Iterator(ptr + offset); } // Add offset
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

   
    vectors() : len(0), cap(0), data(nullptr) {}

    vectors(const vectors& other) : len(other.len), cap(other.cap), data(new T[other.cap]) {
        for (int i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }
    }


    //vectors(const vectors& other) : len(other.len), cap(other.cap), data(new T[other.cap]) {
    //    for (int i = 0; i < len; ++i) {
    //        data[i] = std::move(other.data[i]);  // Move elements if possible
    //    }
    //}
    //// In your assignment operator:
    //vectors& operator=(vectors other) {  // Note: pass by value
    //    swap(other);
    //    return *this;
    //}

    ~vectors() {
        delete[] data;
    }

    // Operators
    vectors& operator=(const vectors& other) {
        if (this != &other) {
            T* new_ptr = new T[other.cap];
            for (int i = 0; i < other.len; ++i) {
                new_ptr[i] = other.data[i];
            }
            delete[] data;
            data = new_ptr;
            len = other.len;
            cap = other.cap;
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= len) {
            cout << "Error: Index " << index << " out of range\n";
            exit(1);
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= len) {
            cout << "Error: Index " << index << " out of range\n";
            exit(1);
        }
        return data[index];
    }

    bool operator==(const vectors& other) const {
        if (len != other.len) return false;
        for (int i = 0; i < len; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const vectors& other) const {
        return !(*this == other);
    }

    // Modifiers
    void push(const T& value) {
        if (len == cap) {
            double_capacity();
        }
        data[len++] = value;
    }

    void pop() {
        if (len > 0) {
            len--;
            if (len < cap / 4 && cap > 2) {
                reserve(cap / 2); // Shrink if too empty
            }
        }
    }

    void insert_at(int index, const T& value) {
        if (index < 0 || index > len) {
            cout << "Error: Invalid index " << index << "\n";
            exit(1);
        }
        if (len == cap) {
            double_capacity();
        }
        for (int i = len; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        len++;
    }

    void erase(int index) {
        if (index < 0 || index >= len) {
            cout << "Error: Invalid index " << index << "\n";
            exit(1);
        }
        for (int i = index; i < len - 1; i++) {
            data[i] = data[i + 1];
        }
        len--;
    }

    void erase(Iterator it) {
        int index = it.to_index(*this); // Use the conversion method
        if (index < 0 || index >= len) {
            cout << "Error: Invalid iterator position\n";
            exit(1);
        }
        for (int i = index; i < len - 1; ++i) {
            data[i] = data[i + 1];
        }
        len--;
    }

    void reserve(int new_capacity) {
        if (new_capacity <= cap) return;
        T* new_ptr = new T[new_capacity];
        for (int i = 0; i < len; ++i) {
            new_ptr[i] = data[i];
        }
        delete[] data;
        data = new_ptr;
        cap = new_capacity;
    }

    void clear() {
        len = 0;
        if (cap > 2) {
            reserve(2); // Reset to initial capacity
        }
    }

    void swap(vectors& other) {
        T* temp_data = data;
        int temp_len = len;
        int temp_cap = cap;
        data = other.data;
        len = other.len;
        cap = other.cap;
        other.data = temp_data;
        other.len = temp_len;
        other.cap = temp_cap;
    }

    void shrink_to_fit() {
        if (len < cap) {
            reserve(len ? len : 2);
        }
    }

    // Accessors
    T& at(int index) {
        if (index < 0 || index >= len) {
            cout << "Error: Index " << index << " out of range\n";
            exit(1);
        }
        return data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= len) {
            cout << "Error: Index " << index << " out of range\n";
            exit(1);
        }
        return data[index];
    }

    bool empty() const {
        return len == 0;
    }

    size_t size() const {
        return len;
    }

    size_t capacity() const {
        return cap;
    }

    T& front() {
        if (empty()) {
            cout << "Error: Vector is empty\n";
            exit(1);
        }
        return data[0];
    }

    const T& front() const {
        if (empty()) {
            cout << "Error: Vector is empty\n";
            exit(1);
        }
        return data[0];
    }

    T& back() {
        if (empty()) {
            cout << "Error: Vector is empty\n";
            exit(1);
        }
        return data[len - 1];
    }

    const T& back() const {
        if (empty()) {
            cout << "Error: Vector is empty\n";
            exit(1);
        }
        return data[len - 1];
    }

    int find(const T& value) const {
        for (int i = 0; i < len; ++i) {
            if (data[i] == value) return i;
        }
        return -1;
    }

  

    // Iterator methods
    Iterator begin() { return Iterator(data); }
    Iterator begin() const { return Iterator(data); } // Const overload
    Iterator end() { return Iterator(data + len); }
    Iterator end() const { return Iterator(data + len); } // Const overload
};

#endif // MYVECTOR_H