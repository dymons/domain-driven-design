#include "transport.hpp"

namespace delivery::core::domain::courier {

const Transport Transport::kPedestrian =
    Transport{TransportId{1}, TransportName{"pedestrian"}, Speed{1}, Weight{1}};

const Transport Transport::kBicycle =
    Transport{TransportId{2}, TransportName{"bicycle"}, Speed{2}, Weight{4}};

const Transport Transport::kScooter =
    Transport{TransportId{3}, TransportName{"scooter"}, Speed{3}, Weight{6}};

const Transport Transport::kCar =
    Transport{TransportId{4}, TransportName{"car"}, Speed{4}, Weight{8}};

auto Transport::Hydrate(TransportId id, TransportName name, Speed speed,
                        Weight capacity) -> Transport {
  return Transport{id, std::move(name), speed, capacity};
}

auto Transport::GetId() const -> TransportId { return id_; }
auto Transport::GetName() const -> TransportName { return name_; }
auto Transport::GetSpeed() const -> Speed { return speed_; }
auto Transport::GetCapacity() const -> Weight { return capacity_; }

}  // namespace delivery::core::domain::courier
