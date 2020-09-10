#ifndef BOOST_DESCRIBE_DETAIL_BASE_CLASSES_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_BASE_CLASSES_HPP_INCLUDED

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

// is_public_base_of
template<class T, class U> using is_public_base_of = std::is_convertible<U*, T*>;

// is_virtual_base_of
template<class T, class U, class = void> struct can_cast: std::false_type {};
template<class T, class U> struct can_cast<T, U, decltype((void)(U*)(T*)0)>: std::true_type {};

template<class T, class U> using is_virtual_base_of =
    std::integral_constant<bool, can_cast<U, T>::value && !can_cast<T, U>::value>;

// base_class_modifiers
template<class C, class B> constexpr unsigned base_class_modifiers() noexcept
{
    return (is_public_base_of<B, C>::value? mod_public: mod_private) | (is_virtual_base_of<B, C>::value? mod_virtual: 0);
}

// base_class_descriptor
template<class C, class B> struct base_class_descriptor
{
    static_assert( std::is_base_of<B, C>::value, "A type listed as a base is not one" );

    using type = B;
    static constexpr unsigned modifiers = base_class_modifiers<C, B>();
};

template<class C, class B> constexpr unsigned base_class_descriptor<C, B>::modifiers;

template<class... T> auto base_class_descriptor_fn_impl( int, T... )
{
    return list<T...>();
}

#define BOOST_DESCRIBE_BASE_CLASS_IMPL(C, B) , boost::describe::detail::base_class_descriptor<C, B>()

#if defined(_MSC_VER) && !defined(__clang__)

#define BOOST_DESCRIBE_BASE_CLASSES(C, ...) inline auto _base_class_descriptor_fn( C * ) \
{ return boost::describe::detail::base_class_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_BASE_CLASS_IMPL, C, __VA_ARGS__) ); }

#else

#define BOOST_DESCRIBE_BASE_CLASSES(C, ...) inline auto _base_class_descriptor_fn( C * ) \
{ return boost::describe::detail::base_class_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_BASE_CLASS_IMPL, C, ##__VA_ARGS__) ); }

#endif

} // namespace detail
} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_DETAIL_BASE_CLASSES_HPP_INCLUDED
