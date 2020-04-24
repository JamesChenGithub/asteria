// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "../precompiled.hpp"
#include "abstract_hooks.hpp"
#include "../utilities.hpp"

namespace Asteria {

Abstract_Hooks::
~Abstract_Hooks()
  {
  }

void
Abstract_Hooks::
on_variable_declare(const Source_Location& /*sloc*/, const phsh_string& /*name*/)
  {
  }

void
Abstract_Hooks::
on_function_call(const Source_Location& /*sloc*/, const cow_function& /*target*/)
  {
  }

void
Abstract_Hooks::
on_function_return(const Source_Location& /*sloc*/, const Reference& /*result*/)
  {
  }

void
Abstract_Hooks::
on_function_except(const Source_Location& /*sloc*/, const Runtime_Error& /*except*/)
  {
  }

void
Abstract_Hooks::
on_single_step_trap(const Source_Location& /*sloc*/, Executive_Context* /*ctx_opt*/)
  {
  }

}  // namespace Asteria
