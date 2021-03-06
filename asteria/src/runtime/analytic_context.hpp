// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_RUNTIME_ANALYTIC_CONTEXT_HPP_
#define ASTERIA_RUNTIME_ANALYTIC_CONTEXT_HPP_

#include "../fwd.hpp"
#include "abstract_context.hpp"

namespace asteria {

class Analytic_Context
  : public Abstract_Context
  {
  private:
    Abstract_Context* m_parent_opt;

  public:
    // A plain context must have a parent context.
    // Its parent context shall outlast itself.
    Analytic_Context(M_plain, Abstract_Context& parent)
      : m_parent_opt(::std::addressof(parent))
      { }

    // A function context may have a parent.
    // Names found in ancestor contexts will be bound into the
    // instantiated function object.
    Analytic_Context(M_function, Abstract_Context* parent_opt,
                     const cow_vector<phsh_string>& params);

    ASTERIA_NONCOPYABLE_DESTRUCTOR(Analytic_Context);

  protected:
    bool
    do_is_analytic()
      const noexcept final
      { return this->is_analytic();  }

    Abstract_Context*
    do_get_parent_opt()
      const noexcept override
      { return this->get_parent_opt();  }

    Reference*
    do_lazy_lookup_opt(const phsh_string& /*name*/)
      override
      { return nullptr;  }

  public:
    bool
    is_analytic()
      const noexcept
      { return true;  }

    Abstract_Context*
    get_parent_opt()
      const noexcept
      { return this->m_parent_opt;  }
  };

}  // namespace asteria

#endif
