#ifndef BOOST_DESCRIBE_MODIFIERS_HPP_INCLUDED
#define BOOST_DESCRIBE_MODIFIERS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

namespace boost
{
namespace describe
{

constexpr unsigned mod_public = 1;
constexpr unsigned mod_protected = 2;
constexpr unsigned mod_private = 4;
constexpr unsigned mod_virtual = 8;
constexpr unsigned mod_static = 16;

//

constexpr unsigned mod_any_access = mod_public | mod_protected | mod_private;

} // namespace describe
} // namespace boost

#endif // #ifndef BOOST_DESCRIBE_MODIFIERS_HPP_INCLUDED
