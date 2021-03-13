#ifndef BOOST_DESCRIBE_ENUM_HPP_INCLUDED
#define BOOST_DESCRIBE_ENUM_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/pp_for_each.hpp>
#include <boost/describe/detail/list.hpp>
#include <boost/describe/detail/config.hpp>

#if !defined(BOOST_DESCRIBE_CXX14)

#define BOOST_DESCRIBE_ENUM(E, ...)

#else

namespace boost
{
namespace describe
{
namespace detail
{

template<class D> struct enum_descriptor
{
    // can't use auto here because of the need to supply the definitions below
    static constexpr decltype(D::value()) value = D::value();
    static constexpr decltype(D::name()) name = D::name();
};

// GCC requires these definitions
template<class D> constexpr decltype(D::value()) enum_descriptor<D>::value;
template<class D> constexpr decltype(D::name()) enum_descriptor<D>::name;

template<class... T> auto enum_descriptor_fn_impl( int, T... )
{
    return list<enum_descriptor<T>...>();
}

#define BOOST_DESCRIBE_ENUM_BEGIN(E) \
    inline auto boost_enum_descriptor_fn( E* ) \
    { return boost::describe::detail::enum_descriptor_fn_impl( 0

#define BOOST_DESCRIBE_ENUM_ENTRY(E, e) , []{ struct D { \
    static constexpr auto value() noexcept { return E::e; } \
    static constexpr auto name() noexcept { return #e; } }; return D(); }()

#define BOOST_DESCRIBE_ENUM_END(E) ); }

} // namespace detail

#define BOOST_DESCRIBE_ENUM(E, ...) \
    BOOST_DESCRIBE_ENUM_BEGIN(E) \
    BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_ENUM_ENTRY, E, __VA_ARGS__) \
    BOOST_DESCRIBE_ENUM_END(E)

} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_CXX14)

#define BOOST_DEFINE_ENUM(E, ...) enum E { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)
#define BOOST_DEFINE_ENUM_CLASS(E, ...) enum class E { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)

#define BOOST_DEFINE_FIXED_ENUM(E, Base, ...) enum E: Base { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)
#define BOOST_DEFINE_FIXED_ENUM_CLASS(E, Base, ...) enum class E: Base { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)

#endif // #ifndef BOOST_DESCRIBE_ENUM_HPP_INCLUDED
