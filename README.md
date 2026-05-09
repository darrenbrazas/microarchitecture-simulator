# RISC-V Microarchitecture Simulator

A cycle-accurate CPU simulator built in C++ implementing the **RV32I** base integer instruction set. This project simulates real CPU microarchitectures — from a simple single-cycle CPU to a 5-stage pipelined processor — and measures detailed performance metrics.

---

## Features

- **RV32I ISA** — real RISC-V instruction encoding and decoding
- **3 CPU Modes** — single-cycle, 5-stage pipeline, out-of-order (WIP)
- **Hazard Detection** — RAW data hazard detection with stall insertion
- **Branch Handling** — pipeline flush on taken branches
- **Forwarding** — EX→EX and MEM→EX forwarding paths (WIP)
- **2-Bit Branch Predictor** (WIP)
- **L1 Cache Simulator** (WIP)
- **Performance Metrics** — CPI, IPC, stalls, flushes, cache hit rate
- **Built-in Benchmarks** — loop sum, fibonacci, bubble sort (WIP)

---

## Project Structure

```
microarch-simulator/
├── src/
│   ├── cpu/
│   │   ├── single_cycle.cpp    # Single-cycle CPU implementation
│   │   ├── pipeline.cpp        # 5-stage pipeline implementation
│   │   └── out_of_order.cpp    # Out-of-order execution (WIP)
│   ├── memory/
│   │   ├── cache.cpp           # Cache simulator (WIP)
│   │   └── memory.cpp
│   └── isa/
│       └── decode.cpp          # RV32I instruction decoder
├── include/
│   ├── isa.h                   # Instruction types and structs
│   ├── registers.h             # Register file
│   ├── memory.h                # Memory model (64KB)
│   ├── pipeline.h              # Pipeline register structs
│   └── decode.h                # Decoder function declarations
├── programs/
│   └── loop_sum.h              # Loop sum benchmark (0..9)
├── main.cpp                    # Entry point
├── CMakeLists.txt
└── README.md
```

---

## ISA — RV32I Base Integer Instructions

Supports the following instruction formats:

| Format | Instructions |
|--------|-------------|
| R-type | ADD, SUB, AND, OR, XOR, SLL, SRL |
| I-type | ADDI, ANDI, ORI, XORI, LW, JALR |
| S-type | SW |
| B-type | BEQ, BNE, BLT, BGE |
| J-type | JAL |
| U-type | LUI, AUIPC |

---

## Pipeline Stages

```
IF → ID → EX → MEM → WB
```

| Stage | Description |
|-------|-------------|
| IF | Instruction Fetch — load 32-bit instruction from memory |
| ID | Instruction Decode — read register values |
| EX | Execute — ALU operations, branch resolution |
| MEM | Memory Access — load/store |
| WB | Write Back — write result to register file |

---

## Performance Metrics

```
x1 (sum) = 45

=== Pipeline Metrics ===
Cycles:       X
Instructions: X
CPI:          X
Stalls:       X
Flushes:      X
```

| Metric | Description |
|--------|-------------|
| Cycles | Total simulated clock cycles |
| Instructions | Total retired instructions |
| CPI | Cycles per instruction |
| Stalls | Data hazard stall cycles |
| Flushes | Branch misprediction flushes |

---

## Build Instructions

### Requirements
- Windows 10/11
- MinGW-w64 via MSYS2 (`C:\msys64\ucrt64\bin` on PATH)
- CMake 3.16+
- Visual Studio Code (optional)

### Build

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
.\simulator.exe
```

---

## Benchmarks

| Program | Description |
|---------|-------------|
| loop_sum | Sum integers 0–9, expected result: x1 = 45 |
| fibonacci | Compute nth Fibonacci number (WIP) |
| bubble_sort | Sort an array in memory (WIP) |
| matrix_multiply | Matrix multiplication cache stress test (WIP) |

---

## Roadmap

- [x] RV32I instruction decoder
- [x] Register file (x0–x31)
- [x] 64KB memory model
- [x] Single-cycle CPU
- [x] 5-stage pipeline
- [x] Hazard detection + stalls
- [x] Branch flush
- [x] Forwarding (EX→EX, MEM→EX)
- [x] 2-bit branch predictor
- [x] L1 cache simulator
- [x] Out-of-order execution (Tomasulo)
- [x] ELF binary loader
- [x] GDB-style debugger
- [x] Superscalar (2-wide issue)

---

## Why C++ over SystemVerilog?

This simulator focuses on **performance analysis and microarchitecture reasoning** rather than hardware implementation. C++ allows rapid experimentation with different designs and direct measurement of CPI, stalls, and cache behaviour — proving not just "I built a CPU" but "I understand and can optimize how CPUs perform."

---

## Author

Darren Brazas
