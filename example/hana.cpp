// Copyright 2022 Denis Mikhailov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

// g++ -std=c++17 -Iinclude example/hana.cpp -o example/hana

#include <boost/hana/accessors.hpp>
#include <boost/hana/assert.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/not_equal.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/tuple.hpp>
#include <string>

#include <type_traits>
#include <boost/describe.hpp>

namespace boost { namespace hana {
    namespace adapt_describe_detail {
        template <typename Memptr, Memptr ptr>
        struct member_ptr {
            template <typename T>
            constexpr decltype(auto) operator()(T&& t) const
            { return static_cast<T&&>(t).*ptr; }
        };

        constexpr std::size_t strlen(char const* s) {
            std::size_t n = 0;
            while (*s++ != '\0')
                ++n;
            return n;
        }

        template <class D, std::size_t ...i>
        constexpr auto prepare_member_name_impl(std::index_sequence<i...>) {
            return hana::string_c< D::name[i]... >;
        }

        template <class D>
        constexpr auto prepare_member_name() {
            constexpr std::size_t len = strlen(D::name);
            return prepare_member_name_impl<D>(std::make_index_sequence<len>{});
        }

        template<template<class...> class L, class... D>
        constexpr auto hana_accessors_apply_impl(L<D...>)
        {
            return ::boost::hana::make_tuple(
                ::boost::hana::make_pair(
                    prepare_member_name<D>(),
                    member_ptr<decltype(D::pointer), D::pointer>{}
                ) ...
            );
        }
    }
    template <class T>
    struct accessors_impl<T, when<boost::describe::has_describe_bases<T>::value &&
                                  boost::describe::has_describe_members<T>::value &&
                                  !std::is_union<T>::value> >
    {
        static BOOST_HANA_CONSTEXPR_LAMBDA auto apply()
        {
            using Dm = boost::describe::describe_members<T,
                boost::describe::mod_public | boost::describe::mod_inherited>;
            return adapt_describe_detail::hana_accessors_apply_impl(Dm());
        }
    };
}}




namespace hana = boost::hana;
struct PersonName {
    std::string name;
};
BOOST_DESCRIBE_STRUCT(PersonName, (), (name))

struct PersonAge {
    int age;
};
BOOST_DESCRIBE_STRUCT(PersonAge, (), (age))

struct Person : PersonName, PersonAge {
};
BOOST_DESCRIBE_STRUCT(Person, (PersonName, PersonAge), ())


// The member names are hana::strings:
auto names = hana::transform(hana::accessors<Person>(), hana::first);
BOOST_HANA_CONSTANT_CHECK(
    names == hana::make_tuple(BOOST_HANA_STRING("name"), BOOST_HANA_STRING("age"))
);

int main() {
    Person john{"John", 30}, bob{"Bob", 40};
    BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
    BOOST_HANA_RUNTIME_CHECK(hana::not_equal(john, bob));
    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("name")) == hana::just("John"));
    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("age")) == hana::just(30));
    BOOST_HANA_CONSTANT_CHECK(hana::find(john, BOOST_HANA_STRING("foo")) == hana::nothing);
    BOOST_HANA_RUNTIME_CHECK(hana::to_tuple(john) == hana::make_tuple(
        hana::make_pair(BOOST_HANA_STRING("name"), "John"),
        hana::make_pair(BOOST_HANA_STRING("age"), 30)
    ));
    BOOST_HANA_RUNTIME_CHECK(hana::to_map(john) == hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("name"), "John"),
        hana::make_pair(BOOST_HANA_STRING("age"), 30)
    ));
}
