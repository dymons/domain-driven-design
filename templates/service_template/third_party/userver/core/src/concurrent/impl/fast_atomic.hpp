#pragma once

#include <atomic>
#include <type_traits>

#ifdef USERVER_USE_BOOST_DWCAS
#include <boost/atomic/atomic.hpp>
#endif

#include <utils/impl/assert_extra.hpp>

#ifdef USERVER_PROTECT_DWCAS
#define USERVER_IMPL_PROTECT_DWCAS_ATTR __attribute__((noinline, flatten))
#else
#define USERVER_IMPL_PROTECT_DWCAS_ATTR __attribute__((always_inline, flatten))
#endif

USERVER_NAMESPACE_BEGIN

namespace concurrent::impl {

#ifdef USERVER_USE_BOOST_DWCAS
template <typename T>
using DoubleWidthCapableAtomic = boost::atomic<T>;

constexpr boost::memory_order ToInternalMemoryOrder(
    std::memory_order order) noexcept {
  switch (order) {
    case std::memory_order_relaxed:
      return boost::memory_order_relaxed;
    case std::memory_order_consume:
      return boost::memory_order_consume;
    case std::memory_order_acquire:
      return boost::memory_order_acquire;
    case std::memory_order_release:
      return boost::memory_order_release;
    case std::memory_order_acq_rel:
      return boost::memory_order_acq_rel;
    case std::memory_order_seq_cst:
      return boost::memory_order_seq_cst;
  }
  // AbortWithStacktrace here leads to a compilation error on GCC 8.
  return boost::memory_order_seq_cst;
}
#else
template <typename T>
using DoubleWidthCapableAtomic = std::atomic<T>;

constexpr std::memory_order ToInternalMemoryOrder(
    std::memory_order order) noexcept {
  return order;
}
#endif

// Tries harder than std::atomic to be lock-free.
// See also RequireDWCAS.cmake.
//
// Has a std::atomic-compatible interface.
template <typename T>
class FastAtomic final {
  static_assert(sizeof(T) <= sizeof(void*) * 2);
  // NOLINTNEXTLINE(misc-redundant-expression)
  static_assert(alignof(T) == sizeof(T));
  static_assert(std::is_trivially_copyable_v<T>);
  static_assert(std::has_unique_object_representations_v<T>);

 public:
  constexpr FastAtomic(T desired) noexcept : impl_(desired) {}

  FastAtomic(const FastAtomic&) = delete;

  template <std::memory_order Success, std::memory_order Failure>
  USERVER_IMPL_PROTECT_DWCAS_ATTR bool compare_exchange_strong(
      T& expected, T desired) noexcept {
    return impl_.compare_exchange_strong(expected, desired,
                                         ToInternalMemoryOrder(Success),
                                         ToInternalMemoryOrder(Failure));
  }

  template <std::memory_order Order>
  USERVER_IMPL_PROTECT_DWCAS_ATTR T load() const noexcept {
    return impl_.load(ToInternalMemoryOrder(Order));
  }

  template <std::memory_order Order>
  USERVER_IMPL_PROTECT_DWCAS_ATTR T exchange(T desired) noexcept {
    return impl_.exchange(desired, ToInternalMemoryOrder(Order));
  }

 private:
  DoubleWidthCapableAtomic<T> impl_;
};

}  // namespace concurrent::impl

USERVER_NAMESPACE_END
