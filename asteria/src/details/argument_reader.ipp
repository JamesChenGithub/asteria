// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_RUNTIME_ARGUMENT_READER_HPP_
#  error Please include <asteria/runtime/argument_reader.hpp> instead.
#endif

namespace asteria {
namespace details_argument_reader {

// This struct records all parameters of an overload.
// It can be copied elsewhere and back; any further operations will
// resume from that point.
struct State
  {
    cow_string history;
    uint32_t nparams = 0;
    bool finished = false;
    bool succeeded = false;
  };

}  // namespace details_argument_reader
}  // namespace asteria
