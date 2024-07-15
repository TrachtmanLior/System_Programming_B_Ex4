// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Getter methods
    double getReal() const { return real; }

    double getImag() const { return imag; }

    // Overloaded operators for arithmetic operations
    Complex operator+(const Complex &other) const {
        return {real + other.real, imag + other.imag};
    }

    Complex operator-(const Complex &other) const {
        return {real - other.real, imag - other.imag};
    }

    Complex operator*(const Complex &other) const {
        return {real * other.real - imag * other.imag, real * other.imag + imag * other.real};
    }

    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        return abs(real) + abs(imag) < abs(other.real) + abs(other.imag);
    }

    bool operator>(const Complex& other) const {
        return abs(real) + abs(imag) > abs(other.real) + abs(other.imag);
    }

    bool operator<=(const Complex& other) const {
        return !(*this > other);
    }

    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

#endif // COMPLEX_HPP
