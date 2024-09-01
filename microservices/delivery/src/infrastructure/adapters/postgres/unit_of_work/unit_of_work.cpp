#include "unit_of_work.hpp"

#include <optional>

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/adapters/postgres/courier_repository/repository.hpp>
#include <infrastructure/adapters/postgres/order_repository/repository.hpp>

#include "irun_transaction_context.hpp"
#include "iunit_of_work.hpp"
#include "run_transaction_context.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

class UnitOfWork final : public IUnitOfWork {
 public:
  ~UnitOfWork() final = default;

  explicit UnitOfWork(userver::storages::postgres::ClusterPtr cluster)
      : cluster_{std::move(cluster)} {}

  auto RunTransaction(
      std::function<void(SharedRef<IRunTransactionContext>)> routine) const
      -> void final {
    auto transaction = delivery::MakeMutableSharedRef<
        userver::storages::postgres::Transaction>(cluster_->Begin({}));

    try {
      routine(MakeRunTransactionContext(transaction));
      transaction->Commit();
    } catch (const std::exception& e) {
      LOG_ERROR() << "Exception is thrown during run transaction: " << e;
      throw;
    }
  };

 private:
  userver::storages::postgres::ClusterPtr const cluster_;
};

}  // namespace

auto MakeUnitOfWork(userver::storages::postgres::ClusterPtr cluster)
    -> SharedRef<IUnitOfWork> {
  return delivery::MakeSharedRef<UnitOfWork>(std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
