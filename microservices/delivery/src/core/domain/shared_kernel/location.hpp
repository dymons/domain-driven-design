#pragma once

#include <compare>

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::shared_kernel {

using X = userver::utils::StrongTypedef<struct XTag, int>;
using Y = userver::utils::StrongTypedef<struct YTag, int>;

class Location {
  int x_;
  int y_;

  // Constructors

  /*!
    \brief
        User constructor, constructs Location with predefined x and y
  */
  Location(X x, Y y) : x_(x.GetUnderlying()), y_(y.GetUnderlying()) {}

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
  [[nodiscard]] static auto Create(X x, Y y) -> Location;

  // Observers

  /*!
    \brief
        Get coordinates
  */
  [[nodiscard]] auto GetX() const noexcept -> X { return X{x_}; }
  [[nodiscard]] auto GetY() const noexcept -> Y { return Y{y_}; }

  /*!
    \brief
        Calculate distance between locations. The distance between Location
        is the cumulative number of X and Y steps that the courier needs
        to take to reach the point
  */
  [[nodiscard]] auto DistanceTo(Location const&) const noexcept -> int;

  /*!
    \brief
        Comparing two Location objects
  */
  constexpr auto operator<=>(Location const&) const = default;
};

}  // namespace delivery::core::domain::shared_kernel
