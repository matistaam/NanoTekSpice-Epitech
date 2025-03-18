# NanoTekSpice
A digital circuit simulator that supports various logic gates and complex components for simulating and testing digital circuits.

## 🚀 Features
- Simulation of digital circuits
- Multiple component types support
- Interactive shell interface
- Real-time circuit simulation
- Comprehensive error handling

## 📋 Supported Components

### Elementary Components
- AND (2 inputs, 1 output)
- OR (2 inputs, 1 output)
- XOR (2 inputs, 1 output)
- NOT (1 input, 1 output)

### Special Components
- Input (user-settable input)
- Output (display output)
- Clock (oscillating output)
- True (constant 1)
- False (constant 0)
- Logger (binary output logger)

### Gates Components (4000 series)
- 4001: Quad 2-input NOR gates
- 4011: Quad 2-input NAND gates
- 4030: Quad 2-input XOR gates
- 4069: Hex inverter
- 4071: Quad 2-input OR gates
- 4081: Quad 2-input AND gates

### Advanced Components
- 4008: 4-bit binary full adder
- 4013: Dual D-type flip-flop
- 4017: Decade counter with 10 decoded outputs
- 4040: 12-bit binary counter
- 4094: 8-bit shift register
- 4514: 4-bit latched/4-to-16 line decoder
- 2716: 16K (2K x 8) UV erasable PROM

## 🛠️ Building the Project
```sh
# Build the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Rebuild
make re
```

## 🚦 Usage
```sh
./nanotekspice circuit_file.nts
```

## 💻 Shell Commands
| Command | Description |
|---------|-------------|
| exit | Quit the program |
| display | Show current values of inputs/outputs |
| simulate | Simulate one tick of the circuit |
| loop | Run simulation continuously |
| input=value | Set input value (0: FALSE, 1: TRUE, U: UNDEFINED) |

## 📝 Circuit File Format
The circuit file (.nts) must contain two sections:
```
.chipsets
input in1
input in2
4081 and
output out

.links
in1:1 and:1
in2:1 and:2
and:3 out:1
```

## ⚠️ Error Handling
The simulator includes comprehensive error handling for:
- Invalid circuit files
- Unknown components
- Invalid pin numbers
- Duplicate component names
- Missing sections in circuit files
- Invalid input values

## 📄 Note
This project is part of the EPITECH curriculum and implements a digital circuit simulator following specific requirements and guidelines.