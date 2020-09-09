#ifndef BOOST_DESCRIBE_ENUM_HPP_INCLUDED
#define BOOST_DESCRIBE_ENUM_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/pp_for_each.hpp>
#include <boost/describe/detail/descriptor_list.hpp>

namespace boost
{
namespace describe
{
namespace detail
{

template<class D> struct enum_descriptor
{
    // can't use auto here because of the need to supply the definition below
    static constexpr decltype(D::value()) value = D::value();
    static constexpr auto name = D::name();
};

// GCC requires this definition
template<class D> constexpr decltype(D::value()) enum_descriptor<D>::value;

template<class... T> auto enum_descriptor_fn_impl( int, T... )
{
    return descriptor_list<enum_descriptor<T>...>();
}

#define BOOST_DESCRIBE_ENUM_IMPL(E, e) , []{ struct D { \
    static constexpr auto value() noexcept { return e; } \
    static constexpr auto name() noexcept { return #e; } }; return D(); }()

#define BOOST_DESCRIBE_ENUM_CLASS_IMPL(E, e) , []{ struct D { \
    static constexpr auto value() noexcept { return E::e; } \
    static constexpr auto name() noexcept { return #e; } }; return D(); }()

} // namespace detail

#define BOOST_DESCRIBE_ENUM(E, ...) inline auto _enum_descriptor_fn( E* ) \
{ return boost::describe::detail::enum_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_ENUM_IMPL, E, __VA_ARGS__) ); }

#define BOOST_DESCRIBE_ENUM_CLASS(E, ...) inline auto _enum_descriptor_fn( E* ) \
{ return boost::describe::detail::enum_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_ENUM_CLASS_IMPL, E, __VA_ARGS__) ); }

#define BOOST_DEFINE_ENUM(E, ...) enum E { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)
#define BOOST_DEFINE_ENUM_CLASS(E, ...) enum class E { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM_CLASS(E, __VA_ARGS__)

#define BOOST_DEFINE_FIXED_ENUM(E, Base, ...) enum E: Base { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM(E, __VA_ARGS__)
#define BOOST_DEFINE_FIXED_ENUM_CLASS(E, Base, ...) enum class E: Base { __VA_ARGS__ }; BOOST_DESCRIBE_ENUM_CLASS(E, __VA_ARGS__)

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_ENUM_HPP_INCLUDED
