#pragma once

#include <compare>

namespace delivery::core::domain::shared_kernel {

class Location {
  int x_;
  int y_;

  // Constructors

  /*!
    \brief
        User constructor, constructs Location with predefined x and y
  */
  Location(int x, int y) : x_(x), y_(y) {}

 public:
  /*!
    \brief
        Factory method, constructs Location with predefined x and y

    \param x
      The coordinate by horizontal in units

    \param y
      The coordinate by vertical in units

    \throw ArgumentException
          During construction, check that coordinates are in the range
          from 1 and to 10

    \return
          Return a validate Location value object

    \ingroup
          SharedKernel
  */
  [[nodiscard]] static auto Create(int x, int y) -> Location;

  // Observers

  /*!
    \brief
        Get coordinates
  */
  [[nodiscard]] auto GetX() const noexcept -> int { return x_; }
  [[nodiscard]] auto GetY() const noexcept -> int { return y_; }

  /*!
    \brief
        Comparing two Location objects
  */
  constexpr auto operator<=>(Location const&) const = default;
};

} // namespace delivery::core::domain::shared_kernel
