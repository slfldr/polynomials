#include "gtest.h"
#include "polynomial.h"

TEST(term_test, default_constructor)
{
    Term t;

    EXPECT_EQ(t.get_degree(), 0);
    EXPECT_EQ(t.get_k(), 0);
}

TEST(term_test, constructor_with_parameters)
{
    Term t(123, 5.0);

    EXPECT_EQ(t.get_degree(), 123);
    EXPECT_EQ(t.get_k(), 5.0);
}

TEST(term_test, constructor_throws_exception_for_invalid_degree)
{
    EXPECT_THROW(Term t(1000, 5.0), std::invalid_argument);
}

TEST(term_test, add_terms_with_equal_degree)
{
    Term t1(123, 2.0);
    Term t2(123, 3.0);

    Term result = t1 + t2;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.get_k(), 5.0);
}

TEST(term_test, add_terms_with_different_degrees)
{
    Term t1(123, 2.0);
    Term t2(124, 3.0);

    EXPECT_THROW(t1 + t2, std::logic_error);
}

TEST(term_test, subtract_terms_with_equal_degree)
{
    Term t1(123, 5.0);
    Term t2(123, 2.0);

    Term result = t1 - t2;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.get_k(), 3.0);
}

TEST(term_test, subtract_terms_with_different_degrees)
{
    Term t1(123, 5.0);
    Term t2(124, 2.0);

    EXPECT_THROW(t1 - t2, std::logic_error);
}

TEST(term_test, multiply_term_with_scalar)
{
    Term t(123, 3.0);

    Term result = t * 2.0;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.get_k(), 6.0);
}

TEST(term_test, multiply_terms)
{
    Term t1(123, 3.0);
    Term t2(124, 4.0);

    Term result = t1 * t2;

    EXPECT_EQ(result.get_degree(), 247);
    EXPECT_EQ(result.get_k(), 12.0);
}

TEST(term_test, multiply_term_with_zero)
{
    Term t(123, 3.0);
    Term result = t * 0.0;

    EXPECT_EQ(result.get_degree(), 0);
    EXPECT_EQ(result.get_k(), 0.0);
}

TEST(polynomial_test, default_constructor)
{
    Polynomial p;

    EXPECT_EQ(p.get_size(), 0);
}

TEST(polynomial_test, add_term)
{
    Polynomial p;

    Term t1(123, 2.0);

    p.add_term(t1);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.get_k(), 2.0);
}

TEST(polynomial_test, add_multiple_terms)
{
    Polynomial p;

    Term t1(123, 2.0);
    Term t2(124, 3.0);

    p.add_term(t1);
    p.add_term(t2);

    EXPECT_EQ(p.get_size(), 2);
    EXPECT_EQ(p.get_first()->value.get_degree(), 124);
    EXPECT_EQ(p.get_first()->value.get_k(), 3.0);
    EXPECT_EQ(p.get_first()->next->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->next->value.get_k(), 2.0);
}

TEST(polynomial_test, add_terms_with_same_degree)
{
    Polynomial p;

    Term t1(123, 2.0);
    Term t2(123, 3.0);

    p.add_term(t1);
    p.add_term(t2);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.get_k(), 5.0);
}

TEST(polynomial_test, add_terms_with_zero_coefficient)
{
    Polynomial p;

    Term t1(123, 2.0);
    Term t2(124, 0.0);

    p.add_term(t1);
    p.add_term(t2);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.get_k(), 2.0);
}

TEST(polynomial_test, add_polynomials)
{
    Polynomial p1;
    Term t1(123, 2.0);
    Term t2(124, 3.0);
    p1.add_term(t1);
    p1.add_term(t2);

    Polynomial p2;
    Term t3(123, 1.0);
    Term t4(125, 4.0);
    p2.add_term(t3);
    p2.add_term(t4);

    Polynomial result = p1 + p2;

    EXPECT_EQ(result.get_size(), 3);
    EXPECT_EQ(result.get_first()->value.get_degree(), 125);
    EXPECT_EQ(result.get_first()->value.get_k(), 4.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->next->value.get_k(), 3.0);
    EXPECT_EQ(result.get_first()->next->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->next->value.get_k(), 3.0);
}

TEST(polynomial_test, add_polynomials_with_same_degrees)
{
    Polynomial p1;
    Term t1(123, 2.0);
    Term t2(124, 3.0);
    p1.add_term(t1);
    p1.add_term(t2);

    Polynomial p2;
    Term t3(123, 1.0);
    Term t4(124, 4.0);
    p2.add_term(t3);
    p2.add_term(t4);

    Polynomial result = p1 + p2;

    EXPECT_EQ(result.get_size(), 2);
    EXPECT_EQ(result.get_first()->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->value.get_k(), 7.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->value.get_k(), 3.0);
}

TEST(polynomial_test, add_polynomials_with_different_degrees)
{
    Polynomial p1;
    Term t1(123, 2.0);
    Term t2(124, 3.0);
    p1.add_term(t1);
    p1.add_term(t2);

    Polynomial p2;
    Term t3(125, 4.0);
    p2.add_term(t3);

    Polynomial result = p1 + p2;

    EXPECT_EQ(result.get_size(), 3);
    EXPECT_EQ(result.get_first()->value.get_degree(), 125);
    EXPECT_EQ(result.get_first()->value.get_k(), 4.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->next->value.get_k(), 3.0);
    EXPECT_EQ(result.get_first()->next->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->next->value.get_k(), 2.0);
}

TEST(polynomial_test, multiply_polynomial_by_scalar)
{
    Polynomial p;

    Term t1(123, 2.0);
    Term t2(124, 3.0);

    p.add_term(t1);
    p.add_term(t2);

    Polynomial result = p * 2.0;

    EXPECT_EQ(result.get_size(), 2);
    EXPECT_EQ(result.get_first()->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->value.get_k(), 6.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->value.get_k(), 4.0);
}

TEST(polynomial_test, multiply_polynomial_by_zero)
{
    Polynomial p;
    Term t1(123, 2.0);
    Term t2(124, 3.0);
    p.add_term(t1);
    p.add_term(t2);

    Polynomial result = p * 0.0;

    EXPECT_EQ(result.get_size(), 0);
}