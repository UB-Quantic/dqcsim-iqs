# DQCsim Intel QS backend

A [DQCsim](https://github.com/QE-Lab/dqcsim) backend plugin for the [Intel QS](https://github.com/iqusoft/intel-qs) simulator.

## Usage
You need a DQCsim host plugin executable installed. You may use the `dqcsim` host, which you can install running `cargo install dqcsim --features cli` for a system-wide installation.

If you prefer to work on Python virtualenvs, you may install it running `pip install dqcsim`.

> NOTE: `poetry` crashes if you try to install `dqcsim`. This is a known [bug](https://github.com/python-poetry/poetry/issues/3110).

You will also need a frontend that generates the gate stream. The [OpenQASM frontend](https://github.com/mbrobbel/dqcsim-openqasm) has been used but the [cQASM frontend](https://github.com/jvanstraten/dqcsim-cqasm) could also be used. You may install them by running `cargo install dqcsim-openqasm` and `pip install dqcsim-cqasm`.

Once everything is installed, you can simulate your algorithm by running:
```
dqcsim MY_ALGORITHM.qasm dqcsim-iqs
```
or
```
dqcsim MY_ALGORITHM.cq dqcsim-iqs
```

## Building
Requirements:
- Rust (stable)
- GCC or Intel C/C++ Compiler
- MPI 3.1+ libraries (MPICH recommended)
- CMake 3.14+

In order to use the CMake modules to find the `dqcsim` package, you need to install `dqcsim` through CMake and not through `cargo` or `pip`. Because of that you have to clone the `dqcsim` repository, build it manually and install it. It will only install the `libdqcsim` shared library and the CMake files.

```
git clone https://github.com/QE-Lab/dqcsim
cd dqcsim
cmake -B build -DCMAKE_BUILD_RELEASE .
cmake --build build --config Release --target all
cmake --build build --config Release --target install
```

You can then proceed to build this package.
```
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --config Release --target all
```

This will install the `dqcsim-iqs` executable and `libiqs` shared library into your system.
```
cmake --build build --config Release --target install
```