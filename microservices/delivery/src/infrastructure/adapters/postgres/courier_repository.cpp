#include "courier_repository.hpp"

#include <core/domain/courier/courier.hpp>

namespace delivery::infrastructure::adapters::postgres {

class CourierRepository final : public core::ports::ICourierRepository {
 public:
  ~CourierRepository() final = default;

  auto Add(core::domain::courier::Courier const&) const -> void final {}

  auto Update(core::domain::courier::Courier const&) const -> void final {}

  auto GetById(core::domain::courier::CourierId const&) const
      -> core::domain::courier::Courier final {
    return core::domain::courier::Courier::Create(
        core::domain::courier::CourierName{"CourierName"},
        core::domain::courier::Transport::kBicycle);
  }

  auto GetAllReady() const
      -> std::vector<core::domain::courier::Courier> final {
    return {};
  }

  auto GetAllBusy() const -> std::vector<core::domain::courier::Courier> final {
    return {};
  }
};

userver::utils::SharedRef<const core::ports::ICourierRepository>
MakeCourierRepository() {
  return userver::utils::MakeSharedRef<const CourierRepository>();
}

}  // namespace delivery::infrastructure::adapters::postgres
