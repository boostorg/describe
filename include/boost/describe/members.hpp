#ifndef BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>
#include <boost/mp11/algorithm.hpp>

namespace boost
{
namespace describe
{
namespace detail
{

template<class T> using _describe_public_members = decltype( _public_member_descriptor_fn( static_cast<T*>(0) ) );
template<class T> using _describe_protected_members = decltype( _protected_member_descriptor_fn( static_cast<T*>(0) ) );
template<class T> using _describe_private_members = decltype( _private_member_descriptor_fn( static_cast<T*>(0) ) );
template<class T> using _describe_members = mp11::mp_append<_describe_public_members<T>, _describe_protected_members<T>, _describe_private_members<T>>;

template<unsigned M> struct member_filter
{
    template<class T> using fn = mp11::mp_bool< ( M & mod_any_access & T::modifiers ) != 0 && ( M & mod_static ) == ( T::modifiers & mod_static ) && ( M & mod_function ) == ( T::modifiers & mod_function ) >;
};

} // namespace detail

template<class T, unsigned M> using describe_members = mp11::mp_copy_if_q<detail::_describe_members<T>, detail::member_filter<M>>;

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED
