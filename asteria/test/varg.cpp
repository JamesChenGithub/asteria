// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "util.hpp"
#include "../src/simple_script.hpp"
#include "../src/runtime/global_context.hpp"

using namespace asteria;

int main()
  {
    Simple_Script code;
    code.reload_string(
      ::rocket::sref(__FILE__), __LINE__, ::rocket::sref(R"__(
///////////////////////////////////////////////////////////////////////////////

        func binary(a, b, ...) {
          var narg = __varg();
          var arg = __varg(a);
          return [ narg, arg ];
        }
        return [
          binary(1),           // [ 0, null ]
          binary(1,2),         // [ 0, null ]
          binary(1,2,3),       // [ 1, null ]
          binary(1,2,3,4),     // [ 2, 4 ]
          binary(1,2,3,4,5),   // [ 3, 4 ]
        ];

///////////////////////////////////////////////////////////////////////////////
      )__"));
    Global_Context global;
    auto res = code.execute(global);

    const auto& array = res.dereference_readonly().as_array();
    ASTERIA_TEST_CHECK(array.size() == 5);
    ASTERIA_TEST_CHECK(array.at(0).as_array().at(0).as_integer() == 0);
    ASTERIA_TEST_CHECK(array.at(0).as_array().at(1).is_null());
    ASTERIA_TEST_CHECK(array.at(1).as_array().at(0).as_integer() == 0);
    ASTERIA_TEST_CHECK(array.at(1).as_array().at(1).is_null());
    ASTERIA_TEST_CHECK(array.at(2).as_array().at(0).as_integer() == 1);
    ASTERIA_TEST_CHECK(array.at(2).as_array().at(1).is_null());
    ASTERIA_TEST_CHECK(array.at(3).as_array().at(0).as_integer() == 2);
    ASTERIA_TEST_CHECK(array.at(3).as_array().at(1).as_integer() == 4);
    ASTERIA_TEST_CHECK(array.at(4).as_array().at(0).as_integer() == 3);
    ASTERIA_TEST_CHECK(array.at(4).as_array().at(1).as_integer() == 4);

    code.reload_string(
      ::rocket::sref(__FILE__), __LINE__, ::rocket::sref(R"__(
///////////////////////////////////////////////////////////////////////////////

        return __varg('meow', 42, true);

///////////////////////////////////////////////////////////////////////////////
      )__"));
    ASTERIA_TEST_CHECK_CATCH(code.execute(global));
  }
