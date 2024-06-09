#pragma once

#include <vector>

#include <core/domain/courier/strong_typedefs.hpp>

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::ports {

class ICourierRepository {
 public:
  virtual ~ICourierRepository() = default;

  ICourierRepository() = default;
  ICourierRepository(ICourierRepository const&) = delete;
  ICourierRepository(ICourierRepository&&) = delete;
  ICourierRepository& operator=(ICourierRepository const&) = delete;
  ICourierRepository& operator=(ICourierRepository&&) = delete;

  virtual auto Add(domain::courier::Courier const&) const -> void = 0;
  virtual auto Update(domain::courier::Courier const&) const -> void = 0;
  virtual auto GetById(domain::courier::CourierId const&) const
      -> domain::courier::Courier = 0;
  virtual auto GetByReadyStatus() const
      -> std::vector<domain::courier::Courier> = 0;
  virtual auto GetByBusyStatus() const
      -> std::vector<domain::courier::Courier> = 0;
};

}  // namespace delivery::core::ports
