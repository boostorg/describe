#ifndef BOOST_DESCRIBE_DETAIL_RF_AS_LIST_HPP_INCLUDED
#define BOOST_DESCRIBE_DETAIL_RF_AS_LIST_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/list.hpp>
#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_HAS_REFLECTION)

#include <meta>
#include <vector>

namespace boost
{
namespace describe
{
namespace detail
{

template<class R>
consteval auto rf_as_list( std::meta::info desc, R range )
{
    std::vector<std::meta::info> args;

    for( auto r: range )
    {
        args.push_back( substitute( desc, { reflect_constant( r ) } ) );
    }

    return substitute( ^^list, args );
}

} // namespace detail
} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_HAS_REFLECTION)

#endif // #ifndef BOOST_DESCRIBE_DETAIL_RF_AS_LIST_HPP_INCLUDED
