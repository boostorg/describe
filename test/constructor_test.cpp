// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/describe/constructor.hpp>
#include <boost/describe/class.hpp>
#include <boost/core/lightweight_test.hpp>
#include <utility>

class X
{
private:

    std::pair<int, int> p_;


    X() : p_(0,0)  {}
public:
    X(int x, int y) noexcept : p_(x, y) {}
    X(const std::pair<int, int> & p) : p_(p) {}
    BOOST_DESCRIBE_CLASS(X, (), (), (), (p_));
    BOOST_DESCRIBE_CLASS_CONSTRUCTORS(X, (),  (int, int), (const std::pair<int, int>&));

    int x() {return p_.first; }
    int y() {return p_.second; }
};


#if !defined(BOOST_DESCRIBE_CXX14)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because C++14 is not available")
int main() {}

#else

#include <boost/mp11.hpp>


int main()
{
    using namespace boost::describe;
    using namespace boost::mp11;

    {

        X x(1, 2);
        BOOST_TEST_EQ(x.x(), 1);
        BOOST_TEST_EQ(x.y(), 2);
        using L1 = describe_constructors<X>;

        BOOST_TEST_EQ( mp_size<L1>::value, 3 );

        using C1 = mp_at_c<L1, 0>;
        BOOST_TEST( (std::is_same<C1::signature, X() >::value) );
        BOOST_TEST_EQ( C1::modifiers, mod_constructor );
        BOOST_TEST_EQ( C1::is_noexcept, false );
        BOOST_TEST_EQ( C1::is_trivial, false );
        BOOST_TEST_EQ(&x, C1::construct_at(&x));
        BOOST_TEST_EQ(x.x(), 0);
        BOOST_TEST_EQ(x.y(), 0);

        using C2 = mp_at_c<L1, 1>;
        BOOST_TEST( (std::is_same<C2::signature, X(int, int) >::value) );
        BOOST_TEST_EQ( C2::modifiers, mod_constructor );
        BOOST_TEST_EQ( C2::is_noexcept, true );
        BOOST_TEST_EQ( C2::is_trivial, false );
        BOOST_TEST_EQ(&x, C2::construct_at(&x, 3, 4));
        BOOST_TEST_EQ(x.x(), 3);
        BOOST_TEST_EQ(x.y(), 4);

        using C3 = mp_at_c<L1, 2>;
        BOOST_TEST( (std::is_same<C3::signature, X(const std::pair<int, int> &) >::value) );
        BOOST_TEST_EQ( C3::modifiers, mod_constructor );
        BOOST_TEST_EQ( C3::is_noexcept, false );
        BOOST_TEST_EQ( C3::is_trivial, false );
        BOOST_TEST_EQ(&x, C3::construct_at(&x, {5,6}));
        BOOST_TEST_EQ(x.x(), 5);
        BOOST_TEST_EQ(x.y(), 6);

    }

    return boost::report_errors();
}

#endif // !defined(BOOST_DESCRIBE_CXX14)
