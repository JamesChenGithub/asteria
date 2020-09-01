// This file is part of Asteri, 13a.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "utilities.hpp"
#include "../src/simple_script.hpp"
#include "../src/runtime/global_context.hpp"

using namespace asteria;

int main()
  {
    ::rocket::tinybuf_str cbuf;
    cbuf.set_string(::rocket::sref(
      R"__(
        var one = 1;
        const two = 2;
        func fib(n) {
          return n <= one ? n : fib(n - one) + fib(n - two);
        }
        var con = { };
        con["value"] = fib(11);
        con["const"] = one;
        return con.value + con.const;
      )__"), tinybuf::open_read);
    Simple_Script code;
    code.reload(cbuf, ::rocket::sref("<test>"), 14);
    Global_Context global;
    auto res = code.execute(global);
    ASTERIA_TEST_CHECK(res.read().as_integer() == 90);
  }
