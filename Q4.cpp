#include <iostream>

template<typename T>
class Base {
protected:
    T a, b;

public:
    Base(T x, T y) : a(x), b(y) {}
    T multiply() { return a * b; }
};

template<typename T>
class Derived : public Base<T> {
private:
    T c, d;

public:
    Derived(T x, T y, T p, T q) : Base<T>(x, y), c(p), d(q) {}

    T multiplyDerived() { return c * d; }
};

int main() {
    Derived<int> obj(2, 3, 4, 5);
    std::cout << "Base Multiply: " << obj.multiply() << std::endl;
    std::cout << "Derived Multiply: " << obj.multiplyDerived() << std::endl;

    return 0;
}
