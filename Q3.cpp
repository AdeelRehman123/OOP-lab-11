#include <iostream>

class ArrayIndexOutOfBounds {
public:
    const char* what() const {
        return "ArrayIndexOutOfBounds: Invalid array index accessed.";
    }
};

template<typename T>
class SafeArray {
private:
    T* arr;
    int size;

public:
    SafeArray(int s) : size(s) {
        arr = new T[size];
    }

    ~SafeArray() {
        delete[] arr;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw ArrayIndexOutOfBounds();
        return arr[index];
    }
};

int main() {
    SafeArray<int> arr(5);

    try {
        arr[2] = 100;
        std::cout << "arr[2]: " << arr[2] << std::endl;
        std::cout << "arr[5]: " << arr[5] << std::endl;
    } catch (const ArrayIndexOutOfBounds& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
