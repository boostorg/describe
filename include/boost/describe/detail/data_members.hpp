#ifndef BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>
#include <boost/describe/detail/pp_for_each.hpp>
#include <boost/describe/detail/list.hpp>
#include <type_traits>

namespace boost
{
namespace describe
{
namespace detail
{

template<class Pm> constexpr unsigned dm_static_modifier( Pm )
{
    return std::is_member_pointer<Pm>::value? 0: mod_static;
}

template<class D, unsigned M> struct data_member_descriptor
{
    static constexpr decltype(D::pointer()) pointer = D::pointer();
    static constexpr decltype(D::name()) name = D::name();
    static constexpr unsigned modifiers = M | dm_static_modifier( D::pointer() );
};

template<class D, unsigned M> constexpr decltype(D::pointer()) data_member_descriptor<D, M>::pointer;
template<class D, unsigned M> constexpr decltype(D::name()) data_member_descriptor<D, M>::name;
template<class D, unsigned M> constexpr unsigned data_member_descriptor<D, M>::modifiers;

template<unsigned M, class... T> auto data_member_descriptor_fn_impl( int, T... )
{
    return list<data_member_descriptor<T, M>...>();
}

#define BOOST_DESCRIBE_DATA_MEMBER_IMPL(C, m) , []{ struct D { \
    static constexpr auto pointer() noexcept { return &C::m; } \
    static constexpr auto name() noexcept { return #m; } }; return D(); }()

#if defined(_MSC_VER) && !defined(__clang__)

#define BOOST_DESCRIBE_PUBLIC_DATA_MEMBERS(C, ...) inline auto _public_data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl<boost::describe::mod_public>( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, __VA_ARGS__) ); }

#define BOOST_DESCRIBE_PRIVATE_DATA_MEMBERS(C, ...) inline auto _private_data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl<boost::describe::mod_private>( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, __VA_ARGS__) ); }

#else

#define BOOST_DESCRIBE_PUBLIC_DATA_MEMBERS(C, ...) inline auto _public_data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl<boost::describe::mod_public>( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, ##__VA_ARGS__) ); }

#define BOOST_DESCRIBE_PRIVATE_DATA_MEMBERS(C, ...) inline auto _private_data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl<boost::describe::mod_private>( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, ##__VA_ARGS__) ); }

#endif

} // namespace detail
} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED
