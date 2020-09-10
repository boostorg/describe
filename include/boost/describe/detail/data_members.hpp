#ifndef BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>
#include <boost/describe/detail/pp_for_each.hpp>
#include <boost/describe/detail/descriptor_list.hpp>
#include <type_traits>

namespace boost
{
namespace describe
{
namespace detail
{

template<class D> struct data_member_descriptor
{
    static constexpr decltype(D::pointer()) pointer = D::pointer();
    static constexpr decltype(D::name()) name = D::name();
    static constexpr decltype(D::modifiers()) modifiers = D::modifiers();
};

template<class D> constexpr decltype(D::pointer()) data_member_descriptor<D>::pointer;
template<class D> constexpr decltype(D::name()) data_member_descriptor<D>::name;
template<class D> constexpr decltype(D::modifiers()) data_member_descriptor<D>::modifiers;

template<class... T> auto data_member_descriptor_fn_impl( int, T... )
{
    return descriptor_list<data_member_descriptor<T>...>();
}

#define BOOST_DESCRIBE_DATA_MEMBER_IMPL(C, m) , []{ struct D { \
    static constexpr auto pointer() noexcept { return &C::m; } \
    static constexpr auto name() noexcept { return #m; } \
    static constexpr auto modifiers() noexcept { return boost::describe::mod_public; } \
    }; return D(); }()

#if defined(_MSC_VER) && !defined(__clang__)

#define BOOST_DESCRIBE_PUBLIC_DATA_MEMBERS(C, ...) inline auto _data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, __VA_ARGS__) ); }

#else

#define BOOST_DESCRIBE_PUBLIC_DATA_MEMBERS(C, ...) inline auto _data_member_descriptor_fn( C * ) \
{ return boost::describe::detail::data_member_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_DATA_MEMBER_IMPL, C, ##__VA_ARGS__) ); }

#endif

} // namespace detail
} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_DETAIL_DATA_MEMBERS_HPP_INCLUDED
