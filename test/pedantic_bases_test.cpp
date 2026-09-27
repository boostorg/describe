// Copyright 2022 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/bases.hpp>
#include <boost/core/lightweight_test_trait.hpp>

struct X {};

int main()
{
#if defined(BOOST_DESCRIBE_CXX11)
#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

    BOOST_TEST_TRAIT_TRUE((boost::describe::has_describe_bases<X>));

#else

    BOOST_TEST_TRAIT_FALSE((boost::describe::has_describe_bases<X>));

#endif
#endif

    return boost::report_errors();
}
