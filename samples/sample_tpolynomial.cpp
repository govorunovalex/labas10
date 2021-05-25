#include <iostream>
#include <locale.h>

#include "tpolynomial.h"

using namespace std;

int main()
{
    try {
	int a[] = { 1, 2, 3 };
	int b[] = { 4, 5, 6 };
	TMonomial A(3, a, 1);
	TMonomial B(3, b, 2);
	cout << "Monom A: " << A << endl;
	cout << "Monom B: " << B << endl;

	TPolynomial P(3);
	P += A;
	P += B;
	cout << "\nPolynom P = A + B: " << P << endl;

	TPolynomial P2(P);
	cout << "Polynom P2(P): " << P2 << endl;

	TPolynomial P3(3);
	P3 = P + P2;
	cout << "\nPolynom P3 = P + P2 : " << P3 << endl;
    }
    catch(TException exp) {
	exp.Show();
    }
    return 0;
}
