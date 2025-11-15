// Copyright 2022 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/describe/class.hpp>
#include <boost/core/lightweight_test_trait.hpp>

#if !defined(BOOST_DESCRIBE_CXX14)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because C++14 is not available")
int main() {}

#else

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wgnu-zero-variadic-macro-arguments"
#endif


// Using (void) to specify empty bases for simple structs
struct X { int foo; };
BOOST_DESCRIBE_STRUCT(X, (void), (foo))

// Using underlying macros for classes or empty types
class Y {
  public:
    int foo;
  private:
    int bar;
    friend BOOST_DESCRIBE_BASES(Y, void)
    friend BOOST_DESCRIBE_PUBLIC_MEMBERS(Y, foo)
    friend BOOST_DESCRIBE_PROTECTED_MEMBERS_EMPTY(Y)
    friend BOOST_DESCRIBE_PRIVATE_MEMBERS(Y, bar)
};


int main()
{
    using namespace boost::describe;
    using namespace boost::mp11;

    {
        using L = describe_bases<X, mod_any_access>;
        BOOST_TEST_EQ( mp_size<L>::value, 0 );
    }

    {
        using L = describe_members<X, mod_any_access>;
        BOOST_TEST_EQ( mp_size<L>::value, 1 );
    }

    {
        using L = describe_bases<Y, mod_any_access>;
        BOOST_TEST_EQ( mp_size<L>::value, 0 );
    }

    {
        using L = describe_members<Y, mod_any_access>;
        BOOST_TEST_EQ( mp_size<L>::value, 2 );
    }

    return boost::report_errors();
}



#endif
