// Copyright 2021, 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/core/lightweight_test_trait.hpp>

#if !defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because reflection is not available")
int main() {}

#else

struct X1
{
};

union X2
{
};

struct X3
{
    X3( int );
};

struct X4
{
    ~X4();
};

struct X5
{
    template<class T1, class T2> X5();
};

struct X6
{
    template<class T> void f( T );
};

struct X7
{
    struct A;
};

struct X8
{
    template<class T> struct B;
};

struct X9
{
    using T = int;
};

struct X10
{
    template<class...> using V = void;
};

struct X11
{
    enum E { e1 };
};

struct X12
{
    enum { e2 };
};

struct X13
{
    operator int() const noexcept;
};

struct X14
{
    void operator=( int );
};

struct X15
{
    auto operator<=>( X15 const& r ) const = default;
};

struct X16
{
    void f() = delete;
};

struct X17
{
    void operator=( int ) = delete;
};

int main()
{
    using boost::describe::has_describe_members;

    BOOST_TEST_TRAIT_TRUE((has_describe_members<X1>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X2>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X3>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X4>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X5>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X6>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X8>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X9>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X10>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X11>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X12>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X13>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X14>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X15>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X16>));
    BOOST_TEST_TRAIT_TRUE((has_describe_members<X17>));

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_HAS_REFLECTION)
