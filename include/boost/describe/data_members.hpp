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

template<class T> using _describe_public_data_members = decltype( _public_data_member_descriptor_fn( static_cast<T*>(0) ) );
template<class T> using _describe_private_data_members = decltype( _private_data_member_descriptor_fn( static_cast<T*>(0) ) );
template<class T> using _describe_data_members = mp11::mp_append<_describe_public_data_members<T>, _describe_private_data_members<T>>;

template<unsigned M> struct data_member_filter
{
    template<class T> using fn = mp11::mp_bool< ( M & mod_any_access & T::modifiers ) != 0 >;
};

} // namespace detail

template<class T, unsigned M> using describe_data_members = mp11::mp_copy_if_q<detail::_describe_data_members<T>, detail::data_member_filter<M>>;

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED
