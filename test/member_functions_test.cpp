// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/member_functions.hpp>
#include <boost/describe/class.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/mp11.hpp>

using namespace boost::mp11;

struct X
{
    void f() {}
    int g() const { return 1; }
    static void h() {}
};

BOOST_DESCRIBE_STRUCT(X, (), (), (f, g, h))

int main()
{
    using namespace boost::describe;
    using namespace boost::mp11;

    {
        using L = describe_member_functions<X, mod_protected>;
        BOOST_TEST_EQ( mp_size<L>::value, 0 );
    }

    {
        using L = describe_member_functions<X, mod_private>;
        BOOST_TEST_EQ( mp_size<L>::value, 0 );
    }

    {
        using L = describe_member_functions<X, mod_public>;

        BOOST_TEST_EQ( mp_size<L>::value, 2 );

        using D1 = mp_at_c<L, 0>;
        using D2 = mp_at_c<L, 1>;

        BOOST_TEST( D1::pointer == &X::f );
        BOOST_TEST_CSTR_EQ( D1::name, "f" );
        BOOST_TEST_EQ( D1::modifiers, mod_public );

        BOOST_TEST( D2::pointer == &X::g );
        BOOST_TEST_CSTR_EQ( D2::name, "g" );
        BOOST_TEST_EQ( D2::modifiers, mod_public );
    }

    {
        using L = describe_member_functions<X, mod_public | mod_static>;

        BOOST_TEST_EQ( mp_size<L>::value, 1 );

        using D1 = mp_at_c<L, 0>;

        BOOST_TEST( D1::pointer == &X::h );
        BOOST_TEST_CSTR_EQ( D1::name, "h" );
        BOOST_TEST_EQ( D1::modifiers, mod_public | mod_static );
    }

    return boost::report_errors();
}
