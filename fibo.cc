#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

#include "fibo.h"

//constructors, destructor
Fibo::Fibo() : Fibo(0) {};

Fibo::Fibo(const std::string& s) {
    size_t length = s.length() + 1;

    normalized = std::vector<bool>(length);
    normalized_length = length;

    for (size_t i = 1; i < length; i++) {
        //assert(s[i] == '1' || s[i] == '0');
        normalized[i] = s[i - 1] == '1';
    }

    normalizeBackwards(normalized, length);
    normalizeForwards(normalized, length);
}

Fibo::Fibo(int number) {
    assert(number >= 0);
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

Fibo& Fibo::operator<<=(unsigned long long n) {
    normalized_length += n;
    normalized.resize(normalized_length);
    for (size_t i = normalized_length - n; i < normalized_length; i++) {
        normalized[i] = false;
    }
    return *this;
}

Fibo operator<<(Fibo f, unsigned long long n) {
    return f <<= n;
}

Fibo& Fibo::operator|=(const Fibo& f) {
    if (f.normalized_length >= normalized_length) {

        size_t diff = f.normalized_length - normalized_length;
        normalized.resize(f.normalized_length + 1);
        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + diff + 1, normalized.end());
        this->printFibo();
        std::cout << std::endl;
        for (int i = 0; i < f.normalized_length; i++) {
            normalized[i + 1] = normalized[i + 1] || f.normalized[i];
        }
        normalized_length += diff + 1;
    } else {

        size_t diff = normalized_length - f.normalized_length;
        normalized.resize(normalized_length + 1);

        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + 1, normalized.end());

        for (int i = 0; i < f.normalized_length; i++) {
            normalized[i + 1 + diff] = normalized[i + 1 + diff] ||
                    f.normalized[i];
        }
        normalized_length++;
    }
    normalizeBackwards(normalized, normalized_length);
    normalizeForwards(normalized, normalized_length);
    return *this;
}
Fibo& Fibo::operator|=(unsigned long long num) {
    return *this |= Fibo(num);
}

Fibo operator|(unsigned long long num, const Fibo& f) {
    return Fibo(num) |= f;
}
Fibo Fibo::operator|(const Fibo& f) {
    return Fibo(*this) |= f;
}
Fibo Fibo::operator|(unsigned long long num) {
    return Fibo(num) |= *this;
}

void Fibo::convertIntToFibo(std::vector<bool>& normalized,
        unsigned long long number) {
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
