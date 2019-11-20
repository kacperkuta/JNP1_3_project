#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <string>
#include <vector>

class Fibo {
public:
    Fibo();

    explicit Fibo(const std::string&);
    explicit Fibo(const char*);
    explicit Fibo(int);
    explicit Fibo(unsigned int);
    explicit Fibo(unsigned long);
    explicit Fibo(unsigned long long);

    Fibo(const Fibo&);
    //~Fibo() = delete;

    template<class T>
    explicit Fibo(T) = delete;

    Fibo& operator=(const Fibo&);
    Fibo& operator=(unsigned long long);

    friend Fibo operator+(long long, const Fibo&);
    Fibo operator+(const Fibo&);
    Fibo operator+(unsigned long long);

    friend Fibo operator&(long long, const Fibo&);
    Fibo operator&(const Fibo&);
    Fibo operator&(unsigned long long);

    friend Fibo operator^(long long, const Fibo&);
    Fibo operator^(const Fibo&);
    Fibo operator^(unsigned long long);

    Fibo& operator+=(const Fibo&);
    Fibo& operator+=(unsigned long long);

    Fibo& operator&=(unsigned long long);
    Fibo& operator&=(const Fibo&);

    Fibo& operator^=(const Fibo&);
    Fibo& operator^=(unsigned long long);

    friend Fibo operator|(unsigned long long, const Fibo&);
    Fibo operator|(const Fibo&);
    Fibo operator|(unsigned long long);

    Fibo& operator|=(const Fibo&);
    Fibo& operator|=(unsigned long long);

    friend Fibo operator<<(Fibo, unsigned long long);

    Fibo& operator<<=(unsigned long long);

    friend bool operator>(long long, const Fibo&);
    bool operator>(const Fibo&);
    bool operator>(long long);

    friend bool operator>=(long long, const Fibo&);
    bool operator>=(const Fibo&);
    bool operator>=(long long);

    friend bool operator==(long long, const Fibo&);
    bool operator==(const Fibo&);
    bool operator==(long long);

    friend bool operator<=(long long, const Fibo&);
    bool operator<=(const Fibo&);
    bool operator<=(long long);

    friend bool operator<(long long, const Fibo&);
    bool operator<(const Fibo&);
    bool operator<(long long);

    friend bool operator!=(long long, const Fibo&);
    bool operator!=(const Fibo&);
    bool operator!=(long long);

    void printFibo();

    size_t length();

private:

    void convertIntToFibo(std::vector<bool>& normalized,
            unsigned long long number);

    void normalizeForwards(std::vector<bool>& v, size_t length);

    void normalizeBackwards(std::vector<bool>& v, size_t length);

    void removeLeadingZeros();

    std::vector<bool> normalized;

    size_t normalized_length;

};
const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
