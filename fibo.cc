#include <iostream>
#include <vector>

#include "fibo.h"

//constructors, destructor
Fibo::Fibo() : Fibo(0) {};

Fibo::Fibo(const std::string& s) {
    size_t length = s.length() + 1;

    normalized = std::vector<bool>(length);

    for (size_t i = 1; i < length; i++) {
        normalized[i] = s[i - 1] == '1';
    }

    normalizeBackwards(normalized, length);
    normalizeForwards(normalized, length);
}

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

//functions Zero() and One()
const Fibo Zero() {
    return Fibo(0);
}

const Fibo One() {
    return Fibo(1);
}

//operations
bool Fibo::operator==(const Fibo& other) {
    if (other.normalized_length != normalized_length)
        return false;

    for (size_t i = 0; i < normalized_length; i++) {
        if (other.normalized[i] != normalized[i])
            return false;
    }
    return true;
}
bool Fibo::operator==(long long number) {
    if (number < 0)
        return false;
    return *this == Fibo((unsigned long long)number);
}
bool operator==(long long num, const Fibo& other) {
    if (num < 0)
        return false;
    return Fibo((unsigned long long)num) == other;
}

bool Fibo::operator>(const Fibo& other) {
    if (other.normalized_length != normalized_length)
        return normalized_length > other.normalized_length;

    for (int i = 0; i < normalized_length; i++) {
        if (other.normalized[i] > normalized[i])
            return false;
        else if (other.normalized[i] < normalized[i])
            return true;
    }
    return false;
}
bool Fibo::operator>(long long num) {
    if (num < 0)
        return true;
    return *this > Fibo((unsigned long long)num);
}
bool operator>(long long num, const Fibo& other) {
    if (num < 0)
        return false;
    return Fibo((unsigned long long)num) > other;
}

bool Fibo::operator>=(const Fibo& other) {
    //czy lepiej skopiować kod czy mniej optymalnie kprzystajac z > i ==?
    if (other.normalized_length != normalized_length)
        return normalized_length > other.normalized_length;

    for (int i = 0; i < normalized_length; i++) {
        if (other.normalized[i] > normalized[i])
            return false;
        else if (other.normalized[i] < normalized[i])
            return true;
    }
    return true;
}
bool Fibo::operator>=(long long num) {
    if (num < 0)
        return true;
    return *this >= Fibo((unsigned long long)num);
}
bool operator>=(long long num, const Fibo& other) {
    if (num < 0)
        return false;
    return Fibo((unsigned long long)num) >= other;
}

bool Fibo::operator<(const Fibo& other) {
    return !(*this >= other);
}
bool Fibo::operator<(long long num) {
    if (num <= 0)
        return false;
    return *this < Fibo((unsigned long long)num);
}
bool operator<(long long num, const Fibo& other) {
    if (num < 0)
        return true;
    return Fibo((unsigned long long)num) < other;
}

bool Fibo::operator<=(const Fibo& other) {
    return !(*this > other);
}
bool Fibo::operator<=(long long num) {
    if (num < 0)
        return false;
    return *this <= Fibo((unsigned long long)num);
}
bool operator<=(long long num, const Fibo& other) {
    if (num <= 0)
        return true;
    return Fibo((unsigned long long)num) <= other;
}

bool Fibo::operator!=(const Fibo& other) {
    return !(*this == other);
}
bool Fibo::operator!=(long long num) {
    if (num < 0)
        return true;
    return *this != Fibo((unsigned long long)num);
}
bool operator!=(long long num, const Fibo& other) {
    if (num < 0)
        return true;
    return Fibo((unsigned long long)num) != other;
}

void Fibo::convertIntToFibo(std::vector<bool>& normalized, long long number) {
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

void Fibo::normalizeForwards(std::vector<bool>& v, size_t length) {
    for (size_t i = 0; i < length - 2; i++) {
        if (v[i + 1] && v[i + 2]) {
            v[i] = true;
            v[i + 1] = false;
            v[i + 2] = false;
        }
    }
}

void Fibo::normalizeBackwards(std::vector<bool>& v, size_t length) {
    for (size_t i = length - 1; i >= 2; i--) {
        if (v[i - 1] && v[i] && !v[i - 2]) {
            v[i - 2] = true;
            v[i - 1] = false;
            v[i] = false;
        }
    }
}

size_t Fibo::length() {
    return normalized_length;
}

void Fibo::printFibo() {
    for (bool b : normalized)
        std::cout << b;
};
