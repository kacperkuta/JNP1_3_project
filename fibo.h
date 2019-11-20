#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <string>
#include <vector>

class Fibo {
public:
    Fibo();

    explicit Fibo(const std::string&);
    explicit Fibo(const char*);

    Fibo(int);
    Fibo(long);
    Fibo(long long);
    Fibo(unsigned int);
    Fibo(unsigned long);
    Fibo(unsigned long long);

    Fibo(const Fibo&);

    template<class T>
    explicit Fibo(T) = delete;

    Fibo& operator=(const Fibo&);

    friend Fibo operator+(long long, const Fibo&);
    Fibo operator+(const Fibo&);

    friend Fibo operator&(long long, const Fibo&);
    Fibo operator&(const Fibo&);

    friend Fibo operator^(long long, const Fibo&);
    Fibo operator^(const Fibo&);

    Fibo& operator+=(const Fibo&);

    Fibo& operator&=(const Fibo&);

    Fibo& operator^=(const Fibo&);

    friend Fibo operator|(long long, const Fibo&);
    Fibo operator|(const Fibo&);

    Fibo& operator|=(const Fibo&);

    friend Fibo operator<<(Fibo, long long);

    Fibo& operator<<=(long long);

    friend bool operator>(long long, const Fibo&);
    bool operator>(const Fibo&);

    friend bool operator>=(long long, const Fibo&);
    bool operator>=(const Fibo&);

    friend bool operator==(const Fibo&, const Fibo&);

    friend bool operator<=(long long, const Fibo&);
    bool operator<=(const Fibo&);

    friend bool operator<(long long, const Fibo&);
    bool operator<(const Fibo&);

    friend bool operator!=(long long, const Fibo&);
    bool operator!=(const Fibo&);

    void printFibo();

    size_t length();

private:

    void convertIntToFibo(std::vector<bool>& normalized,
            long long number);

    void normalizeForwards(std::vector<bool>& v, size_t length);

    void normalizeBackwards(std::vector<bool>& v, size_t length);

    void removeLeadingZeros();

    std::vector<bool> normalized;

    size_t normalized_length;

};
const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
