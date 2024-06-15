#pragma once

#include <unordered_set>

#include <core/domain/courier/strong_typedefs.hpp>
#include <utils/memory.hpp>

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::ports {

struct CourierNotFound final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct CourierAlreadyExists final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class ICourierRepository {
 public:
  virtual ~ICourierRepository() = default;

  ICourierRepository() = default;
  ICourierRepository(ICourierRepository const&) = delete;
  ICourierRepository(ICourierRepository&&) = delete;
  ICourierRepository& operator=(ICourierRepository const&) = delete;
  ICourierRepository& operator=(ICourierRepository&&) = delete;

  virtual auto Add(SharedRef<domain::courier::Courier> const&) const
      -> void = 0;
  virtual auto Update(SharedRef<domain::courier::Courier> const&) const
      -> void = 0;
  virtual auto GetById(domain::courier::CourierId const&) const
      -> MutableSharedRef<domain::courier::Courier> = 0;
  virtual auto GetByReadyStatus() const
      -> std::unordered_set<MutableSharedRef<domain::courier::Courier>> = 0;
  virtual auto GetByBusyStatus() const
      -> std::unordered_set<MutableSharedRef<domain::courier::Courier>> = 0;
};

}  // namespace delivery::core::ports
