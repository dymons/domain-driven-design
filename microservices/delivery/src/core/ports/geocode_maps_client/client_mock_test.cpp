#include "client_mock_test.hpp"

namespace delivery::core::ports {

namespace {

class Location final : public ILocation {
 public:
  ~Location() final = default;

  explicit Location(core::domain::Location location) : location_{location} {}

  auto GetLocation() const -> core::domain::Location final { return location_; }

 private:
  core::domain::Location location_;
};

class GeocodeMapsClient final : public IGeocodeMapsClient {
 public:
  ~GeocodeMapsClient() final = default;

  explicit GeocodeMapsClient(core::domain::Location location)
      : location_{userver::utils::MakeSharedRef<const Location>(location)} {}

  auto Geocode(std::string const&) const -> SharedRef<ILocation> final {
    return location_;
  }

 private:
  SharedRef<ILocation> const location_;
};

}  // namespace

auto MockGeocodeMapsClient(core::domain::Location location)
    -> SharedRef<IGeocodeMapsClient> {
  return userver::utils::MakeSharedRef<const GeocodeMapsClient>(location);
}

}  // namespace delivery::core::ports
