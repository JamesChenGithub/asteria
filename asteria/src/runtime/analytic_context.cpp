// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "../precompiled.hpp"
#include "analytic_context.hpp"
#include "../utilities.hpp"

namespace Asteria {

Analytic_Context::~Analytic_Context()
  {
  }

void Analytic_Context::do_prepare_function(const cow_vector<phsh_string>& params)
  {
    // Set parameters, which are local references.
    for(size_t i = 0;  i < params.size();  ++i) {
      const auto& name = params.at(i);
      if(name.empty()) {
        continue;
      }
      if(name == "...") {
        // Nothing is set for the variadic placeholder, but the parameter list terminates here.
        ROCKET_ASSERT(i == params.size() - 1);
        break;
      }
      if(name.rdstr().starts_with("__")) {
        ASTERIA_THROW("reserved name not declarable as parameter (name `", name, "`)");
      }
      // Its contents are out of interest.
      this->open_named_reference(name) /*= Reference_root::S_void()*/;
    }
    // Set pre-defined references.
    // N.B. If you have ever changed these, remember to update 'executive_context.cpp' as well.
    this->open_named_reference(::rocket::sref("__varg")) /*= Reference_root::S_void()*/;
    this->open_named_reference(::rocket::sref("__this")) /*= Reference_root::S_void()*/;
    this->open_named_reference(::rocket::sref("__func")) /*= Reference_root::S_void()*/;
  }

bool Analytic_Context::do_is_analytic() const noexcept
  {
    return this->is_analytic();
  }

const Abstract_Context* Analytic_Context::do_get_parent_opt() const noexcept
  {
    return this->get_parent_opt();
  }

Reference* Analytic_Context::do_lazy_lookup_opt(const phsh_string& /*name*/)
  {
    return nullptr;
  }

}  // namespace Asteria
