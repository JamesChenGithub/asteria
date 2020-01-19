// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ROCKET_UTILITIES_HPP_
#define ROCKET_UTILITIES_HPP_

// This must be the first header as it defines some macros that interact with the standard library.
#include "compiler.h"

#include <type_traits>  // so many...
#include <iterator>  // std::iterator_traits<>, std::begin(), std::end()
#include <utility>  // std::swap()
#include <memory>  // std::allocator<>, std::addressof(), std::default_delete<>
#include <new>  // placement new
#include <initializer_list>  // std::initializer_list<>
#include <limits>  // std::numeric_limits<>
#include <functional>  // std::hash<>, std::equal_to<>
#include <tuple>  // std::tuple<>
#include <stdexcept>  // standard exceptions...
#include <cstring>  // std::memset()
#include <cstddef>  // std::size_t, std::ptrdiff_t

namespace rocket {

using ::std::nullptr_t;
using ::std::ptrdiff_t;
using ::std::size_t;
using ::std::intptr_t;
using ::std::uintptr_t;
using ::std::intmax_t;
using ::std::uintmax_t;
using ::std::int8_t;
using ::std::uint8_t;
using ::std::int16_t;
using ::std::uint16_t;
using ::std::int32_t;
using ::std::uint32_t;
using ::std::int64_t;
using ::std::uint64_t;
using ::std::initializer_list;
using ::std::numeric_limits;
using ::std::type_info;
using ::std::nothrow_t;

using ::std::true_type;
using ::std::false_type;
using ::std::integral_constant;
using ::std::enable_if;
using ::std::conditional;
using ::std::decay;
using ::std::is_constructible;
using ::std::is_assignable;
using ::std::is_nothrow_constructible;
using ::std::is_nothrow_assignable;
using ::std::is_nothrow_default_constructible;
using ::std::is_nothrow_copy_constructible;
using ::std::is_nothrow_copy_assignable;
using ::std::is_nothrow_move_constructible;
using ::std::is_nothrow_move_assignable;
using ::std::is_nothrow_destructible;
using ::std::is_convertible;
using ::std::is_copy_constructible;
using ::std::is_copy_assignable;
using ::std::is_move_constructible;
using ::std::is_move_assignable;
using ::std::is_const;
using ::std::add_const;
using ::std::remove_const;
using ::std::is_reference;
using ::std::is_lvalue_reference;
using ::std::is_rvalue_reference;
using ::std::add_lvalue_reference;
using ::std::add_rvalue_reference;
using ::std::remove_reference;
using ::std::remove_cv;
using ::std::is_same;
using ::std::is_trivial;
using ::std::is_integral;
using ::std::is_floating_point;
using ::std::is_void;
using ::std::is_trivially_default_constructible;
using ::std::is_trivially_copy_constructible;
using ::std::is_trivially_move_constructible;
using ::std::is_trivially_copy_assignable;
using ::std::is_trivially_move_assignable;
using ::std::is_trivially_destructible;
using ::std::underlying_type;
using ::std::is_array;
using ::std::is_base_of;
using ::std::aligned_union;
using ::std::is_signed;
using ::std::make_signed;
using ::std::is_unsigned;
using ::std::make_unsigned;
using ::std::is_final;
using ::std::is_enum;
using ::std::is_class;
using ::std::is_union;
using ::std::is_scalar;
using ::std::is_arithmetic;

using ::std::allocator;
using ::std::allocator_traits;
using ::std::default_delete;

using ::std::iterator_traits;
using ::std::output_iterator_tag;
using ::std::input_iterator_tag;
using ::std::forward_iterator_tag;
using ::std::bidirectional_iterator_tag;
using ::std::random_access_iterator_tag;

using ::std::hash;
using ::std::equal_to;
using ::std::pair;
using ::std::tuple;

using ::std::logic_error;
using ::std::domain_error;
using ::std::invalid_argument;
using ::std::length_error;
using ::std::out_of_range;
using ::std::runtime_error;
using ::std::range_error;
using ::std::overflow_error;
using ::std::underflow_error;

using ::std::cbegin;
using ::std::cend;
using ::std::begin;
using ::std::end;
using ::std::swap;

namespace noadl = ::rocket;

#define ROCKET_ENABLE_IF(...)            typename ::std::enable_if<+bool(__VA_ARGS__)>::type* = nullptr
#define ROCKET_DISABLE_IF(...)           typename ::std::enable_if<!bool(__VA_ARGS__)>::type* = nullptr

template<typename... unusedT> struct make_void
  {
    using type = void;
  };

#define ROCKET_ENABLE_IF_HAS_TYPE(...)       typename ::rocket::make_void<typename __VA_ARGS__>::type* = nullptr
#define ROCKET_ENABLE_IF_HAS_VALUE(...)      typename ::std::enable_if<!sizeof((__VA_ARGS__)) || true>::type* = nullptr

// The argument must be a non-const lvalue.
template<typename argT, ROCKET_DISABLE_IF(is_same<const argT, argT>::value)>
    ROCKET_ARTIFICIAL_FUNCTION constexpr argT&& move(argT& arg) noexcept
  {
    return static_cast<typename remove_reference<argT>::type&&>(arg);
  }

// The argument must be an lvalue.
template<typename targetT, typename argT, ROCKET_ENABLE_IF(is_reference<argT>::value)>
    ROCKET_ARTIFICIAL_FUNCTION constexpr targetT&& forward(argT&& arg) noexcept
  {
    return static_cast<targetT&&>(arg);
  }

#include "details/utilities.tcc"

template<typename lhsT, typename rhsT>
    struct is_lvalue_assignable : is_assignable<typename add_lvalue_reference<lhsT>::type, rhsT>
  {
  };

template<typename typeT>
    struct remove_cvref : remove_cv<typename remove_reference<typeT>::type>
  {
  };

template<typename typeT>
    struct is_nothrow_swappable : integral_constant<bool, noexcept(swap(::std::declval<typeT&>(),
                                                                        ::std::declval<typeT&>()))>
  {
  };

template<typename typeT>
    ROCKET_ARTIFICIAL_FUNCTION inline void xswap(typeT& lhs, typeT& rhs) noexcept(noexcept(swap(lhs, rhs)))
  {
    swap(lhs, rhs);
  }

template<typename firstT, typename secondT, typename... restT>
    struct select_type : select_type<typename select_type<firstT, secondT>::type,
                                     restT...>
  {
  };
template<typename firstT, typename secondT>
    struct select_type<firstT, secondT> : enable_if<1, decltype(1 ? ::std::declval<firstT ()>()()
                                                                  : ::std::declval<secondT ()>()())>
  {
  };

template<typename lhsT, typename rhsT>
    constexpr typename select_type<lhsT&&, rhsT&&>::type min(lhsT&& lhs, rhsT&& rhs)
  {
    return (rhs < lhs) ? noadl::forward<rhsT>(rhs)
                       : noadl::forward<lhsT>(lhs);
  }

template<typename lhsT, typename rhsT>
    constexpr typename select_type<lhsT&&, rhsT&&>::type max(lhsT&& lhs, rhsT&& rhs)
  {
    return (lhs < rhs) ? noadl::forward<rhsT>(rhs)
                       : noadl::forward<lhsT>(lhs);
  }

template<typename testT, typename lowerT, typename upperT>
    constexpr typename select_type<testT&&, lowerT&&, upperT&&>::type clamp(testT&& test, lowerT&& lower, upperT&& upper)
  {
    return (test < lower) ? noadl::forward<lowerT>(lower)
                          : (upper < test) ? noadl::forward<upperT>(upper)
                                           : noadl::forward<testT>(test);
  }

template<typename firstT, typename lastT, typename funcT, typename... paramsT>
    void ranged_for(firstT first, lastT last, funcT&& func, const paramsT&... params)
  {
    for(auto qit = noadl::move(first); qit != last; ++qit)
      noadl::forward<funcT>(func)(qit, params...);
  }

template<typename firstT, typename lastT, typename funcT, typename... paramsT>
    void ranged_do_while(firstT first, lastT last, funcT&& func, const paramsT&... params)
  {
    auto qit = noadl::move(first);
    do {
      noadl::forward<funcT>(func)(qit, params...);
    } while(++qit != last);
  }

template<typename... typesT>
    struct conjunction : true_type
  {
  };
template<typename firstT, typename... restT>
    struct conjunction<firstT, restT...> : conditional<bool(firstT::value), conjunction<restT...>, firstT>::type
  {
  };

template<typename... typesT>
    struct disjunction : false_type
  {
  };
template<typename firstT, typename... restT>
    struct disjunction<firstT, restT...> : conditional<bool(firstT::value), firstT, disjunction<restT...>>::type
  {
  };

template<typename iteratorT>
    constexpr size_t estimate_distance(iteratorT first, iteratorT last)
  {
    return details_utilities::estimate_distance_aux(typename iterator_traits<iteratorT>::iterator_category(),
                                                    noadl::move(first), noadl::move(last));
  }

template<typename elementT, typename... paramsT>
    elementT* construct_at(elementT* ptr, paramsT&&... params)
                       noexcept(is_nothrow_constructible<elementT, paramsT&&...>::value)
  {
#ifdef ROCKET_DEBUG
    ::std::memset(static_cast<void*>(ptr), 0xAA, sizeof(elementT));
#endif
    return ::new(static_cast<void*>(ptr)) elementT(noadl::forward<paramsT>(params)...);
  }

template<typename elementT>
    elementT* default_construct_at(elementT* ptr)
                       noexcept(is_nothrow_default_constructible<elementT>::value)
  {
#ifdef ROCKET_DEBUG
    ::std::memset(static_cast<void*>(ptr), 0xBE, sizeof(elementT));
#endif
    return ::new(static_cast<void*>(ptr)) elementT;
  }

template<typename elementT>
    void destroy_at(elementT* ptr) noexcept(is_nothrow_destructible<elementT>::value)
  {
    if(is_trivially_destructible<elementT>::value) {
      // Don't do anything. The C++ standard says the lifetime of such an object does not end.
      return;
    }
    ptr->~elementT();
#ifdef ROCKET_DEBUG
    ::std::memset(static_cast<void*>(ptr), 0xD9, sizeof(elementT));
#endif
  }

template<typename elementT> void rotate(elementT* ptr, size_t begin, size_t seek, size_t end)
  {
    auto bot = begin;
    auto brk = seek;
    //   |<- isl ->|<- isr ->|
    //   bot       brk       end
    // > 0 1 2 3 4 5 6 7 8 9 -
    auto isl = brk - bot;
    if(isl == 0) {
      return;
    }
    auto isr = end - brk;
    if(isr == 0) {
      return;
    }
    auto stp = brk;
  r:
    if(isl < isr) {
      // Before:  bot   brk           end
      //        > 0 1 2 3 4 5 6 7 8 9 -
      // After:         bot   brk     end
      //        > 3 4 5 0 1 2 6 7 8 9 -
      do {
        swap(ptr[bot++], ptr[brk++]);
      } while(bot != stp);
      // `isr` will have been decreased by `isl`, which will not result in zero.
      isr = end - brk;
      // `isl` is unchanged.
      stp = brk;
      goto r;
    }
    if(isl > isr) {
      // Before:  bot           brk   end
      //        > 0 1 2 3 4 5 6 7 8 9 -
      // After:       bot       brk   end
      //        > 7 8 9 3 4 5 6 0 1 2 -
      do {
        swap(ptr[bot++], ptr[brk++]);
      } while(brk != end);
      // `isl` will have been decreased by `isr`, which will not result in zero.
      isl = stp - bot;
      // `isr` is unchanged.
      brk = stp;
      goto r;
    }
    // Before:  bot       brk       end
    //        > 0 1 2 3 4 5 6 7 8 9 -
    // After:             bot       brk
    //        > 5 6 7 8 9 0 1 2 3 4 -
    do {
      swap(ptr[bot++], ptr[brk++]);
    } while(bot != stp);
  }

template<typename containerT, typename callbackT>
    void for_each(containerT&& cont, callbackT&& callback)
  {
    return details_utilities::for_each_nonconstexpr(noadl::forward<containerT>(cont),
                                                    noadl::forward<callbackT>(callback));
  }
template<typename elementT, typename callbackT>
    void for_each(initializer_list<elementT> init, callbackT&& callback)
  {
    return details_utilities::for_each_nonconstexpr(init, noadl::forward<callbackT>(callback));
  }

template<typename containerT, typename callbackT>
    constexpr bool any_of(containerT&& cont, callbackT&& callback)
  {
    return details_utilities::any_of_nonconstexpr(noadl::forward<containerT>(cont),
                                                  noadl::forward<callbackT>(callback));
  }
template<typename elementT, typename callbackT>
    constexpr bool any_of(initializer_list<elementT> init, callbackT&& callback)
  {
    return details_utilities::any_of_nonconstexpr(init, noadl::forward<callbackT>(callback));
  }

template<typename containerT, typename callbackT>
    constexpr bool none_of(containerT&& cont, callbackT&& callback)
  {
    return details_utilities::none_of_nonconstexpr(noadl::forward<containerT>(cont),
                                                   noadl::forward<callbackT>(callback));
  }
template<typename elementT, typename callbackT>
    constexpr bool none_of(initializer_list<elementT> init, callbackT&& callback)
  {
    return details_utilities::none_of_nonconstexpr(init, noadl::forward<callbackT>(callback));
  }

template<typename targetT, typename containerT>
    constexpr bool is_any_of(targetT&& targ, containerT&& cont)
  {
    return details_utilities::is_any_of_nonconstexpr(noadl::forward<targetT>(targ),
                                                     noadl::forward<containerT>(cont));
  }
template<typename targetT, typename elementT>
    constexpr bool is_any_of(targetT&& targ, initializer_list<elementT> init)
  {
    return details_utilities::is_any_of_nonconstexpr(noadl::forward<targetT>(targ), init);
  }

template<typename targetT, typename containerT>
    constexpr bool is_none_of(targetT&& targ, containerT&& cont)
  {
    return details_utilities::is_none_of_nonconstexpr(noadl::forward<targetT>(targ),
                                                      noadl::forward<containerT>(cont));
  }
template<typename targetT, typename elementT>
    constexpr bool is_none_of(targetT&& targ, initializer_list<elementT> init)
  {
    return details_utilities::is_none_of_nonconstexpr(noadl::forward<targetT>(targ), init);
  }

template<typename enumT>
    constexpr typename underlying_type<enumT>::type weaken_enum(enumT value) noexcept
  {
    return static_cast<typename underlying_type<enumT>::type>(value);
  }

template<typename elementT, size_t countT>
    constexpr size_t countof(const elementT (&)[countT]) noexcept
  {
    return countT;
  }

template<intmax_t valueT>
    struct lowest_signed
      : details_utilities::integer_selector<intmax_t, valueT,
              signed char, signed short, signed, signed long, signed long long>
  {
  };

template<uintmax_t valueT>
    struct lowest_unsigned
      : details_utilities::integer_selector<uintmax_t, valueT,
              unsigned char, unsigned short, unsigned, unsigned long, unsigned long long>
  {
  };

// This tag value is used to construct an empty container. Assigning `emptyc` to a container clears it.
struct emptyc_t
  {
  }
constexpr emptyc;

// Fancy pointer conversion
template<typename pointerT>
    constexpr typename remove_reference<decltype(*(::std::declval<pointerT&>()))>::type* unfancy(pointerT&& ptr)
  {
    return ptr ? ::std::addressof(*ptr) : nullptr;
  }

template<typename targetT, typename sourceT>
    struct can_static_cast : details_utilities::can_static_cast_aux<targetT, sourceT>
  {
  };

template<typename targetT, typename sourceT>
    constexpr targetT static_or_dynamic_cast(sourceT&& src)
  {
    return details_utilities::static_or_dynamic_cast_aux<targetT, sourceT>(
      details_utilities::can_static_cast_aux<targetT, sourceT&&>(), noadl::forward<sourceT>(src));
  }

}  // namespace rocket

#endif
