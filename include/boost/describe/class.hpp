#ifndef BOOST_DESCRIBE_CLASS_HPP_INCLUDED
#define BOOST_DESCRIBE_CLASS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/base_classes.hpp>

namespace boost
{
namespace describe
{

#define BOOST_DESCRIBE_PP_UNPACK(...) __VA_ARGS__

#define BOOST_DESCRIBE_CLASS(C, Bases, PublicData, PrivateData, Functions) \
    friend BOOST_DESCRIBE_BASE_CLASSES(C, BOOST_DESCRIBE_PP_UNPACK Bases)

#define BOOST_DESCRIBE_STRUCT(C, Bases, Data, Functions) \
    BOOST_DESCRIBE_BASE_CLASSES(C, BOOST_DESCRIBE_PP_UNPACK Bases)

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_CLASS_HPP_INCLUDED
