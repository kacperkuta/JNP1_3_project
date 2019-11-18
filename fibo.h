#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <string>
#include <vector>

class Fibo {
public:
    Fibo();
    explicit Fibo(const std::string&);
    explicit Fibo(int);
    explicit Fibo(unsigned int);
    explicit Fibo(unsigned long);
    explicit Fibo(unsigned long long);

    Fibo(const Fibo&);

    Fibo& operator=(const Fibo&);
    Fibo& operator=(size_t);

    Fibo operator+(const Fibo&);
    Fibo operator+(size_t);

    Fibo operator&(const Fibo&);
    Fibo operator&(size_t);

    Fibo operator|(const Fibo&);
    Fibo operator|(size_t);

    Fibo operator^(const Fibo&);
    Fibo operator^(size_t);

    Fibo operator<<(size_t);

    Fibo& operator+=(const Fibo&);
    Fibo& operator+=(size_t);

    Fibo& operator&=(const Fibo&);
    Fibo& operator&=(size_t);

    Fibo& operator|=(const Fibo&);
    Fibo& operator|=(size_t);

    Fibo& operator^=(const Fibo&);
    Fibo& operator^=(size_t);

    Fibo& operator<<=(int);

    bool operator>(const Fibo&);
    bool operator>(size_t);

    bool operator>=(const Fibo&);
    bool operator>=(size_t);

    bool operator==(const Fibo&);
    bool operator==(size_t);

    bool operator<=(const Fibo&);
    bool operator<=(size_t);

    bool operator<(const Fibo&);
    bool operator<(size_t);

    bool operator!=(const Fibo&);
    bool operator!=(size_t);

    void printFibo();

    int length();

private:

    void convertIntToFibo(std::vector<bool>& normalized, size_t number);

    size_t convertFiboToInt(const std::string& s);

    std::vector<bool> normalized;

    unsigned int normalized_length;

};
const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
