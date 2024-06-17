#pragma once

namespace delivery {

class NonCopyableAndMoveable {
 public:
  NonCopyableAndMoveable() = default;
  NonCopyableAndMoveable(NonCopyableAndMoveable const&) = delete;
  NonCopyableAndMoveable(NonCopyableAndMoveable&&) = delete;
  NonCopyableAndMoveable& operator=(NonCopyableAndMoveable const&) = delete;
  NonCopyableAndMoveable& operator=(NonCopyableAndMoveable&&) = delete;
};

}  // namespace delivery
