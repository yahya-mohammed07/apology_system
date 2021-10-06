#include <iostream>
#include "apology.hpp"

constexpr
auto factorial(int val, src_loc src = src_loc::current()) -> int
{
  if ( val < 0 ) {
    Apology( [&] { return error{ src.file_name(), src.function_name(),
                                  err_codes::neg_arg, src.line() }; } );
  } else if ( val > 20 ) {
    Apology( [&] { return error{ src.file_name(), src.function_name(),
                                  err_codes::big_arg, src.line() }; } );
  }
  if ( val <= 1) return 1;
  return val * factorial(val - 1, src);
}

auto main() -> int
{
  std::cout << factorial(4) << '\n';
  std::cout << factorial(1) << '\n';
  std::cout << factorial(3) << '\n';
  std::cout << factorial(21) << '\n'; // line 21
  std::cout << factorial(-1) << '\n';
}
