#include <Backend.hpp>

#ifdef DQCSIM_SHORT_LOGGING_MACROS
#ifdef DQCSIM_IQS_MPI_ENABLED
#define DQCSIM_IQS_TRACE(x) \
    if (!rank)              \
        TRACE(x);
#else
#define DQCSIM_IQS_TRACE(x) TRACE(x)
#endif
#else
#define DQCSIM_IQS_TRACE(x)
#endif

IqsBackend::IqsBackend(int argc, char *argv[]) : env{argc, argv}, rank{env.GetRank()}, reg{1} {
    if (env.IsUsefulRank() == false)
        std::exit(EXIT_FAILURE);
}

void IqsBackend::initialize(PluginState &state, ArbCmdQueue &&queue) {
    DQCSIM_IQS_TRACE("@ IqsBackend::initialize");
}

void IqsBackend::drop(PluginState &state) {
    DQCSIM_IQS_TRACE("@ IqsBackend::drop");
    reg.Print("", {});
}

void IqsBackend::allocate(PluginState &state, QubitSet &&qubits, ArbCmdQueue &&queue) {
    auto n = qubits.size();

    DQCSIM_IQS_TRACE("@ IqsBackend::allocate (" + std::to_string(n) + " qubits)");
    reg.Allocate(n, 0);
    reg.Initialize("base", 0);
}

void IqsBackend::free(PluginState &state, QubitSet &&qbits) {
    DQCSIM_IQS_TRACE("@ IqsBackend::free");
}

MeasurementSet IqsBackend::gate(PluginState &state, Gate &&arg) {
    using complex = dqcsim::wrap::complex;
    DQCSIM_IQS_TRACE("@ IqsBackend::gate");

    auto measurement_set = MeasurementSet();

    auto type = arg.get_type();
    switch (type) {
    case GateType::Unitary: {
        DQCSIM_IQS_TRACE("\ttype=unitary");

        auto matrix = arg.get_matrix();
        auto target = arg.get_targets().pop().get_index() - 1;
        DQCSIM_IQS_TRACE("\ttarget=" + std::to_string(target));

        // Controlled or single gate
        if (arg.has_controls()) {
            if (arg.get_controls().size() != 1)
                ERROR("Cannot simulate gates with more than 2 control qubits");

            auto control = arg.get_controls().pop().get_index() - 1;
            DQCSIM_IQS_TRACE("\tcontrol=" + std::to_string(control));

            apply_controlled_gate(control, target, matrix);
        } else {
            apply_gate(target, matrix);
        }
        break;
    }

    case GateType::Measurement: {
        DQCSIM_IQS_TRACE("\ttype=measurement");

        auto target = arg.get_measures().pop().get_index() - 1;
        DQCSIM_IQS_TRACE("\ttarget=" + std::to_string(target));

        auto matrix = arg.get_matrix();
        apply_gate(target, matrix);

        auto value = reg.GetClassicalValue(target) ? MeasurementValue::One : MeasurementValue::Zero;
        auto measurement = Measurement(target + 1, value);
        measurement_set.set(measurement);

        break;
    }

    default: {
        ERROR("gate type not recognized" + arg.dump());
        break;
    }
    }

    return measurement_set;
}

void IqsBackend::advance(PluginState &state, Cycle cycle) {
    DQCSIM_IQS_TRACE("@ IqsBackend::advance");
}

ArbData IqsBackend::arb_cmd(PluginState &state, ArbCmd cmd) {
    DQCSIM_IQS_TRACE("@ IqsBackend::arb_cmd");
    return ArbData();
}

void IqsBackend::apply_gate(QubitIndex qubit, Matrix matrix) {
    using complex = dqcsim::wrap::complex;

    auto vec = matrix.get();
    auto tm = TM2x2<complex>(*reinterpret_cast<complex(*)[2][2]>(vec.data()));

    reg.Apply1QubitGate(qubit, tm);
}

void IqsBackend::apply_controlled_gate(QubitIndex control, QubitIndex target, Matrix matrix) {
    using complex = dqcsim::wrap::complex;

    auto vec = matrix.get();
    auto tm = TM2x2<complex>(*reinterpret_cast<complex(*)[2][2]>(vec.data()));

    reg.ApplyControlled1QubitGate(control, target, tm);
}