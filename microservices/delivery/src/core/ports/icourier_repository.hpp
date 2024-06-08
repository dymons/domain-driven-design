#pragma once

#include <vector>

#include <core/domain/courier/strong_typedefs.hpp>

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::ports {

class ICourierRepository {
 protected:
  using Courier = domain::courier::Courier;
  using CourierId = domain::courier::CourierId;

 public:
  virtual ~ICourierRepository() = default;

  ICourierRepository() = default;
  ICourierRepository(ICourierRepository const&) = delete;
  ICourierRepository(ICourierRepository&&) = delete;
  ICourierRepository& operator=(ICourierRepository const&) = delete;
  ICourierRepository& operator=(ICourierRepository&&) = delete;

  virtual auto Add(Courier const&) const -> void = 0;
  virtual auto Update(Courier const&) const -> void = 0;
  virtual auto GetById(CourierId const&) const -> Courier = 0;
  virtual auto GetByReadyStatus() const -> std::vector<Courier> = 0;
  virtual auto GetByBusyStatus() const -> std::vector<Courier> = 0;
};

}  // namespace delivery::core::ports
