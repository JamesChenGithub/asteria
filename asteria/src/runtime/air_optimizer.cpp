// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#include "../precompiled.hpp"
#include "air_optimizer.hpp"
#include "analytic_context.hpp"
#include "instantiated_function.hpp"
#include "enums.hpp"
#include "../compiler/statement.hpp"
#include "../compiler/expression_unit.hpp"
#include "../util.hpp"

namespace asteria {

AIR_Optimizer::
~AIR_Optimizer()
  {
  }

AIR_Optimizer&
AIR_Optimizer::
reload(Abstract_Context* ctx_opt, const cow_vector<phsh_string>& params,
       const cow_vector<Statement>& stmts)
  {
    this->m_code.clear();
    this->m_params = params;

    // Generate code for all statements.
    Analytic_Context ctx_func(Analytic_Context::M_function(),
                              ctx_opt, this->m_params);
    for(size_t i = 0;  i < stmts.size();  ++i) {
      auto qnext = stmts.ptr(i + 1);
      bool rvoid = !qnext || qnext->is_empty_return();
      stmts[i].generate_code(this->m_code, nullptr, ctx_func, this->m_opts,
                             rvoid ? ptc_aware_void : ptc_aware_none);
    }

    // TODO: Insert optimization passes
    return *this;
  }

AIR_Optimizer&
AIR_Optimizer::
rebind(Abstract_Context* ctx_opt, const cow_vector<phsh_string>& params,
       const cow_vector<AIR_Node>& code)
  {
    this->m_code = code;
    this->m_params = params;

    // Rebind all nodes recursively.
    // Don't trigger copy-on-write unless a node needs rewriting.
    Analytic_Context ctx_func(Analytic_Context::M_function(),
                              ctx_opt, this->m_params);
    for(size_t i = 0;  i < code.size();  ++i) {
      auto qnode = code.at(i).rebind_opt(ctx_func);
      if(!qnode)
        continue;
      this->m_code.mut(i) = ::std::move(*qnode);
    }

    // TODO: Insert optimization passes
    return *this;
  }

cow_function
AIR_Optimizer::
create_function(const Source_Location& sloc, const cow_string& name)
  {
    // Compose the function signature.
    // We only do this if `name` really looks like a function name.
    cow_string func = name;
    if(is_cctype(name.front(), cctype_namei) && (name.back() != ')')) {
      func << '(';
      if(this->m_params.size()) {
        func << this->m_params[0];
        for(size_t k = 1;  k != this->m_params.size();  ++k)
          func << ", " << this->m_params[k];
      }
      func << ')';
    }

    // Instantiate the function.
    return ::rocket::make_refcnt<Instantiated_Function>(this->m_params,
               ::rocket::make_refcnt<Variadic_Arguer>(sloc, ::std::move(func)),
               this->m_code);
  }

}  // namespace asteria
