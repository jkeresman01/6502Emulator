<div align="center">

  <h1>🧠 6502 emulator. </h1>
  <h6> ---> This is custom 6502 emulator. <--- </h6>

![C++](https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c%2B%2B)
![Work In Progress](https://img.shields.io/badge/Work%20In%20Progress-orange?style=for-the-badge)

</div>

## 6502 Emulator Memory Map

---

## 📦 Full Memory Layout

| Address Range       | Size         | Description                          |
|---------------------|--------------|--------------------------------------|
| `$0000 – $00FF`     | 256 bytes    | Zero Page                            |
| `$0100 – $01FF`     | 256 bytes    | **Stack** (used by Stack Pointer)    |
| `$0200 – $05FF`     | 1024 bytes   | **Pixel Display Memory**             |
| `$0600 – $0601`     | 2 bytes      | **LED Display** (16 LEDs total)      |
| `$0602 – $0605`     | 4 bytes      | **7-Segment HEX Display** (4 digits) |
| `$0606`             | 2 bytes      | **Switch Panel** (10 bits + "All")   |
| `$0608+`            | Reserved     | (Push buttons / IRQs / Future I/O)   |
| `$0700 – $7FFF`     | Free / RAM   | General purpose RAM or programs      |
| `$8000 – $FFFF`     | 32KB         | ROM / Cartridge / Program Code       |

---

## 🔌 I/O Devices (`$0600` and up)

| Address       | Device                  | Description                               |
|---------------|--------------------------|-------------------------------------------|
| `$0600`       | LED Lower Byte           | LEDs 0–7 (1 bit each)                     |
| `$0601`       | LED Upper Byte           | LEDs 8–15 (1 bit each)                    |
| `$0602 – $0605` | HEX 7-Segment Display  | 4 digits, 1 byte per digit (0x0–0xF)      |
| `$0606`       | Switches                | 10-bit toggle switches (bits 0–9)         |
| `$0607`       | (Reserved)              | Reserved / Padding                        |
| `$0608+`      | Future I/O              | Push buttons, interrupts, etc. (planned)  |

---


## 📦 CPU Registers

| Name | Full Name        | Size    | Description                         |
|------|------------------|---------|-------------------------------------|
| PC   | Program Counter  | 16-bit  | Points to the next instruction      |
| AC   | Accumulator      | 8-bit   | Used for arithmetic and logic ops   |
| X    | X Register       | 8-bit   | General-purpose / indexing          |
| Y    | Y Register       | 8-bit   | General-purpose / indexing          |
| SR   | Status Register  | 8-bit   | Processor flags: `N V - B D I Z C`  |
| SP   | Stack Pointer    | 8-bit   | Stack offset from `$0100` base      |


## 📦 Instruction set

Not all instructions are implemented in current stage

| Mnemonic | Description |
|----------|------------|
| **ADC**  | Add with carry |
| **AND**  | And (with accumulator) |
| **ASL**  | Arithmetic shift left |
| **BCC**  | Branch on carry clear |
| **BCS**  | Branch on carry set |
| **BEQ**  | Branch on equal (zero set) |
| **BIT**  | Bit test |
| **BMI**  | Branch on minus (negative set) |
| **BNE**  | Branch on not equal (zero clear) |
| **BPL**  | Branch on plus (negative clear) |
| **BRK**  | Break / interrupt |
| **BVC**  | Branch on overflow clear |
| **BVS**  | Branch on overflow set |
| **CLC**  | Clear carry |
| **CLD**  | Clear decimal |
| **CLI**  | Clear interrupt disable |
| **CLV**  | Clear overflow |
| **CMP**  | Compare (with accumulator) |
| **CPX**  | Compare with X |
| **CPY**  | Compare with Y |
| **DEC**  | Decrement |
| **DEX**  | Decrement X |
| **DEY**  | Decrement Y |
| **EOR**  | Exclusive OR (with accumulator) |
| **INC**  | Increment |
| **INX**  | Increment X |
| **INY**  | Increment Y |
| **JMP**  | Jump                          |
| **JSR**  | Jump subroutine               |
| **LDA**  | Load accumulator              |
| **LDX**  | Load X                        |
| **LDY**  | Load Y                        |
| **LSR**  | Logical shift right           |
| **NOP**  | No operation                  |
| **ORA**  | OR with accumulator           |
| **PHA**  | Push accumulator              |
| **PHP**  | Push processor status (SR)    |
| **PLA**  | Pull accumulator              |
| **PLP**  | Pull processor status (SR)    |
| **ROL**  | Rotate left                   |
| **ROR**  | Rotate right                  |
| **RTI**  | Return from interrupt         |
| **RTS**  | Return from subroutine        |
| **SBC**  | Subtract with carry           |
| **SEC**  | Set carry                     |
| **SED**  | Set decimal                   |
| **SEI**  | Set interrupt disable         |
| **STA**  | Store accumulator             |
| **STX**  | Store X                       |
| **STY**  | Store Y                       |
| **TAX**  | Transfer accumulator to X     |
| **TAY**  | Transfer accumulator to Y     |
| **TSX**  | Transfer stack pointer to X   |
| **TXA**  | Transfer X to accumulator     |
| **TXS**  | Transfer X to stack pointer   |
| **TYA**  | Transfer Y to accumulator     |

## 📦 Addressing modes

//TODO


## 📌 General Notes

- **Stack** grows downward from `$01FF` to `$0100`.
- **Pixel display** memory is read by the graphics renderer.
- **Switches and LEDs** are user-controlled I/O for interactivity and testing.
- Memory beyond `$0608` is currently unassigned but reserved for expansion.
