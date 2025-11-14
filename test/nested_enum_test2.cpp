// Copyright 2025 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/enumerators.hpp>
#include <boost/describe/enum.hpp>
#include <boost/config.hpp>
#include <boost/config/pragma_message.hpp>

#if BOOST_CXX_VERSION < 202002L

BOOST_PRAGMA_MESSAGE("Skipping test because BOOST_CXX_VERSION < 202002L")

#else

struct X
{
    enum E { v1 };
    BOOST_DESCRIBE_NESTED_ENUM(E, v1)

    using L = boost::describe::describe_enumerators<E>;
};

#endif
