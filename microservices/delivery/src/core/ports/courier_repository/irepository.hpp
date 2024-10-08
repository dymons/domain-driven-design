#pragma once

#include <vector>

#include <core/domain/courier/fwd.hpp>
#include <core/domain/courier/strong_typedefs.hpp>
#include <core/domain/order/strong_typedefs.hpp>
#include <core/domain/shared_kernel/strong_typedefs.hpp>
#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::ports {

struct CourierNotFound final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct CourierAlreadyExists final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class ICourierRepository : private NonCopyableAndMoveable {
 public:
  virtual ~ICourierRepository() = default;

  // Modifiers

  // clang-format off
  virtual auto Add(SharedRef<domain::courier::Courier> const&) const -> void = 0;
  virtual auto Update(SharedRef<domain::courier::Courier> const&) const -> void = 0;
  // clang-format on

  // Observers

  // clang-format off
  virtual auto GetById(domain::CourierId const&) const -> MutableSharedRef<domain::courier::Courier> = 0;
  virtual auto GetByReadyStatus() const -> std::vector<MutableSharedRef<domain::courier::Courier>> = 0;
  virtual auto GetByBusyStatus() const -> std::vector<MutableSharedRef<domain::courier::Courier>> = 0;
  virtual auto GetCouriers() const -> std::vector<MutableSharedRef<domain::courier::Courier>> = 0;
  // clang-format on
};

}  // namespace delivery::core::ports
