//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_DESCRIBE_DETAIL_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_CONSTRUCTOR_HPP_INCLUDED

#include <boost/describe/modifiers.hpp>
#include <type_traits>

namespace boost
{
namespace describe
{
namespace detail
{

template<class S>
struct ctor_descriptor;

template<class C, class ... Args>
struct ctor_descriptor<C(Args...)>
{
    using signature = C(Args...);
    static constexpr unsigned modifiers = mod_constructor;
    static constexpr bool is_noexcept = std::is_nothrow_constructible<C, Args...>::value;
    static constexpr bool is_trivial = std::is_trivially_constructible<C, Args...>::value;

    constexpr static C* construct_at(C* p, Args... args)
    {
        return new (p) C(static_cast<Args>(args)...);
    }
};

template<class... T> auto ctor_descriptor_fn_impl( int, T... )
{
    return list<T...>();
}

#define BOOST_DESCRIBE_CTOR_IMPL(C, B) , boost::describe::detail::ctor_descriptor<C B>()


#if defined(_MSC_VER) && !defined(__clang__)

#define BOOST_DESCRIBE_CTORS(C, ...) inline auto boost_ctor_descriptor_fn( C** ) \
{ return boost::describe::detail::ctor_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_CTOR_IMPL, C, __VA_ARGS__) ); }

#else

#define BOOST_DESCRIBE_CTORS(C, ...) inline auto boost_ctor_descriptor_fn( C** ) \
{ return boost::describe::detail::ctor_descriptor_fn_impl( 0 BOOST_DESCRIBE_PP_FOR_EACH(BOOST_DESCRIBE_CTOR_IMPL, C, ##__VA_ARGS__) ); }

#endif

}
}
}

#endif //BOOST_DESCRIBE_DETAIL_CONSTRUCTOR_HPP_INCLUDED
