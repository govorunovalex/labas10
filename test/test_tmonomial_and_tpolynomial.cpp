#include "tpolynomial.h"

#include <gtest.h>

TEST(TMonomial, can_create_default_monomial)
{
    ASSERT_NO_THROW(TMonomial A);
}

TEST(TMonomial, can_create_monomial_wiht_custom_size)
{
    ASSERT_NO_THROW(TMonomial A(3));
}

TEST(TMonomial, throws_when_create_monomial_with_negative_size)
{
    ASSERT_ANY_THROW(TMonomial A(-3));
}

TEST(TMonomial, throws_when_create_monom_with_negative_power)
{
    int a[3] = { 1, -2, 3 };
    ASSERT_ANY_THROW(TMonomial A(3, a, 1));
}

TEST(TMonomial, can_create_monomial_with_parameters)
{
    int a[3] = { 1, 2, 3 };
    ASSERT_NO_THROW(TMonomial A(3, a, 3.34));
}

TEST(TMonomial, can_create_copy_of_the_monomial)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 3.34);
    TMonomial B(A);
    ASSERT_EQ(B.GetCoeff(), A.GetCoeff());
    ASSERT_EQ(B.GetN(), A.GetN());
    ASSERT_EQ(B.GetNext(), A.GetNext());
    int *power = B.GetPower();
    for (int i = 0; i < 3; i++) {
	ASSERT_EQ(power[i], a[i]);
    }
}

TEST(TMonomial, can_set_next)
{
    TMonomial A(2);
    TMonomial B(3);
    ASSERT_NO_THROW(A.SetNext(&B));
    ASSERT_EQ(A.GetNext(), &B);
}

TEST(TMonomial, can_set_and_get_coeff)
{
    TMonomial A;
    ASSERT_NO_THROW(A.SetCoeff(3.14));
    ASSERT_EQ(3.14, A.GetCoeff());
}

TEST(TMonomial, can_set_and_get_power)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3);
    ASSERT_NO_THROW(A.SetPower(a));
    ASSERT_EQ(1, A.GetPower()[0]);
    ASSERT_EQ(2, A.GetPower()[1]);
    ASSERT_EQ(3, A.GetPower()[2]);
}

TEST(TMonomial, can_set_and_get_size)
{
    TMonomial A(3);
    ASSERT_NO_THROW(A.SetN(5));
    ASSERT_EQ(5, A.GetN());
}

TEST(TMonomial, can_assign_monomials)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 3.12);
    TMonomial B(6);
    B = A;
    ASSERT_EQ(B.GetCoeff(), A.GetCoeff());
    ASSERT_EQ(B.GetN(), A.GetN());
    ASSERT_EQ(B.GetNext(), A.GetNext());
    int *power = B.GetPower();
    for (int i = 0; i < 3; i++) {
	ASSERT_EQ(power[i], a[i]);
    }
}

TEST(TMonomial, can_add_monomials_with_equal_size)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 3.1);
    TMonomial B(3, a, 0.5);
    ASSERT_NO_THROW(A + B);
    TMonomial C(3);
    C = A + B;
    ASSERT_EQ(3.6, C.GetCoeff());
}

TEST(TMonomial, trows_when_add_monomials_with_different_size_and_powers)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3);
    TMonomial B(3);
    TMonomial C(4);
    A.SetPower(a);
    ASSERT_ANY_THROW(A + B);
    ASSERT_ANY_THROW(A + C);
}

TEST(TMonomial, can_subtract_monomials_with_equal_size)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 3.1);
    TMonomial B(3, a, 0.5);
    ASSERT_NO_THROW(A - B);
    TMonomial C(3);
    C = A - B;
    ASSERT_EQ(2.6, C.GetCoeff());
}

TEST(TMonomial,
     trows_when_subtract_monomials_with_different_size_and_power)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3);
    TMonomial B(3);
    TMonomial C(4);
    A.SetPower(a);
    ASSERT_ANY_THROW(A - B);
    ASSERT_ANY_THROW(A - C);
}

TEST(TMonomial, can_multiply_monomials_with_equal_size)
{
    int a[3] = { 1, 2, 3 };
    int a2[3] = { 3, 2, 1 };
    TMonomial A(3, a, 3.1);
    TMonomial B(3, a2, 0.5);
    ASSERT_NO_THROW(A * B);
    TMonomial C(3);
    C = A * B;
    ASSERT_EQ(3.1 * 0.5, C.GetCoeff());
    for (int i = 0; i < 3; i++)
	ASSERT_EQ(C.GetPower()[i], 4);
}

TEST(TMonomial, trows_when_multiply_monomials_with_different_size)
{
    int a[3];
    for (int i = 0; i < 3; i++)
	a[i] = i + 1;
    TMonomial A(3);
    TMonomial C(4);
    A.SetPower(a);
    ASSERT_ANY_THROW(A * C);
}

TEST(TMonomial, can_equivalence_equal_monomials)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 3.1);
    TMonomial B(3, a, 3.1);
    ASSERT_TRUE(A == B);
}

TEST(TMonomial, trows_when_equivalence_monomials_with_different_size)
{
    TMonomial A(3);
    TMonomial B(4);
    ASSERT_ANY_THROW(A == B);
}

TEST(TMonomial, equivalence_different_monomials_with_equal_size)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 1, 3, 2 };
    TMonomial A(3);
    TMonomial B(3);
    A.SetPower(a);
    B.SetPower(b);
    ASSERT_FALSE(A == B);
    B.SetPower(a);
    A.SetCoeff(3.1);
    B.SetCoeff(3.4);
    ASSERT_FALSE(A == B);
}

