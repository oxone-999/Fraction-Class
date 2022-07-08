/****************************************
*    Software Engineering Assignment    *
*    Assignment 2 Fractions             *
*    Name:       Mayank Kumar           *
*    Roll No.:   19CS30029              *
*****************************************/

#include "Fraction.hxx"

static const int prcsn = 100000;	// constant precision value

// returns precision value
static int precision()
{
	return prcsn;
}

// utility function to calculate gcd of p and q
static int gcd(int p, int q)
{
	p = abs(p);
	q = abs(q);
	if(p>=q)
    {
        if(q==0)
            return p;
        return gcd(q, p%q);
    }
    else
	{
        if(p==0)
            return q;
        return gcd(p, q%p);
    }
}

// utility function to calculate lcm of p and q
static int lcm(int p, int q)
{
	return ((p/gcd(p, q))*q);
}

// utility function to normalize the function to proper form
// divides numerator and denominator by their gcd
// makes denominator 1 if the numerator is 0
// takes negative of numerator and denominator if denominator is negative
void Fraction::normalize()
{
	if(this->p==0)
	{
		this->q = 1;
	}
	int x = gcd(this->p, this->q);
	this->p = this->p/x;
	this->q = this->q/x;
	if(this->q<0)
	{
		this->p = -this->p;
		this->q = -this->q;
	}
}

// default constructor
// shows error and exits if denominator is 0
Fraction::Fraction(int m, int n)
{
	if(n==0)
	{
		std::cout << "Error. Denominator can't be zero." << std::endl;
		exit(1);
	}
	this->p = m;
	this->q = n;
	this->normalize();
}

// overloaded constructor
// converts double to fraction according to precision value
Fraction::Fraction(double d)
{
	int x = std::floor(d);
	d -= x;
	this->p = d*precision();
	this->q = precision();
	this->normalize();
	this->p = this->p + ((int)this->q)*x;
	this->normalize();
}

// copy constructor
Fraction::Fraction(const Fraction& f)
{
	this->p = f.p;
	this->q = f.q;
}

// destructor
Fraction::~Fraction()
{

}

Fraction Fraction::sc_fUnity = Fraction();
Fraction Fraction::sc_fZero = Fraction(0);

// copy assignment operator that returns refrence to allow cascading
Fraction& Fraction::operator=(const Fraction& f)
{
	if(this!=&f)
	{
		this->p = f.p;
		this->q = f.q;
	}
	return *this;
}

// unary - operator
Fraction Fraction::operator-()
{
	Fraction res = *this;
	res.p = -res.p;
	return res;
}

// unary + operator
Fraction Fraction::operator+() const
{
	return *this;
}

// unary pre-decrement operator
Fraction Fraction::operator--()
{
	this->p = this->p-this->q;
	return *this;
}

// unary pre-increment operator
Fraction Fraction::operator++()
{
	this->p = this->p+this->q;
	return *this;
}

// unary post-decrement operator
Fraction Fraction::operator--(int)
{
	Fraction res(*this);
	this->p = this->p-this->q;
	return res;
}

// unary post-increment operator
Fraction Fraction::operator++(int)
{
	Fraction res(*this);
	this->p = this->p+this->q;
	return res;
}

// binary + operator
Fraction operator+(const Fraction f1, const Fraction f2)
{
	Fraction res;
	res.q = lcm(f1.q, f2.q);
	res.p = ((res.q/f1.q)*f1.p) + ((res.q/f2.q)*f2.p);
	res.normalize();
	return res;
}

// binary - operator
Fraction operator-(const Fraction f1, const Fraction f2)
{
	Fraction res;
	res.q = lcm(f1.q, f2.q);
	res.p = ((res.q/f1.q)*f1.p) - ((res.q/f2.q)*f2.p);
	res.normalize();
	return res;
}

// binary * operator
Fraction operator*(const Fraction f1, const Fraction f2)
{
	Fraction res;
	res.p = f1.p*f2.p;
	res.q = f1.q*f2.q;
	res.normalize();
	return res;
}

// binary / operator
Fraction operator/(const Fraction f1, const Fraction f2)
{
	if(f2.p==0)
	{
		std::cout << "Error. Can't divide by zero." << std::endl;
		exit(1);
	}
	Fraction res;
	res.p = f1.p*f2.q;
	res.q = f1.q*f2.p;
	res.normalize();
	return res;
}

// binary remainder operator
Fraction operator%(const Fraction f1, const Fraction f2)
{
	if(f2.p==0)
	{
		std::cout << "Error. Can't divide by zero." << std::endl;
		exit(1);
	}
	Fraction res = f1/f2;
	res = f1 - (Fraction(int(res.p/int(res.q))))*f2;
	return res;
}

// special not operator to return inverse
Fraction Fraction::operator!()
{
	if(this->p==0)
	{
		std::cout << "Error. Denominator can't be zero." << std::endl;
		exit(1);
	}
	Fraction res;
	res.p = this->q;
	res.q = this->p;
	return res;
}

// istream operator for input
std::istream& operator>>(std::istream& s, Fraction& f)
{
	s >> f.p >> f.q;
	f.normalize();
	return s;
}

// ostream operator for output
std::ostream& operator<<(std::ostream& s, const Fraction& f)
{
	if(f.q!=1)
		s << f.p << "/" << f.q;
	else
		s << f.p;
	return s;
}