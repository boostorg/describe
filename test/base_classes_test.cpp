// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/base_classes.hpp>
#include <boost/describe/class.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/mp11.hpp>

using namespace boost::mp11;

struct X1
{
};

struct X2
{
};

struct X3
{
};

struct X4
{
};

struct Y: public X1, private X2, public virtual X3, private virtual X4
{
};

BOOST_DESCRIBE_STRUCT(Y, (X1, X2, X3, X4), (), ())

int main()
{
    using namespace boost::describe;
    using namespace boost::mp11;

    {
        using L1 = describe_base_classes<Y, mod_any_access>;

        BOOST_TEST_EQ( mp_size<L1>::value, 4 );

        BOOST_TEST_TRAIT_SAME( typename mp_at_c<L1, 0>::type, X1 );
        BOOST_TEST_EQ( (mp_at_c<L1, 0>::modifiers), mod_public );

        BOOST_TEST_TRAIT_SAME( typename mp_at_c<L1, 1>::type, X2 );
        BOOST_TEST_EQ( (mp_at_c<L1, 1>::modifiers), mod_private );

        BOOST_TEST_TRAIT_SAME( typename mp_at_c<L1, 2>::type, X3 );
        BOOST_TEST_EQ( (mp_at_c<L1, 2>::modifiers), mod_public | mod_virtual );

        BOOST_TEST_TRAIT_SAME( typename mp_at_c<L1, 3>::type, X4 );
        BOOST_TEST_EQ( (mp_at_c<L1, 3>::modifiers), mod_private | mod_virtual );
    }

    return boost::report_errors();
}
