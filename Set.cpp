#include <iostream>
#include <cstring>
using namespace std;

class SetException {
private:
    char message[100];
public:
    SetException(const char* msg) {
        strncpy(message, msg, 99);
        message[99] = '\0';
    }
    const char* what() const {
        return message;
    }
};

template <typename T>
class SET {
private:
    int n;
    int capacity;
    T* elements;

    void resize(int new_capacity) {
        if (new_capacity < n) {
            throw SetException("Kich thuoc moi nho hon so phan tu hien tai");
        }
        
        T* new_elements = new T[new_capacity];
        if (!new_elements) {
            throw SetException("Khong the cap phat bo nho khi resize");
        }
        
        for (int i = 0; i < n; i++) {
            new_elements[i] = elements[i];
        }
        
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }

public:
    SET() : n(0), capacity(1) {
        elements = new T[capacity];
        if (!elements) {
            throw SetException("Khong the cap phat bo nho ban dau");
        }
    }
    
    SET(int size) {
        if (size < 0) {
            throw SetException("Kich thuoc tap hop khong the am");
        }
        
        elements = new T[size];
        if (!elements) {
            throw SetException("Khong the cap phat bo nho");
        }
        n = size;
        capacity = size;
    }
    
    SET(const SET& other) : n(other.n), capacity(other.capacity) {
        elements = new T[capacity];
        if (!elements) {
            throw SetException("Khong the cap phat bo nho cho copy constructor");
        }
        for (int i = 0; i < n; i++) {
            elements[i] = other.elements[i];
        }
    }
    
    ~SET() {
        delete[] elements;
    }
    
    SET& operator=(const SET& other) {
        if (this != &other) {
            T* new_elements = new T[other.capacity];
            if (!new_elements) {
                throw SetException("Khong the cap phat bo nho cho operator=");
            }
            
            for (int i = 0; i < other.n; i++) {
                new_elements[i] = other.elements[i];
            }
            
            delete[] elements;
            elements = new_elements;
            n = other.n;
            capacity = other.capacity;
        }
        return *this;
    }
    
    SET operator+(const T& element) const {
        if (this->contains(element)) {
            return *this;
        }
        
        SET result = *this;
        
        if (result.n >= result.capacity) {
            result.resize(result.capacity * 2);
        }
        
        result.elements[result.n] = element;
        result.n++;
        return result;
    }
    
    SET operator-(const T& element) const {
        if (!this->contains(element)) {
            return *this;
        }
        
        SET result;
        for (int i = 0; i < n; i++) {
            if (elements[i] != element) {
                result = result + elements[i];
            }
        }
        return result;
    }
    
    SET operator+(const SET& other) const {
        SET result = *this;
        for (int i = 0; i < other.n; i++) {
            if (!result.contains(other.elements[i])) {
                result = result + other.elements[i];
            }
        }
        return result;
    }
    
    SET operator-(const SET& other) const {
        SET result = *this;
        for (int i = 0; i < other.n; i++) {
            if (result.contains(other.elements[i])) {
                result = result - other.elements[i];
            }
        }
        return result;
    }
    
    SET operator*(const SET& other) const {
        SET result;
        for (int i = 0; i < n; i++) {
            if (other.contains(elements[i])) {
                result = result + elements[i];
            }
        }
        return result;
    }
    
    bool operator()(const T& element) const {
        return contains(element);
    }
    
    bool contains(const T& element) const {
        for (int i = 0; i < n; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= n) {
            char buffer[100];
            sprintf(buffer, "Chi so %d nam ngoai pham vi hop le [0, %d]", index, n-1);
            throw SetException(buffer);
        }
        return elements[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= n) {
            char buffer[100];
            sprintf(buffer, "Chi so %d nam ngoai pham vi hop le [0, %d]", index, n-1);
            throw SetException(buffer);
        }
        return elements[index];
    }
    
    friend ostream& operator<<(ostream& os, const SET<T>& set) {
        os << "{";
        for (int i = 0; i < set.n; i++) {
            os << set.elements[i];
            if (i < set.n - 1) {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }
    
    int size() const {
        return n;
    }
    
    bool empty() const {
        return n == 0;
    }
    
    int get_capacity() const {
        return capacity;
    }
};

void testBasicOperations() {
    cout << "=== TEST CAC PHEP TOAN CO BAN ===" << endl;
    
    SET<int> A;
    cout << "Tao tap hop A rong: " << A << endl;
    
    A = A + 1;
    A = A + 2;
    A = A + 3;
    cout << "A sau khi them 1, 2, 3: " << A << endl;
    
    A = A - 2;
    cout << "A sau khi xoa 2: " << A << endl;
}

void testSetOperations() {
    cout << "\n=== TEST CAC PHEP TOAN TAP HOP ===" << endl;
    
    SET<int> A;
    A = A + 1;
    A = A + 2;
    A = A + 3;
    cout << "A = " << A << endl;
    
    SET<int> B;
    B = B + 3;
    B = B + 4;
    B = B + 5;
    cout << "B = " << B << endl;
    
    SET<int> C = A + B;
    cout << "A + B (hop) = " << C << endl;
    
    SET<int> D = A - B;
    cout << "A - B (hieu) = " << D << endl;
    
    SET<int> E = A * B;
    cout << "A * B (giao) = " << E << endl;
}

void testErrorHandling() {
    cout << "\n=== TEST XU LY NGOAI LE ===" << endl;
    
    try {
        SET<int> A;
        A = A + 1;
        A = A + 2;
        
        cout << "A = " << A << endl;
        cout << "A[0] = " << A[0] << endl;
        cout << "A[1] = " << A[1] << endl;
        
        cout << "Thu truy xuat A[5]..." << endl;
        cout << A[5] << endl;
    }
    catch (const SetException& e) {
        cout << "Bat duoc ngoai le: " << e.what() << endl;
    }
    
    try {
        cout << "Thu tao tap hop voi kich thuoc am..." << endl;
        SET<int> B(-5);
    }
    catch (const SetException& e) {
        cout << "Bat duoc ngoai le: " << e.what() << endl;
    }
}

void testMembership() {
    cout << "\n=== TEST KIEM TRA PHAN TU ===" << endl;
    
    SET<int> A;
    A = A + 1;
    A = A + 3;
    A = A + 5;
    
    cout << "A = " << A << endl;
    cout << "1 co thuoc A: " << (A(1) ? "true" : "false") << endl;
    cout << "2 co thuoc A: " << (A(2) ? "true" : "false") << endl;
    cout << "5 co thuoc A: " << (A(5) ? "true" : "false") << endl;
}

int main() {
    try {
        testBasicOperations();
        testSetOperations();
        testErrorHandling();
        testMembership();
        
        cout << "\n TEST VOI KIEU DU LIEU KHAC " << endl;
        SET<string> S;
        S = S + "Hello";
        S = S + "World";
        S = S + "C++";
        cout << "Tap hop string: " << S << endl;
        
    }
    catch (const SetException& e) {
        cout << "Loi trong ham main: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}