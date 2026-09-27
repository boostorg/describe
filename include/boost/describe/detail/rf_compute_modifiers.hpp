#ifndef BOOST_DESCRIBE_DETAIL_RF_COMPUTE_MODIFIERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_RF_COMPUTE_MODIFIERS_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>
#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <meta>

namespace boost
{
namespace describe
{
namespace detail
{

consteval int rf_compute_modifiers( std::meta::info J )
{
    int m = 0;

    if( is_public(J) ) m |= mod_public;
    if( is_protected(J) ) m |= mod_protected;
    if( is_private(J) ) m |= mod_private;

    if( is_static_member(J) ) m |= mod_static;
    if( is_function(J) ) m |= mod_function;
    if( is_virtual(J) ) m |= mod_virtual;

    return m;
}

} // namespace detail
} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_HAS_REFLECTION)

#endif // #ifndef BOOST_DESCRIBE_DETAIL_RF_COMPUTE_MODIFIERS_HPP_INCLUDED
