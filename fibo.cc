#include <iostream>
#include <vector>

#include "fibo.h"

Fibo::Fibo() : Fibo(0) {};

Fibo::Fibo(const std::string& s) : Fibo(convertFiboToInt(s)) {}

Fibo::Fibo(int number) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, (unsigned)number);
}

Fibo::Fibo(unsigned int number) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, number);
}

Fibo::Fibo(unsigned long number) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, number);
}

Fibo::Fibo(unsigned long long number) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, number);
}

Fibo::Fibo(const Fibo& other) {
    normalized_length = other.normalized_length;
    normalized = std::vector<bool>(normalized_length);
    for (int i = 0; i < normalized_length; i++) {
        normalized[i] = other.normalized[i];
    }
}

const Fibo Zero() {
    return Fibo(0);
}

const Fibo One() {
    return Fibo(1);
}

void Fibo::convertIntToFibo(std::vector<bool>& normalized, size_t number) {
    size_t f1 = 1;
    size_t f2 = 1;
    unsigned int i = 1;

    while (f2 + f1 <= number) {
        f2 = f1 + f2;
        f1 = f2 - f1;
        i++;
    }
    normalized.resize(i);
    normalized_length = i;

    for (auto itr = normalized.begin(); itr != normalized.end(); itr++) {
        if (number >= f2) {
            *itr = true;
            number -= f2;
        }
        f1 = f2 - f1;
        f2 = f2 - f1;
    }
}

size_t Fibo::convertFiboToInt(const std::string& s) {
    size_t f1 = 1;
    size_t f2 = 2;
    size_t result = 0;

    for (auto itr = s.rbegin(); itr != s.rend(); itr++) {
        if (*itr == '1') {
            result += f1;
        }
        f2 = f2 + f1;
        f1 = f2 - f1;
    }
    return result;
}

int Fibo::length() {
    return normalized_length;
}

void Fibo::printFibo() {
    for (bool b : normalized)
        std::cout << b;
};
