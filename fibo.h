// Fibo class by Mateusz Błajda and Kacper Kuta.

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

    Fibo& operator+=(const Fibo&);

    friend Fibo operator+(const Fibo&, const Fibo&);

    Fibo& operator&=(const Fibo&);

    friend Fibo operator&(const Fibo&, const Fibo&);

    Fibo& operator^=(const Fibo&);

    friend Fibo operator^(const Fibo&, const Fibo&);

    Fibo& operator|=(const Fibo&);

    friend Fibo operator|(const Fibo&, const Fibo&);

    Fibo& operator<<=(long long);

    friend Fibo operator<<(Fibo, long long);


    friend bool operator>(const Fibo&, const Fibo&);

    friend bool operator>=(const Fibo&, const Fibo&);

    friend bool operator==(const Fibo&, const Fibo&);

    friend bool operator<=(const Fibo&, const Fibo&);

    friend bool operator<(const Fibo&, const Fibo&);

    friend bool operator!=(const Fibo&, const Fibo&);


    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Fibo& f);

    size_t length() const;

private:

    void convertStringToFibo(const std::string&);

    void convertIntToFibo(std::vector<bool>& normalized, long long number);

    void removeLeadingZeros();

    void addZeros(size_t);

    void push(size_t pos);

    void checkPush(size_t pos);

    void normalize();

    void addOne(size_t pos);

    void add(const Fibo&);

    std::vector<bool> normalized;

    size_t normalized_length;

};
const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
