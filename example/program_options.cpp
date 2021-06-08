
// Copyright 2021 Samuel Debionne
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

// g++ -std=c++14 -Iinclude example/program_options.cpp -o example/program_options /usr/lib/libboost_program_options.a

#define _CRT_SECURE_NO_WARNINGS

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <boost/program_options.hpp>

#include <type_traits>
#include <iostream>

namespace app
{

enum class log_level {
   fatal,
   error,
   warning,
   trace
};

BOOST_DESCRIBE_ENUM(log_level, fatal, error, warning, trace)

template <typename E, typename = std::enable_if_t<std::is_enum<E>::value>>
std::ostream& operator<<(std::ostream& os, E e)
{
  boost::mp11::mp_for_each< boost::describe::describe_enumerators<E> >([&](auto D) {
      if( e == D.value ) os << D.name;
  });

  return os;
}

// Generic program_options custom validator for (described) enums
template <
    typename E,
    typename Ed = boost::describe::describe_enumerators<E>,
    typename = std::enable_if_t<
        std::is_enum<E>::value && !boost::mp11::mp_empty<Ed>::value
    >
>
void validate(boost::any& v,
              const std::vector<std::string>& values,
              E* target_type, int)
{
    using namespace boost::program_options;

    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const std::string& name = validators::get_single_string(values);

    // Convert string to enum
    bool found = false;
    E r = {};

    boost::mp11::mp_for_each<Ed>([&](auto D){
        if( !found && std::strcmp( D.name, name.c_str() ) == 0 )
        {
            found = true;
            r = D.value;
        }
    });

    if (found)
      v = boost::any(r);
    else
      throw validation_error(validation_error::invalid_option_value);
}

} //namespace app

int main(int argc, char *argv[])
{
  namespace po = boost::program_options;

  app::log_level lvl;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("log-level", po::value<app::log_level>(&lvl), "set log severity level")
  ;
  
  try {
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);

      if (vm.count("help")) {
          std::cout << desc << "\n";
          return 1;
      }

      if (vm.count("log-level")) {
          std::cout << "Log level was set to " << lvl << ".\n";
      } else {
          std::cout << "Log level was not set.\n";
      }
  }
  catch (std::exception& ex)
  {
      std::cerr << "ERROR: " << ex.what() << std::endl;
  }  
}
