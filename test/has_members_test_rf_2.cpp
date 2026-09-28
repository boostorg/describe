// Copyright 2021, 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/core/lightweight_test_trait.hpp>

struct X1
{
    int f: 12;
};

struct X2
{
    int: 12;
};

struct X3
{
    union { int m1; };
};

int main()
{
    using boost::describe::has_describe_members;

    BOOST_TEST_TRAIT_FALSE((has_describe_members<X1>));
    BOOST_TEST_TRAIT_FALSE((has_describe_members<X2>));
    BOOST_TEST_TRAIT_FALSE((has_describe_members<X3>));

    return boost::report_errors();
}
