#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

#include "fibo.h"

//constructors
Fibo::Fibo() : Fibo(0) {};

Fibo::Fibo(const std::string& s) {
    assert(!s.empty()); //empty string is not valid
    assert(s[0] == '1');
    convertStringToFibo(s);
};

Fibo::Fibo(const char* ss) {
    assert(ss != nullptr);
    assert(ss[0] != '\0'); //empty string is not valid
    assert(ss[0] == '1');
    convertStringToFibo(std::string(ss));
};

Fibo::Fibo(int number) {
    assert(number >= 0);
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, (unsigned)number);
}

Fibo::Fibo(long num) {
    assert(num >= 0);
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, num);
}

Fibo::Fibo(long long num) {
    assert(num >= 0);
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, num);
}

Fibo::Fibo(unsigned int num) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, num);
}

Fibo::Fibo(unsigned long num) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, (long long)num);
}

Fibo::Fibo(unsigned long long num) {
    normalized = std::vector<bool>();
    convertIntToFibo(normalized, num);
}

Fibo::Fibo(const Fibo& other) {
    normalized_length = other.normalized_length;
    normalized = std::vector<bool>(normalized_length);
    for (size_t i = 0; i < normalized_length; i++) {
        normalized[i] = other.normalized[i];
    }
}

//functions Zero(), One(), Fibo::length()
const Fibo Zero() {
    return Fibo(0);
}

const Fibo One() {
    return Fibo(1);
}

size_t Fibo::length() const {
    return normalized_length;
}

//operations

Fibo& Fibo::operator=(const Fibo& f) {
    normalized_length = f.normalized_length;
    normalized.resize(normalized_length);
    std::copy(f.normalized.begin(), f.normalized.end(), normalized.begin());
    return *this;
}

bool operator==(const Fibo& me, const Fibo& other) {

    if (other.normalized_length != me.normalized_length) {
        return false;
    }

    for (size_t i = 0; i < me.normalized_length; i++) {
        if (other.normalized[i] != me.normalized[i])
            return false;
    }
    return true;
}

Fibo& Fibo::operator+=(const Fibo& other) {
    add(other);
    return *this;
}

Fibo operator+(const Fibo& first, const Fibo& second) {
    return Fibo(first) += second;
}

Fibo& Fibo::operator<<=(long long n) {
    assert(n >= 0);

    normalized_length += n;
    normalized.resize(normalized_length);

    return *this;
}

Fibo operator<<(Fibo f, long long n) {
    return f <<= n;
}

Fibo& Fibo::operator|=(const Fibo& f) {
    if (f.normalized_length >= normalized_length) {

        size_t diff = f.normalized_length - normalized_length;
        normalized.resize(f.normalized_length + 1);
        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + diff + 1, normalized.end());
        for (size_t i = 0; i < f.normalized_length; i++) {
            normalized[i + 1] = normalized[i + 1] || f.normalized[i];
        }
        normalized_length += diff + 1;
    } else {

        size_t diff = normalized_length - f.normalized_length;
        normalized.resize(normalized_length + 1);

        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + 1, normalized.end());

        for (size_t i = 0; i < f.normalized_length; i++) {
            normalized[i + 1 + diff] = normalized[i + 1 + diff] ||
                    f.normalized[i];
        }
        normalized_length++;
    }
    normalize();
    return *this;
}

Fibo operator|(const Fibo& me, const Fibo& other) {
    return Fibo(me) |= other;

}

Fibo& Fibo::operator&=(const Fibo& f) {
    if (f.normalized_length >= normalized_length) {

        size_t diff = f.normalized_length - normalized_length;

        for (size_t i = 0; i < f.normalized_length; i++) {
            normalized[i] = normalized[i] && f.normalized[i + diff];
        }
    } else {
        size_t diff = normalized_length - f.normalized_length;

        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin(), normalized.end() - diff);

        normalized.resize(f.normalized_length);
        normalized_length = f.normalized_length;

        for (size_t i = 0; i < normalized_length; i++) {
            normalized[i] = normalized[i] && f.normalized[i];
        }
    }
    removeLeadingZeros();
    return *this;
}

Fibo operator&(const Fibo& me, const Fibo& other) {
    return Fibo(me) &= other;
}

Fibo& Fibo::operator^=(const Fibo& f) {
    if (f.normalized_length >= normalized_length) {

        size_t diff = f.normalized_length - normalized_length;
        normalized.resize(f.normalized_length + 1);
        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + diff + 1, normalized.end());
        for (size_t i = 0; i < f.normalized_length; i++) {
            normalized[i + 1] = (normalized[i + 1] + f.normalized[i]) % 2;
        }
        normalized_length += diff + 1;
    } else {

        size_t diff = normalized_length - f.normalized_length;
        normalized.resize(normalized_length + 1);

        std::reverse(normalized.begin(), normalized.end());
        std::reverse(normalized.begin() + 1, normalized.end());

        for (size_t i = 0; i < f.normalized_length; i++) {
            normalized[i + 1 + diff] = (normalized[i + 1 + diff] +
                                       f.normalized[i]) % 2;
        }
        normalized_length++;
    }
    normalize();
    return *this;
}

Fibo operator^(const Fibo& me, const Fibo& other) {
    return Fibo(me) ^= other;

}


bool operator>(const Fibo& me, const Fibo& other) {
    if (other.normalized_length != me.normalized_length)
        return me.normalized_length > other.normalized_length;

    for (size_t i = 0; i < me.normalized_length; i++) {
        if (other.normalized[i] > me.normalized[i])
            return false;
        else if (other.normalized[i] < me.normalized[i])
            return true;
    }
    return false;
}

bool operator>=(const Fibo& me, const Fibo& other) {
    if (other.normalized_length != me.normalized_length)
        return me.normalized_length > other.normalized_length;

    for (size_t i = 0; i < me.normalized_length; i++) {
        if (other.normalized[i] > me.normalized[i])
            return false;
        else if (other.normalized[i] < me.normalized[i])
            return true;
    }
    return true;
}

bool operator<(const Fibo& me, const Fibo& other) {
    return !(me >= other);
}

bool operator<=(const Fibo& me, const Fibo& other) {
    return !(me > other);
}

bool operator!=(const Fibo& me, const Fibo& other) {
    return !(me == other);
}

//private functions
void Fibo::convertIntToFibo(std::vector<bool>& normalized,
        long long number) {
    long long f1 = 1;
    long long f2 = 1;
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

void Fibo::convertStringToFibo(const std::string& s) {
    size_t length = s.length() + 1;

    normalized = std::vector<bool>(length);
    normalized_length = length;

    for (size_t i = 1; i < length; i++) {
        assert(s[i - 1] == '1' || s[i - 1] == '0');
        normalized[i] = s[i - 1] == '1';
    }

    normalize();
}

/*
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
*/
void Fibo::removeLeadingZeros() {
    size_t count = 0;
    size_t i = 0;

    while (i < normalized_length && normalized[i] == false) {
        count++;
        i++;
    }
    if (count == 0)
        return;
    std::reverse(normalized.begin(), normalized.end());
    std::reverse(normalized.begin(), normalized.end() - count);

    size_t new_length = normalized_length - count;
    new_length = new_length > 0 ? new_length : 1;

    normalized.resize(new_length);
    normalized_length = new_length;
}

void Fibo::push(size_t pos) {
    if(normalized[pos - 1]) {
        normalized[pos-1] = false;
        push(pos-2);
    }
    else{
        normalized[pos] = true;
    }
}

void Fibo::checkPush(size_t pos) {
    if(pos > 1){
        if(normalized[pos] && normalized[pos - 1]){
            normalized[pos] = false;
            normalized[pos - 1] = false;
            push(pos - 2);
        }
    }
    if(pos < normalized_length - 1 ){
        if(normalized[pos + 1] && normalized[pos]){
            normalized[pos + 1] = false;
            normalized[pos] = false;
            push(pos - 1);
        }
    }
}

void Fibo::normalize() {
    addZeros(2);
    for(size_t i = 0; i < normalized_length - 1; i++){
        if(normalized[i] && normalized[i+1]){
            normalized[i] = false;
            normalized[i+1] = false;
            push(i-1);
        }
    }
    removeLeadingZeros();
}

void Fibo::addZeros(size_t n) {
    for(size_t i = 0; i < n; i++){
        normalized.push_back(false);
    }
    std::rotate(normalized.rbegin(), normalized.rbegin() + n, normalized.rend());
    normalized_length += n;
}

void Fibo::addOne(size_t pos) {
    while(normalized[pos])
    {
        normalized[pos] = false;
        if(pos == normalized_length - 2){
            normalized[normalized_length - 1] = true;
            normalized[normalized_length - 3] = true;
            checkPush(normalized_length - 3);
        }
        if(pos > normalized_length - 2){
            normalized[normalized_length - 2] = true;
            checkPush(normalized_length - 2);
        }
        if(pos > 0) {
            normalized[pos - 1] = true;
            checkPush(pos - 1);
        }
        pos += 2;
    }
    normalized[pos] = true;
    checkPush(pos);
}

void Fibo::add(const Fibo &b) {
    size_t aSize = normalized_length;
    size_t bSize = b.length();
    size_t diff = (aSize < bSize) ? bSize - aSize : 0;
    diff += 4;
    addZeros(diff);
    aSize += diff;

    for(size_t i = 0; i < bSize; i++) {
        if(b.normalized[i]){
            size_t pos = i + (aSize - bSize);
            addOne(pos);
        }
    }
    normalized_length = aSize;
    removeLeadingZeros();
}

std::string Fibo::printFibo() const {
    std::string s;
    for (bool b : normalized)
        s += b ? "1" : "0";
    return s;
};
