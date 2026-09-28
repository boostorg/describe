// Copyright 2020, 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/core/lightweight_test.hpp>

class X
{
public:

    virtual void f1() = 0;

protected:

    virtual void f2() = 0;

private:

    virtual void f3() = 0;
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

    {
        using L = describe_members<X, mod_public | mod_function>;

        BOOST_TEST_EQ( mp_size<L>::value, 1 );

        using D1 = mp_at_c<L, 0>;

        // BOOST_TEST( D1::pointer == &X::f1 );
        BOOST_TEST_CSTR_EQ( D1::name, "f1" );
        BOOST_TEST_EQ( D1::modifiers, mod_public | mod_function | mod_virtual );
    }

    {
        using L = describe_members<X, mod_protected | mod_function>;

        BOOST_TEST_EQ( mp_size<L>::value, 1 );

        using D1 = mp_at_c<L, 0>;

        // BOOST_TEST( D1::pointer == &X::f2 );
        BOOST_TEST_CSTR_EQ( D1::name, "f2" );
        BOOST_TEST_EQ( D1::modifiers, mod_protected | mod_function | mod_virtual );
    }

    {
        using L = describe_members<X, mod_private | mod_function>;

        BOOST_TEST_EQ( mp_size<L>::value, 1 );

        using D1 = mp_at_c<L, 0>;

        // BOOST_TEST( D1::pointer == &X::f3 );
        BOOST_TEST_CSTR_EQ( D1::name, "f3" );
        BOOST_TEST_EQ( D1::modifiers, mod_private | mod_function | mod_virtual );
    }

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_HAS_REFLECTION)
