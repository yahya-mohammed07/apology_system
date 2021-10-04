#include <string_view>
#include <unordered_map>
#include <iostream>
#include <cassert>

namespace kraken::err_codes {
  constexpr int big_arg {99};
  constexpr int neg_arg {-1};
}

using namespace kraken;

#if __cplusplus >= 202002L

#if defined(_MSC_VER)
  #include <source_location>
  using src_loc = const std::source_location;
#endif

#if defined(__clang__) || defined(__GNUG__)
  #include <experimental/source_location>
  using src_loc = const std::experimental::source_location;
#endif

struct error {
  std::string_view func_name{};
  int err_code{};
  std::uint32_t line{};
};

inline const
std::unordered_map<int, std::string_view> apologies
{
  { err_codes::neg_arg, " -A negative number was given." },
  { err_codes::big_arg,  " -A too big number was given." },
};

constexpr
auto Apology = [](auto apology)
  -> bool
{
  const auto &[function_name, err_code, line] = apology();
  if ( apologies.find(err_code) == apologies.end() ) {
    std::cerr << "-Err_code not defined.\n";
    throw(1);
  }
  std::cerr << "[ -An error occurred inside: `" << function_name
            << "` at line: " << line
            << " and the reason was: `"
            << apologies.at(err_code) << "` ]\n";
  throw(1); // is it ok?
  // or assert(false) maybe?
};

#endif
