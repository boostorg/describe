// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/members.hpp>
#include <boost/utility/string_view.hpp>
#include <utility>

#if !defined(BOOST_DESCRIBE_CXX11)

#include <boost/config/pragma_message.hpp>

BOOST_PRAGMA_MESSAGE("Skipping test because C++11 is not available")
int main() {}

#else

int main()
{
    using boost::describe::has_describe_members;

    constexpr bool r1 = has_describe_members< std::pair<int const, int> >::value;
    (void)r1;

    constexpr bool r2 = has_describe_members< boost::string_view >::value;
    (void)r2;
}

#endif // !defined(BOOST_DESCRIBE_CXX11)
