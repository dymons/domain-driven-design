#include "client_mock.hpp"

namespace delivery::core::ports {

namespace {

class GeocodeMapsLocation final : public IGeocodeMapsLocation {
 public:
  ~GeocodeMapsLocation() final = default;

  GeocodeMapsLocation(core::domain::Location location) : location_{location} {}

  [[nodiscard]] auto GetLocation() const -> core::domain::Location final {
    return location_;
  }

 private:
  core::domain::Location location_;
};

class GeocodeMapsClient final : public IGeocodeMapsClient {
 public:
  ~GeocodeMapsClient() final = default;

  GeocodeMapsClient(core::domain::Location location)
      : location_{delivery::MakeSharedRef<GeocodeMapsLocation>(location)} {}

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
  return delivery::MakeSharedRef<GeocodeMapsClient>(location);
}

}  // namespace delivery::core::ports
