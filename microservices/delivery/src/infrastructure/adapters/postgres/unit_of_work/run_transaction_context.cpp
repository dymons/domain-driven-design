#include "run_transaction_context.hpp"

#include <infrastructure/adapters/postgres/courier_repository/repository.hpp>
#include <infrastructure/adapters/postgres/order_repository/repository.hpp>

#include "irun_transaction_context.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

class RunTransactionContext final : public IRunTransactionContext {
 public:
  ~RunTransactionContext() final = default;

  explicit RunTransactionContext(
      MutableSharedRef<userver::storages::postgres::Transaction> transaction)
      : transaction_{std::move(transaction)} {}

  [[nodiscard]] auto GetCourierRepository() const
      -> SharedRef<core::ports::ICourierRepository> final {
    return MakeCourierRepository(transaction_);
  }

  [[nodiscard]] auto GetOrderRepository() const
      -> SharedRef<core::ports::IOrderRepository> final {
    return MakeOrderRepository(transaction_);
  }

 private:
  MutableSharedRef<userver::storages::postgres::Transaction> const transaction_;
};

}  // namespace

auto MakeRunTransactionContext(
    MutableSharedRef<userver::storages::postgres::Transaction> transaction)
    -> SharedRef<IRunTransactionContext> {
  return delivery::MakeSharedRef<RunTransactionContext>(std::move(transaction));
}

}  // namespace delivery::infrastructure::adapters::postgres
