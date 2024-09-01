#include "repository_mock.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>

#include "irepository.hpp"

namespace delivery::core::ports {

namespace {

class CourierRepository final : public ICourierRepository {
 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(
      std::vector<MutableSharedRef<domain::courier::Courier>> couriers)
      : couriers_{std::move(couriers)} {}

  auto Add(SharedRef<domain::courier::Courier> const& courier) const
      -> void final {
    for (const auto& courier : couriers_) {
      if (courier->GetId() == courier->GetId()) {
        userver::utils::LogErrorAndThrow<CourierAlreadyExists>("");
      }
    }

    couriers_.push_back(
        MakeMutableSharedRef<domain::courier::Courier>(*courier));
  }

  auto Update(SharedRef<domain::courier::Courier> const& new_courier) const
      -> void final {
    auto it = std::ranges::find_if(couriers_, [&](const auto& courier) {
      return courier->GetId() == new_courier->GetId();
    });

    if (it == couriers_.end()) {
      userver::utils::LogErrorAndThrow<CourierNotFound>("");
    }

    *it = MakeMutableSharedRef<domain::courier::Courier>(*new_courier);
  }

  auto GetById(domain::CourierId const& courier_id) const
      -> MutableSharedRef<domain::courier::Courier> final {
    for (const auto& courier : couriers_) {
      if (courier->GetId() == courier_id) {
        return courier;
      }
    }

    userver::utils::LogErrorAndThrow<CourierNotFound>("");
  }

  auto GetByReadyStatus() const
      -> std::vector<MutableSharedRef<domain::courier::Courier>> final {
    auto result = std::vector<MutableSharedRef<domain::courier::Courier>>{};
    for (const auto& courier : couriers_) {
      if (courier->GetStatus().IsReady()) {
        result.push_back(courier);
      }
    }
    return result;
  }

  auto GetByBusyStatus() const
      -> std::vector<MutableSharedRef<domain::courier::Courier>> final {
    auto result = std::vector<MutableSharedRef<domain::courier::Courier>>{};
    for (const auto& courier : couriers_) {
      if (courier->GetStatus().IsBusy()) {
        result.push_back(courier);
      }
    }
    return result;
  }

  auto GetCouriers() const
      -> std::vector<MutableSharedRef<domain::courier::Courier>> final {
    return couriers_;
  }

 private:
  mutable std::vector<MutableSharedRef<domain::courier::Courier>> couriers_;
};

}  // namespace

auto MockCourierRepository(
    std::vector<MutableSharedRef<domain::courier::Courier>> couriers)
    -> SharedRef<ICourierRepository> {
  return delivery::MakeSharedRef<CourierRepository>(std::move(couriers));
}

}  // namespace delivery::core::ports
