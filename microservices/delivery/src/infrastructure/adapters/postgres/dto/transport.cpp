#include "transport.hpp"

#include <core/domain/courier/transport.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::courier::Transport const& transport) -> Transport {
  return Transport{
      .id = transport.GetId().GetUnderlying(),
      .name = transport.GetName().GetUnderlying(),
      .speed = transport.GetSpeed().GetUnderlying(),
      .capacity = transport.GetCapacity().GetWeight(),
  };
}

auto Convert(Transport const& transport) -> core::domain::courier::Transport {
  return core::domain::courier::Transport::Hydrate(
      core::domain::courier::TransportId{transport.id},
      core::domain::courier::TransportName{transport.name},
      core::domain::courier::Speed{transport.speed},
      core::domain::shared_kernel::Weight{transport.capacity});
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
