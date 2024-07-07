#include "client_mock_test.hpp"

namespace delivery::core::ports {

namespace {

class GeocodeMapsLocation final : public IGeocodeMapsLocation {
 public:
  ~GeocodeMapsLocation() final = default;

  GeocodeMapsLocation(core::domain::Location location) : location_{location} {}

  auto GetLocation() const -> core::domain::Location final { return location_; }

 private:
  core::domain::Location location_;
};

class GeocodeMapsClient final : public IGeocodeMapsClient {
 public:
  ~GeocodeMapsClient() final = default;

  GeocodeMapsClient(core::domain::Location location)
      : location_{userver::utils::MakeSharedRef<const GeocodeMapsLocation>(
            location)} {}

  [[nodiscard]] auto Geocode(std::string const&) const
      -> SharedRef<IGeocodeMapsLocation> final {
    return location_;
  }

 private:
  SharedRef<IGeocodeMapsLocation> const location_;
};

}  // namespace

auto MockGeocodeMapsClient(core::domain::Location location)
    -> SharedRef<IGeocodeMapsClient> {
  return userver::utils::MakeSharedRef<const GeocodeMapsClient>(location);
}

}  // namespace delivery::core::ports
