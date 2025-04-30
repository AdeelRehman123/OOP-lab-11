#include <iostream>
#include <vector>

// Custom exception class without inheriting from std::exception
class StackUnderflowException {
public:
    const char* what() const {
        return "StackUnderflowException: Stack is empty.";
    }
};

template<typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (elements.empty())
            throw StackUnderflowException();
        elements.pop_back();
    }

    T top() {
        if (elements.empty())
            throw StackUnderflowException();
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }
};

int main() {
    Stack<int> s;

    try {
        s.push(10);
        s.push(20);
        std::cout << "Top: " << s.top() << std::endl;
        s.pop();
        s.pop();
        s.pop();  // This should trigger exception
    } catch (const StackUnderflowException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