TEST(TMonomial, can_compare_monomials_with_equal_size)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 1, 3, 2 };
    TMonomial A(3, a, 1);
    TMonomial B(3, b, 1);
    ASSERT_FALSE(A > B);
    ASSERT_TRUE(A < B);
}

TEST(TMonomial, trows_when_compare_monomials_with_different_size)
{
    TMonomial A(3);
    TMonomial B(4);
    ASSERT_ANY_THROW(A > B);
    ASSERT_ANY_THROW(A < B);
}

TEST(TMonomial, compare_powers_of_monomials)
{
    int a[3] = { 1, 2, 3 };
    TMonomial A(3, a, 4);
    TMonomial B(3, a, 5);
    ASSERT_TRUE(A.ComparePowers(B));
}

TEST(TPolynomial, can_create_polynomial)
{
    ASSERT_NO_THROW(TPolynomial A);
}

TEST(TPolynomial, can_create_polynomial_with_positive_n)
{
    ASSERT_NO_THROW(TPolynomial A(3));
}

TEST(TPolynomial, throws_when_create_polynomial_with_negative_n)
{
    ASSERT_ANY_THROW(TPolynomial A(-3));
}

TEST(TPolynomial, can_create_copy_polynomial)
{
    TPolynomial A(3);
    ASSERT_NO_THROW(TPolynomial B(A));
    TPolynomial C(A);
    ASSERT_EQ(C.GetSize(), 0);
    ASSERT_EQ(C.GetN(), 3);
    if (C.GetStart() != NULL)
	ASSERT_TRUE(false);
}

TEST(TPolynomial, can_get_size_polynomial)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 1, 0, 3 };
    TMonomial A(3, a, 1);
    TMonomial B(3, b, 2);
    TPolynomial P(3);
    P += A;
    P += B;
    ASSERT_EQ(P.GetSize(), 2);
}

TEST(TPolynomial, can_get_n_of_polynomial)
{
    TPolynomial P(3);
    ASSERT_EQ(P.GetN(), 3);
}

TEST(TPolynomial, trows_when_add_polynomials_with_different_n)
{
    TPolynomial P1(2);
    TPolynomial P2(3);
    ASSERT_ANY_THROW(P1 + P2);
}

TEST(TPolynomial, trows_when_subtract_polynomials_with_different_n)
{
    TPolynomial P1(2);
    TPolynomial P2(3);
    ASSERT_ANY_THROW(P1 - P2);
}

TEST(TPolynomial, add_polynomials)
{
    int a[] = { 1, 0, 3 };
    TMonomial M1(3, a, 1);
    TPolynomial P(3);
    P += M1;
    int b[] = { 1, 2, 3 };
    TMonomial M2(3, b, 4);
    TPolynomial R(3);
    R += M2;
    TPolynomial S(3);
    S = R + P;
    TMonomial *ptr = S.GetStart();
    ASSERT_TRUE((*ptr == M1 && *ptr->GetNext() == M2) ||
		(*ptr == M2 && *ptr->GetNext() == M1));
    ptr = ptr->GetNext();
    if (ptr->GetNext() != NULL)
	ASSERT_TRUE(false);
}

TEST(TPolynomial, sub_polynomials)
{
    int a[] = { 1, 0, 3 };
    TMonomial M1(3, a, 1);
    TPolynomial P(3);
    P += M1;

    int b[] = { 1, 2, 3 };
    TMonomial M2(3, b, 4);
    TPolynomial R(3);
    R += M2;

    TPolynomial S(3);
    S = R - P;

    TMonomial *ptr = S.GetStart();
    M1.SetCoeff(M1.GetCoeff() * (-1));
    ASSERT_TRUE((*ptr == M1 && *ptr->GetNext() == M2) ||
		(*ptr == M2 && *ptr->GetNext() == M1));

    ptr = ptr->GetNext();
    if (ptr->GetNext() != NULL)
	ASSERT_TRUE(false);
}

TEST(TPolynomial, throws_when_assign_monomials_with_different_n)
{
    TPolynomial P1(4);
    TPolynomial P2(3);
    ASSERT_ANY_THROW(P1 = P2);
}

TEST(TPolynomial, trows_when_equivalence_polynomials_with_different_n)
{
    TPolynomial P1(3);
    TPolynomial P2(4);
    ASSERT_ANY_THROW(P1 == P2);
}

TEST(TPolynomial, trows_when_multiply_different_polynomials)
{
    TPolynomial P1(3);
    TPolynomial P2(4);
    ASSERT_ANY_THROW(P1 * P2);
}

TEST(TPolynomial, trows_when_plus_eq_different_polynomials)
{
    int a[] = { 1, 0, 3, 6 };
    TMonomial M(4, a, 1);
    TPolynomial P(3);
    ASSERT_ANY_THROW(P += M);
}

TEST(TPolynomial, trows_when_minus_eq_different_polynomials)
{
    int a[] = { 1, 0, 3, 6 };
    TMonomial M(4, a, 1);
    TPolynomial P(3);
    ASSERT_ANY_THROW(P -= M);
}

TEST(TPolynomial, can_add_polynomials_with_equal_n)
{
    TPolynomial P1(2);
    TPolynomial P2(2);
    ASSERT_NO_THROW(P1 + P2);
}

TEST(TPolynomial, can_subtract_polynomials_with_equal_n)
{
    TPolynomial P1(2);
    TPolynomial P2(2);
    ASSERT_NO_THROW(P1 - P2);
}
