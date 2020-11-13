#define DQCSIM_SHORT_LOGGING_MACROS
#include <Backend.hpp>
#include <dqcsim>

using namespace dqcsim::wrap;

int main(int argc, char *argv[]) {
    IqsBackend backend;
    return Plugin::Backend("Intel QS", "Sergio Sánchez Ramírez", "0.1")
        .with_initialize(&backend, &IqsBackend::initialize)
        .with_drop(&backend, &IqsBackend::drop)
        .with_allocate(&backend, &IqsBackend::allocate)
        .with_free(&backend, &IqsBackend::free)
        .with_gate(&backend, &IqsBackend::gate)
        .with_advance(&backend, &IqsBackend::advance)
        .with_upstream_arb(&backend, &IqsBackend::arb_cmd)
        .with_host_arb(&backend, &IqsBackend::arb_cmd)
        .run(argc, argv);
}