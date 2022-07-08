#include <iostream>
#include <fstream>
#include <cmath>

#ifndef _Fraction_H
#define _Fraction_H
class Fraction
{
    int p;  // Numerator
    unsigned int q; // Denominator
public:
    static Fraction sc_fUnity;  // Fraction(1/1) i.e. 1
    static Fraction sc_fZero;   // Fraction(0/1) i.e. 0

    explicit Fraction(int=1, int=1);    // default constructor
    explicit Fraction(double);  // overloaded constructor
    Fraction(const Fraction&);  // copy constructor

    ~Fraction();    // destructor

    Fraction& operator=(const Fraction&);   // copy assignment operator

    Fraction operator-();   // unary - operator
    Fraction operator+() const; // unary + operator

    Fraction operator--();  // unary pre-decrement operator
    Fraction operator++();  // unary pre-increment operator

    Fraction operator--(int);   // unary post-decrement operator
    Fraction operator++(int);   // unary post-increment operator

    friend Fraction operator+(const Fraction, const Fraction);  // binary + operator
    friend Fraction operator-(const Fraction, const Fraction);  // binary - operator
    friend Fraction operator*(const Fraction, const Fraction);  // binary * operator
    friend Fraction operator/(const Fraction, const Fraction);  // binary / operator
    friend Fraction operator%(const Fraction, const Fraction);  // binary % operator

    inline bool operator==(const Fraction& f)   // relational operator for equality (inline)
    {
        return (p==f.p && q==f.q);
    }
    inline bool operator!=(const Fraction& f)   // relational operator for inequality (inline)
    {
        return (p!=f.p || q!=f.q);
    }
    inline bool operator<(const Fraction& f)    // relational operator for less-than (inline)
    {
        return (p*int(f.q) < int(q)*f.p);
    }
    inline bool operator<=(const Fraction& f)   // relational operator for less-than-equals (inline)
    {
        return (p*int(f.q) <= int(q)*f.p);
    }
    inline bool operator>(const Fraction& f)    // relational operator for greater-than (inline)
    {
        return (p*int(f.q) > int(q)*f.p);
    }
    inline bool operator>=(const Fraction& f)   // relational operator for greater-than-equals (inline)
    {
        return (p*int(f.q) >= int(q)*f.p);
    }

    Fraction operator!();   // special not operator to find inverse of fraction

    friend std::ostream& operator<<(std::ostream&, const Fraction&);    // input operator
    friend std::istream& operator>>(std::istream&, Fraction&);  // output operator

    void normalize();   // utility function to normalize the fraction to proper form
    
};

static int precision();   // utility function to return precision
static int gcd(int p, int q);   // utility function to return gcd
static int lcm(int p, int q);   // utility function to return lcm

#endif