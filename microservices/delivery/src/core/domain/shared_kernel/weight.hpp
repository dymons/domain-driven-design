#pragma once

#include <compare>

namespace delivery::core::domain::shared_kernel {

class Weight {
  /// Weight, stores the value in kilograms
  int value_;

  // Constructors

  /*!
    \brief
        User constructor, constructs Weight with predefined weight
  */
  explicit Weight(int value) : value_(value) {}

 public:
  /*!
    \brief
        Factory method, constructs Weight with predefined weight

    \param weight
        The weight in kilograms

    \throw ArgumentException
        During construction, check that the weight takes a positive value

    \return
        Return a validate weight value object

    \ingroup
        SharedKernel
  */
  [[nodiscard]] static auto Create(int value) -> Weight;

  // Observers

  /*!
    \brief
        Get the weight
  */
  [[nodiscard]] auto GetWeight() const noexcept -> int { return value_; }

  /*!
    \brief
        Comparing two Weight objects
  */
  constexpr auto operator<=>(Weight const&) const = default;
};

}  // namespace delivery::core::domain::shared_kernel
