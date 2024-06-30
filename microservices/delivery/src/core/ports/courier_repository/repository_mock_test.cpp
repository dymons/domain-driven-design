#include "repository_mock_test.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>

namespace delivery::core::ports {

namespace {

class CourierRepository final : public ICourierRepository {
 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(
      std::unordered_set<MutableSharedRef<domain::courier::Courier>> couriers)
      : couriers_{std::move(couriers)} {}

  auto Add(SharedRef<domain::courier::Courier> const& courier) const
      -> void final {
    auto [_, success] = couriers_.insert(
        MakeMutableSharedRef<domain::courier::Courier>(*courier));

    if (not success) {
      userver::utils::LogErrorAndThrow<CourierAlreadyExists>("");
    }
  }

  auto Update(SharedRef<domain::courier::Courier> const& courier) const
      -> void final {
    auto raw_courier = MakeMutableSharedRef<domain::courier::Courier>(*courier);
    if (not couriers_.contains(raw_courier)) {
      userver::utils::LogErrorAndThrow<CourierNotFound>("");
    }

    couriers_.erase(raw_courier);
    Add(raw_courier);
  }

  auto GetById(domain::courier::CourierId const& courier_id) const
      -> MutableSharedRef<domain::courier::Courier> final {
    for (const auto& courier : couriers_) {
      if (courier->GetId() == courier_id) {
        return courier;
      }
    }

    userver::utils::LogErrorAndThrow<CourierNotFound>("");
  }

  auto GetById(domain::order::CourierId const& courier_id) const
      -> MutableSharedRef<domain::courier::Courier> final {
    return GetById(domain::courier::CourierId{courier_id.GetUnderlying()});
  }

  auto GetByReadyStatus() const
      -> std::unordered_set<MutableSharedRef<domain::courier::Courier>> final {
    auto result =
        std::unordered_set<MutableSharedRef<domain::courier::Courier>>{};
    for (const auto& courier : couriers_) {
      if (courier->GetStatus().IsReady()) {
        result.insert(courier);
      }
    }
    return result;
  }

  auto GetByBusyStatus() const
      -> std::unordered_set<MutableSharedRef<domain::courier::Courier>> final {
    auto result =
        std::unordered_set<MutableSharedRef<domain::courier::Courier>>{};
    for (const auto& courier : couriers_) {
      if (courier->GetStatus().IsBusy()) {
        result.insert(courier);
      }
    }
    return result;
  }

  auto GetCouriers() const
      -> std::unordered_set<MutableSharedRef<domain::courier::Courier>> final {
    return couriers_;
  }

 private:
  mutable std::unordered_set<MutableSharedRef<domain::courier::Courier>>
      couriers_;
};

}  // namespace

auto MockCourierRepository(
    std::unordered_set<MutableSharedRef<domain::courier::Courier>> couriers)
    -> SharedRef<ICourierRepository> {
  return userver::utils::MakeSharedRef<const CourierRepository>(
      std::move(couriers));
}

}  // namespace delivery::core::ports
