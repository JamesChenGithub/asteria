// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ROCKET_ALLOCATOR_UTILITIES_HPP_
#  error Please include <rocket/allocator_utilities.hpp> instead.
#endif

namespace details_allocator_utilities {

template<typename allocT> class final_wrapper
  {
  private:
    allocT m_alloc;

  public:
    constexpr final_wrapper() noexcept(is_nothrow_constructible<allocT>::value)
      :
        m_alloc()
      {
      }
    explicit constexpr final_wrapper(const allocT& alloc) noexcept
      :
        m_alloc(alloc)
      {
      }
    explicit constexpr final_wrapper(allocT&& alloc) noexcept
      :
        m_alloc(noadl::move(alloc))
      {
      }

  public:
    constexpr operator const allocT& () const noexcept
      {
        return this->m_alloc;
      }
    operator allocT& () noexcept
      {
        return this->m_alloc;
      }
  };

// don't propagate
struct propagate_none_tag
  {
  }
constexpr propagate_none;

template<typename allocT>
    void propagate(propagate_none_tag, allocT& /*lhs*/, const allocT& /*rhs*/) noexcept
  {
  }

// propagate_on_container_copy_assignment
struct propagate_copy_tag
  {
  }
constexpr propagate_copy;

template<typename allocT>
    void propagate(propagate_copy_tag, allocT& lhs, const allocT& rhs) noexcept
  {
    lhs = rhs;
  }

// propagate_on_container_move_assignment
struct propagate_move_tag
  {
  }
constexpr propagate_move;

template<typename allocT>
    void propagate(propagate_move_tag, allocT& lhs, allocT& rhs) noexcept
  {
    lhs = noadl::move(rhs);
  }

// propagate_on_container_swap
struct propagate_swap_tag
  {
  }
constexpr propagate_swap;

template<typename allocT>
    void propagate(propagate_swap_tag, allocT& lhs, allocT& rhs) noexcept
  {
    xswap(lhs, rhs);
  }

}  // namespace details_allocator_utilities
