// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/enumerators.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/mp11.hpp>

using namespace boost::mp11;

enum E1
{
    v1_1,
    v1_2,
    v1_3,
    v1_4
};

BOOST_DESCRIBE_ENUM(E1, v1_1, v1_2, v1_3, v1_4);

enum class E2
{
    v2_1,
    v2_2,
    v2_3,
    v2_4
};

BOOST_DESCRIBE_ENUM_CLASS(E2, v2_1, v2_2, v2_3, v2_4);

int main()
{
    {
        using D1 = boost::describe::describe_enumerators<E1>;

        BOOST_TEST_EQ( (mp_at_c<D1, 0>::value), v1_1 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D1, 0>::name), "v1_1" );

        BOOST_TEST_EQ( (mp_at_c<D1, 1>::value), v1_2 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D1, 1>::name), "v1_2" );

        BOOST_TEST_EQ( (mp_at_c<D1, 2>::value), v1_3 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D1, 2>::name), "v1_3" );

        BOOST_TEST_EQ( (mp_at_c<D1, 3>::value), v1_4 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D1, 3>::name), "v1_4" );
    }

    {
        using D2 = boost::describe::describe_enumerators<E2>;

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 0>::value), (int)E2::v2_1 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 0>::name), "v2_1" );

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 1>::value), (int)E2::v2_2 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 1>::name), "v2_2" );

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 2>::value), (int)E2::v2_3 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 2>::name), "v2_3" );

        BOOST_TEST_EQ( (int)(mp_at_c<D2, 3>::value), (int)E2::v2_4 );
        BOOST_TEST_CSTR_EQ( (mp_at_c<D2, 3>::name), "v2_4" );
    }

    return boost::report_errors();
}
