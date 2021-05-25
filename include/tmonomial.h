#pragma once

#include <iostream>
#include "exception.h"
using namespace std;

class TMonomial {
  protected:
    int *power;			//массив степеней
    int n;			//кол-во переменных в мономе
    double coeff;		///коэффицтент
    TMonomial *next;		//указатель на следующий моном
  public:
     TMonomial(int _n = 10);
     TMonomial(int _n, int *_power, double _coeff);
     TMonomial(const TMonomial & A);
    ~TMonomial();

    void SetPower(int *_power);
    void SetN(int _n);
    void SetCoeff(double _coeff);
    void SetNext(TMonomial * _next);

    int *GetPower();
    int GetN() const;
    double GetCoeff() const;
    TMonomial *GetNext();

    bool ComparePowers(const TMonomial & A);

     TMonomial & operator =(const TMonomial & A);
    TMonomial operator +(TMonomial & A);
     TMonomial & operator +=(const TMonomial & A);
    TMonomial operator -(TMonomial & A);
     TMonomial & operator -=(const TMonomial & A);
    TMonomial operator *(TMonomial & A);
     TMonomial & operator *=(TMonomial & A);

    bool operator ==(TMonomial & A);
    bool operator <(TMonomial & A);
    bool operator >(TMonomial & A);

    friend istream & operator>>(istream & istr, TMonomial & m);
    friend ostream & operator<<(ostream & ostr, TMonomial & m);
};

TMonomial::TMonomial(int _n)
{
    if (_n < 0)
	throw TException("Error");
    else
if (_n == 0) {
    n = 0;
    next = NULL;
    power = 0;
    coeff = 0;
} else if (_n > 0) {
    n = _n;
    next = NULL;
    power = new int[n];
    coeff = 0;
}
}

TMonomial::TMonomial(int _n, int *_power, double _coeff)
{
    if (_n < 0)
	throw TException("Error");
    else
if (_n == 0) {
    power = 0;
    next = NULL;
    coeff = _coeff;
    n = _n;
} else {
    n = _n;
    coeff = _coeff;
    next = 0;
    power = new int[_n];
    for (int i = 0; i < _n; i++) {
	if (_power[i] >= 0)
	    power[i] = _power[i];
	else
	    throw TException("Error");
    }
}
}

TMonomial::TMonomial(const TMonomial & A)
{
    n = A.n;
    coeff = A.coeff;
    next = A.next;
    if (n != 0) {
	power = new int[n];
	for (int i = 0; i < n; i++) {
	    power[i] = A.power[i];
	}
    } else
	power = NULL;
}

TMonomial::~TMonomial()
{
    if (power)
	delete[]power;
    n = 0;
    coeff = 0;
    next = 0;
}

void TMonomial::SetPower(int *_power)
{
    for (int i = 0; i < n; i++) {
	if (_power[i] >= 0)
	    power[i] = _power[i];
	else
	    throw TException("Error");
    }
}

void TMonomial::SetN(int _n)
{
    if (_n <= 0)
	throw TException("Error");
    else
if (_n == 0) {
    if (power != 0)
	delete[]power;
    power = NULL;
} else if (_n != n) {
    int *tmp = power;
    power = new int[_n];

    int count = n < _n ? n : _n;
    for (int i = 0; i < count; i++) {
	power[i] = tmp[i];
    }
    delete[]tmp;
}
    n = _n;
}

void TMonomial::SetCoeff(double _coeff)
{
    coeff = _coeff;
}

void TMonomial::SetNext(TMonomial * _next)
{
    next = _next;
}

int *TMonomial::GetPower()
{
    return power;
}

int TMonomial::GetN() const
{
    return n;
}

double TMonomial::GetCoeff() const
{
    return coeff;
}

TMonomial *TMonomial::GetNext()
{
    return next;
}

bool TMonomial::ComparePowers(const TMonomial & A)
{
    if (n != A.n)
	return false;
    for (int i = 0; i < n; i++)
	if (power[i] != A.power[i])
	    return false;
    return true;
};

TMonomial & TMonomial::operator =(const TMonomial & A)
{
    coeff = A.coeff;
    n = A.n;
    next = A.next;
    delete[]power;
    power = new int[n];
    for (int i = 0; i < n; i++)
	power[i] = A.power[i];
    return *this;
}

TMonomial TMonomial::operator +(TMonomial & A)
{
    TMonomial tmp(*this);
    tmp += A;
    return tmp;
}

TMonomial & TMonomial::operator+=(const TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    for (int i = 0; i < n; i++)
	if (power[i] != A.power[i])
	    throw TException("Error");
    coeff += A.coeff;
    return *this;
}

TMonomial TMonomial::operator -(TMonomial & A)
{
    TMonomial tmp(*this);
    tmp -= A;
    return tmp;
}

TMonomial & TMonomial::operator-=(const TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    for (int i = 0; i < n; i++)
	if (power[i] != A.power[i])
	    throw TException("Error");
    coeff -= A.coeff;
    return *this;
}

TMonomial TMonomial::operator *(TMonomial & A)
{
    TMonomial tmp(*this);
    tmp *= A;
    return tmp;
}

TMonomial & TMonomial::operator *=(TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    coeff *= A.coeff;
    for (int i = 0; i < n; i++)
	power[i] += A.power[i];
    return *this;
}

bool TMonomial::operator ==(TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    if (coeff != A.coeff)
	return false;
    for (int i = 0; i < n; i++)
	if (power[i] != A.power[i])
	    return false;
    return true;
}

bool TMonomial::operator >(TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    for (int i = 0; i < n; i++) {
	if (power[i] == A.power[i])
	    continue;
	else
	    return power[i] > A.power[i] ? true : false;
    }
    return coeff > A.coeff ? true : false;
}

bool TMonomial::operator <(TMonomial & A)
{
    if (n != A.n)
	throw TException("Error");
    for (int i = 0; i < n; i++) {
	if (power[i] == A.power[i])
	    continue;
	else
	    return power[i] < A.power[i] ? true : false;
    }
    return coeff < A.coeff ? true : false;
}

istream & operator>>(istream & istr, TMonomial & m)
{
    istr >> m.coeff;
    for (int i = 0; i < m.n; i++)
	istr >> m.power[i];
    return istr;
}

ostream & operator<<(ostream & ostr, TMonomial & m)
{
    ostr << m.GetCoeff();
    for (int i = 0; i < m.GetN(); i++)
	ostr << "*" << "x" << i << "^" << m.GetPower()[i];

    return ostr;
}
