// Copyright 2020, 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/enumerators.hpp>
#include <boost/core/lightweight_test.hpp>

#if !defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because reflection is not available")
int main() {}

#else

enum E1
{
    v1_1 = 5
};

enum class E2
{
    v2_1,
    v2_2 = 7
};

#include <boost/mp11.hpp>
using namespace boost::mp11;

int main()
{
    {
        using F1 = E1;
        using D1 = boost::describe::describe_enumerators<F1>;

        BOOST_TEST_EQ( mp_size<D1>::value, 1 );

        BOOST_TEST_EQ( (mp_at_c<D1, 0>::value), v1_1 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D1, 0>::name), "v1_1" );
    }

    {
        using F2 = E2;
        using D2 = boost::describe::describe_enumerators<F2>;

        BOOST_TEST_EQ( mp_size<D2>::value, 2 );

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 0>::value), (int)F2::v2_1 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 0>::name), "v2_1" );

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 1>::value), (int)F2::v2_2 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 1>::name), "v2_2" );
    }

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_HAS_REFLECTION)
