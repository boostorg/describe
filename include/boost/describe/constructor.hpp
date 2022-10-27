//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_DESCRIBE_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_DESCRIBE_CONSTRUCTOR_HPP_INCLUDED

#include <boost/describe/modifiers.hpp>
#include <boost/describe/detail/void_t.hpp>
#include <boost/describe/detail/config.hpp>


#if defined(BOOST_DESCRIBE_CXX11)

#include <boost/mp11/algorithm.hpp>
#include <type_traits>

namespace boost
{
namespace describe
{
namespace detail
{

template<class T> using _describe_ctors = decltype( boost_ctor_descriptor_fn( static_cast<T**>(0) ) );

template<class T, class En = void> struct has_describe_ctors: std::false_type
{
};

template<class T> struct has_describe_ctors<T, void_t<_describe_ctors<T>>>: std::true_type
{
};

}

template<class T> using describe_constructors = detail::_describe_ctors<T>;

template<class T> using has_describe_constructors = detail::has_describe_ctors<T>;

}
}

#endif // !defined(BOOST_DESCRIBE_CXX11)

#endif //BOOST_DESCRIBE_CONSTRUCTOR_HPP_INCLUDED
