// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_RUNTIME_ARGUMENT_READER_HPP_
#define ASTERIA_RUNTIME_ARGUMENT_READER_HPP_

#include "../fwd.hpp"
#include "reference.hpp"
#include "../details/argument_reader.ipp"

namespace asteria {

class Argument_Reader
  {
  private:
    cow_string m_name;
    const cow_vector<Reference>* m_args;

    details_argument_reader::State m_state;
    cow_vector<details_argument_reader::State> m_saved_states;
    cow_string m_arg_lists;

  public:
    Argument_Reader(const cow_string& name, ref<const cow_vector<Reference>> args)
    noexcept
      : m_name(name), m_args(args.ptr())
      { }

    ASTERIA_NONCOPYABLE_DESTRUCTOR(Argument_Reader);

  public:
    const cow_string&
    name()
    const noexcept
      { return this->m_name;  }

    // These functions access `m_saved_states`.
    // Under a number of circumstances, function overloads share a common initial
    // parameter sequence. We allow saving and loading parser states to eliminate
    // the overhead of re-parsing this sequence.
    // The `index` argument is a subscript of `m_saved_states`, which is resized
    // by `save_state()` as necessary.
    Argument_Reader&
    load_state(size_t index);

    Argument_Reader&
    save_state(size_t index);

    // Start an overload. Effectively, this function clears `m_state`.
    Argument_Reader&
    start_overload();

    // Gets an optional argument. The argument may be of the desired type or null.
    Argument_Reader&
    opt_reference(Reference& arg);

    Argument_Reader&
    opt_value(Value& arg);

    Argument_Reader&
    opt_boolean(Opt_boolean& arg);

    Argument_Reader&
    opt_integer(Opt_integer& arg);

    Argument_Reader&
    opt_real(Opt_real& arg);

    Argument_Reader&
    opt_string(Opt_string& arg);

    Argument_Reader&
    opt_opaque(Opt_opaque& arg);

    Argument_Reader&
    opt_function(Opt_function& arg);

    Argument_Reader&
    opt_array(Opt_array& arg);

    Argument_Reader&
    opt_object(Opt_object& arg);

    // Gets a required argument. The argument must be of the desired type.
    Argument_Reader&
    req_boolean(V_boolean& arg);

    Argument_Reader&
    req_integer(V_integer& arg);

    Argument_Reader&
    req_real(V_real& arg);

    Argument_Reader&
    req_string(V_string& arg);

    Argument_Reader&
    req_opaque(V_opaque& arg);

    Argument_Reader&
    req_function(V_function& arg);

    Argument_Reader&
    req_array(V_array& arg);

    Argument_Reader&
    req_object(V_object& arg);

    // Finish an overload. The return value indicates whether the overload has
    // been accepted. The second and third functions accept variadic arguments.
    bool
    finish_overload();

    bool
    finish_overload(cow_vector<Reference>& vargs);

    bool
    finish_overload(cow_vector<Value>& vargs);

    // This function throws an exception containing a message composed from all
    // overloads that have been tested so far.
    [[noreturn]]
    void
    throw_no_matching_function_call()
    const;
  };

}  // namespace asteria

#endif
