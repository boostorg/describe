#ifndef BOOST_DESCRIBE_BASE_CLASSES_HPP_INCLUDED
#define BOOST_DESCRIBE_BASE_CLASSES_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>

namespace boost
{
namespace describe
{
namespace detail
{

template<class T> using _describe_base_classes = decltype( _base_class_descriptor_fn( static_cast<T*>(0) ) );

} // namespace detail

template<class T, unsigned M> using describe_base_classes = detail::_describe_base_classes<T>;

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_BASE_CLASSES_HPP_INCLUDED
