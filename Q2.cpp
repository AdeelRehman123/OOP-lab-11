#include <iostream>
#include <vector>

class DimensionMismatchException {
public:
    const char* what() const {
        return "DimensionMismatchException: Matrix dimensions do not match.";
    }
};

class IndexOutOfBoundsException {
public:
    const char* what() const {
        return "IndexOutOfBoundsException: Invalid index accessed in Matrix.";
    }
};

template<typename T>
class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<T>> data;

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<T>(c)) {}

    T& at(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols)
            throw IndexOutOfBoundsException();
        return data[r][c];
    }

    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols)
            throw DimensionMismatchException();

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.at(i, j) = data[i][j] + other.data[i][j];

        return result;
    }

    Matrix operator*(const Matrix& other) {
        if (cols != other.rows)
            throw DimensionMismatchException();

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.at(i, j) += data[i][k] * other.data[k][j];

        return result;
    }

    void display() const {
        for (const auto& row : data) {
            for (const auto& e : row)
                std::cout << e << " ";
            std::cout << "\n";
        }
    }
};

int main() {
    Matrix<int> m1(2, 2), m2(2, 2);

    m1.at(0, 0) = 1; m1.at(0, 1) = 2;
    m1.at(1, 0) = 3; m1.at(1, 1) = 4;

    m2.at(0, 0) = 5; m2.at(0, 1) = 6;
    m2.at(1, 0) = 7; m2.at(1, 1) = 8;

    try {
        Matrix<int> sum = m1 + m2;
        sum.display();
    } catch (const DimensionMismatchException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
