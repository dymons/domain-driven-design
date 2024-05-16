#pragma once

#include <utility>

namespace delivery::core::domain::shared_kernel {

class Weight {
  /// Weight, stores the value in kilograms
  int weight_;

  // Constructors

  /*!
    \brief
        User constructor, constructs a Weight with predefined weight.
  */
  explicit Weight(int weight) : weight_(weight) {}

 public:
  /*!
    \brief
        Named constructor, constructs a Weight with predefined weight

    \param weight
        The weight in kilograms

    \throw ArgumentException
        During construction, check that the weight takes a positive value

    \return
        Return a validate weight value object

    \ingroup
        SharedKernel
  */
  [[nodiscard]] static auto Create(int weight) -> Weight;

  // Observers

  /*!
    \brief
        Get the weight
  */
  template <typename Self>
  [[nodiscard]] constexpr decltype(auto) GetWeight(this Self&& self) {
    return std::forward<Self>(self).weight_;
  }

  /*!
    \brief
        Comparing two Weight objects
  */
  constexpr auto operator<=>(Weight const&) const = default;
};

}  // namespace delivery::core::domain::shared_kernel
