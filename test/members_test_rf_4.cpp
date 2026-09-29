// Copyright 2020, 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/core/lightweight_test.hpp>

struct X
{
    int a;
    int b;
};

#if !defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because reflection is not available")
int main() {}

#else

#include <boost/mp11.hpp>

int main()
{
    using namespace boost::describe;
    using namespace boost::mp11;

    using Y = X;

    {
        using L = describe_members<Y, mod_any_access>;

        BOOST_TEST_EQ( mp_size<L>::value, 2 );

        using D1 = mp_at_c<L, 0>;

        BOOST_TEST( D1::pointer == &Y::a );
        BOOST_TEST_CSTR_EQ( D1::name, "a" );
        BOOST_TEST_EQ( D1::modifiers, mod_public );

        using D2 = mp_at_c<L, 1>;

        BOOST_TEST( D2::pointer == &Y::b );
        BOOST_TEST_CSTR_EQ( D2::name, "b" );
        BOOST_TEST_EQ( D2::modifiers, mod_public );
    }

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_HAS_REFLECTION)
