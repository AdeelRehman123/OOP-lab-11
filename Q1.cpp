#include <iostream>
#include <typeinfo>

// Custom exception
class BadTypeException {
public:
    const char* what() const {
        return "BadTypeException: Requested type does not match stored type.";
    }
};

// Type erasure via base and derived classes
class BaseHolder {
public:
    virtual ~BaseHolder() {}
};

template<typename T>
class Holder : public BaseHolder {
public:
    T value;
    Holder(const T& v) : value(v) {}
};

class TypeSafeContainer {
private:
    BaseHolder* data;

public:
    TypeSafeContainer() : data(nullptr) {}
    ~TypeSafeContainer() {
        delete data;
    }

    template<typename T>
    void store(const T& value) {
        delete data; // Clean up old data
        data = new Holder<T>(value);
    }

    template<typename T>
    T get() {
        Holder<T>* holder = dynamic_cast<Holder<T>*>(data);
        if (!holder)
            throw BadTypeException();
        return holder->value;
    }
};

int main() {
    TypeSafeContainer container;

    container.store<int>(42);

    try {
        std::cout << "Stored int: " << container.get<int>() << std::endl;
        std::cout << "Trying to get string..." << std::endl;
        std::cout << container.get<std::string>() << std::endl;
    } catch (const BadTypeException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
