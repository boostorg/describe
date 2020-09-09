// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/mp11.hpp>

BOOST_DEFINE_ENUM(E,, v1, v2, v3)

int main()
{
    BOOST_TEST_EQ( boost::mp11::mp_size< boost::describe::describe_enumerators<E> >::value, 3 );
    return boost::report_errors();
}
