#ifndef BOOST_DESCRIBE_DETAIL_RF_MEMBERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_RF_MEMBERS_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <boost/describe/detail/rf_as_list.hpp>
#include <boost/describe/detail/rf_compute_modifiers.hpp>
#include <meta>
#include <vector>
#include <string>
#include <algorithm>

namespace boost
{
namespace describe
{
namespace detail
{

template<std::meta::info J> constexpr auto rf_pointer_of()
{
    return &[: J :];
}

consteval char const* rf_name_of( std::meta::info J )
{
    if( has_identifier( J ) )
    {
        return identifier_of( J ).data();
    }
    else if( is_operator_function( J ) )
    {
        const auto op = operator_of( J );
        const auto sym = symbol_of( op );

        std::string r( "operator" );
        if( (int)op >= 1 && (int)op <= 5 ) r += " ";
        r += sym;

        return std::define_static_string( r );
    }
    else if( is_constructor( J ) )
    {
        return rf_name_of( parent_of( J ) );
    }
    else
    {
        return "__unnamed__";
    }
}

template<auto J> struct rf_member_descriptor
{
    static constexpr char const* name = rf_name_of( J );
    static constexpr int modifiers = rf_compute_modifiers( J );

    static constexpr auto pointer = rf_pointer_of<J>();
};

consteval bool rf_skip_member( std::meta::info J )
{
    if( is_type(J) ) return true;
    if( is_template(J) ) return true;
    if( is_constructor(J) ) return true;
    if( is_destructor(J) ) return true;
    if( is_operator_function(J) ) return true;
    if( is_conversion_function(J) ) return true;

    return false;
}

consteval auto rf_members_of( std::meta::info J )
{
    std::vector<std::meta::info> v = members_of( J, std::meta::access_context::unchecked() );

    std::erase_if( v, rf_skip_member );
    return v;
}

consteval bool rf_valid_member( std::meta::info J )
{
    if( is_bit_field(J) ) return false;
    if( !has_identifier( J ) ) return false;

    return true;
}

template<class T> consteval bool rf_has_describe_members()
{
    std::meta::info J = ^^T;

    if( !is_class_type( J ) && !is_union_type( J ) ) return false;

    std::vector<std::meta::info> v = rf_members_of( J );
    return std::ranges::all_of( v, rf_valid_member );
}

} // namespace detail

template<class T>
requires (detail::rf_has_describe_members<T>())
constexpr auto boost_public_member_descriptor_fn( T** )
-> [: detail::rf_as_list( ^^detail::rf_member_descriptor, detail::rf_members_of( ^^T ) ) :]
{
    return {};
}

template<class T>
requires (detail::rf_has_describe_members<T>())
constexpr auto boost_protected_member_descriptor_fn( T** )
-> detail::list<>
{
    return {};
}

template<class T>
requires (detail::rf_has_describe_members<T>())
constexpr auto boost_private_member_descriptor_fn( T** )
-> detail::list<>
{
    return {};
}

} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_HAS_REFLECTION)

#endif // #ifndef BOOST_DESCRIBE_DETAIL_RF_MEMBERS_HPP_INCLUDED
