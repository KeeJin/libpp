#ifndef CORE_ERROR_TYPES_HPP
#define CORE_ERROR_TYPES_HPP

#include <stdexcept>

namespace libpp_core {
class InvalidBoundError : public std::invalid_argument {
 public:
  InvalidBoundError(const std::string& message)
      : std::invalid_argument(message) {}
};

class OutOfBoundError : public std::out_of_range {
 public:
  OutOfBoundError(const std::string& message) : std::out_of_range(message) {}
};

// class FooException : public std::exception {
//  public:
//   const char* what() const noexcept override { return "Foo exception"; }
// };

}  // namespace libpp_core

#endif /* CORE_ERROR_TYPES_HPP */
