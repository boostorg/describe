#ifndef BOOST_DESCRIBE_DETAIL_RF_BASES_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_RF_BASES_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/describe/detail/rf_as_list.hpp>
#include <boost/describe/detail/rf_compute_modifiers.hpp>
#include <meta>

namespace boost
{
namespace describe
{
namespace detail
{

template<auto J> struct rf_base_descriptor
{
    using type = [: type_of( J ) :];
    static constexpr int modifiers = rf_compute_modifiers( J );
};

} // namespace detail

template<class T>
requires std::is_class_v<T> || std::is_union_v<T>
constexpr auto boost_base_descriptor_fn( T** )
-> [: detail::rf_as_list( ^^detail::rf_base_descriptor, bases_of( ^^T, std::meta::access_context::unchecked() ) ) :]
{
    return {};
}

} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_HAS_REFLECTION)

#endif // #ifndef BOOST_DESCRIBE_DETAIL_RF_BASES_HPP_INCLUDED
