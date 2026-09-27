#ifndef BOOST_DESCRIBE_DETAIL_RF_ENUM_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_RF_ENUM_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/describe/detail/rf_as_list.hpp>
#include <meta>

namespace boost
{
namespace describe
{
namespace detail
{

template<auto J> struct rf_enum_descriptor
{
    static constexpr char const* name = identifier_of( J ).data();
    static constexpr [: type_of( J ) :] value = [: J :];
};

} // namespace detail

template<class E>
requires std::is_enum_v<E>
constexpr auto boost_enum_descriptor_fn( E** )
-> [: detail::rf_as_list( ^^detail::rf_enum_descriptor, enumerators_of( ^^E ) ) :]
{
    return {};
}

} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_HAS_REFLECTION)

#endif // #ifndef BOOST_DESCRIBE_DETAIL_RF_ENUM_HPP_INCLUDED
