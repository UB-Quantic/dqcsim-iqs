#include <Backend.hpp>

IqsBackend::IqsBackend() : reg{1} {}

void IqsBackend::initialize(PluginState &state, ArbCmdQueue &&queue) {
    INFO("@ IqsBackend::initialize");
}

void IqsBackend::drop(PluginState &state) {
    INFO("@ IqsBackend::drop");
    reg.Print("", {});
}

void IqsBackend::allocate(PluginState &state, QubitSet &&qubits, ArbCmdQueue &&queue) {
    auto n = qubits.size();

    INFO("@ IqsBackend::allocate (" + std::to_string(n) + " qubits)");
    reg.Allocate(n, 0);
    reg.Initialize("base", 0);
}

void IqsBackend::free(PluginState &state, QubitSet &&qbits) {
    INFO("@ IqsBackend::free");
}

MeasurementSet IqsBackend::gate(PluginState &state, Gate &&arg) {
    using complex = dqcsim::wrap::complex;
    INFO("@ IqsBackend::gate");

    auto measurement_set = MeasurementSet();

    auto type = arg.get_type();
    switch (type) {
    case GateType::Unitary: {
        INFO("\ttype=unitary");

        auto matrix = arg.get_matrix();
        auto target = arg.get_targets().pop().get_index() - 1;
        INFO("\ttarget=" + std::to_string(target));

        // Controlled or single gate
        if (arg.has_controls()) {
            auto control = arg.get_controls().pop().get_index() - 1;
            INFO("\tcontrol=" + std::to_string(control));

            apply_controlled_gate(control, target, matrix);
        } else {
            apply_gate(target, matrix);
        }
        break;
    }

    case GateType::Measurement: {
        INFO("\ttype=measurement");

        auto target = arg.get_measures().pop().get_index() - 1;
        INFO("\ttarget=" + std::to_string(target));

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
    INFO("@ IqsBackend::advance");
}

ArbData IqsBackend::arb_cmd(PluginState &state, ArbCmd cmd) {
    INFO("@ IqsBackend::arb_cmd");
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