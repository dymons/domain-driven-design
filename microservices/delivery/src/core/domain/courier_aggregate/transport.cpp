#include "transport.hpp"

namespace delivery::core::domain::courier_aggregate {

const Transport Transport::kPedestrian =
    Transport{TransportId{1}, TransportName{"pedestrian"}, Speed{1},
              shared_kernel::Weight::Create(1)};

const Transport Transport::kBicycle =
    Transport{TransportId{2}, TransportName{"bicycle"}, Speed{2},
              shared_kernel::Weight::Create(4)};

const Transport Transport::kScooter =
    Transport{TransportId{3}, TransportName{"scooter"}, Speed{3},
              shared_kernel::Weight::Create(6)};

const Transport Transport::kCar =
    Transport{TransportId{4}, TransportName{"car"}, Speed{4},
              shared_kernel::Weight::Create(8)};

auto Transport::GetId() const -> TransportId { return id_; }
auto Transport::GetName() const -> TransportName { return name_; }
auto Transport::GetSpeed() const -> Speed { return speed_; }
auto Transport::GetCapacity() const -> shared_kernel::Weight {
  return capacity_;
}

}  // namespace delivery::core::domain::courier_aggregate
