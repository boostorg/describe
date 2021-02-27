// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/pp_for_each.hpp>
#include <boost/describe/detail/config.hpp>
#include <boost/core/lightweight_test.hpp>

#if !defined(BOOST_DESCRIBE_CXX11)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because C++11 is not available")
int main() {}

#else

#define F1(x, y) #y

char const * s0 = "" BOOST_DESCRIBE_PP_FOR_EACH(F1, ~);
char const * s1 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a);
char const * s2 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b);
char const * s3 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c);
char const * s4 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d);
char const * s5 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e);
char const * s6 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f);
char const * s7 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g);
char const * s8 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h);
char const * s9 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i);
char const * s10 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j);
char const * s11 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k);
char const * s12 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l);
char const * s13 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m);
char const * s14 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n);
char const * s15 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o);
char const * s16 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
char const * s17 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q);
char const * s18 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r);
char const * s19 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s);
char const * s20 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t);
char const * s21 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u);
char const * s22 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v);
char const * s23 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w);
char const * s24 = BOOST_DESCRIBE_PP_FOR_EACH(F1, ~, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x);

int main()
{
    BOOST_TEST_CSTR_EQ( s0, "" );
    BOOST_TEST_CSTR_EQ( s1, "a" );
    BOOST_TEST_CSTR_EQ( s2, "ab" );
    BOOST_TEST_CSTR_EQ( s3, "abc" );
    BOOST_TEST_CSTR_EQ( s4, "abcd" );
    BOOST_TEST_CSTR_EQ( s5, "abcde" );
    BOOST_TEST_CSTR_EQ( s6, "abcdef" );
    BOOST_TEST_CSTR_EQ( s7, "abcdefg" );
    BOOST_TEST_CSTR_EQ( s8, "abcdefgh" );
    BOOST_TEST_CSTR_EQ( s9, "abcdefghi" );
    BOOST_TEST_CSTR_EQ( s10, "abcdefghij" );
    BOOST_TEST_CSTR_EQ( s11, "abcdefghijk" );
    BOOST_TEST_CSTR_EQ( s12, "abcdefghijkl" );
    BOOST_TEST_CSTR_EQ( s13, "abcdefghijklm" );
    BOOST_TEST_CSTR_EQ( s14, "abcdefghijklmn" );
    BOOST_TEST_CSTR_EQ( s15, "abcdefghijklmno" );
    BOOST_TEST_CSTR_EQ( s16, "abcdefghijklmnop" );
    BOOST_TEST_CSTR_EQ( s17, "abcdefghijklmnopq" );
    BOOST_TEST_CSTR_EQ( s18, "abcdefghijklmnopqr" );
    BOOST_TEST_CSTR_EQ( s19, "abcdefghijklmnopqrs" );
    BOOST_TEST_CSTR_EQ( s20, "abcdefghijklmnopqrst" );
    BOOST_TEST_CSTR_EQ( s21, "abcdefghijklmnopqrstu" );
    BOOST_TEST_CSTR_EQ( s22, "abcdefghijklmnopqrstuv" );
    BOOST_TEST_CSTR_EQ( s23, "abcdefghijklmnopqrstuvw" );
    BOOST_TEST_CSTR_EQ( s24, "abcdefghijklmnopqrstuvwx" );

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_CXX11)
