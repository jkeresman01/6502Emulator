<div align="center">

  <h1>  6502 emulator. </h1>
  <h3> !!!!!!!   Not baked yet   !!!!!!! </h3>
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

## 📦 Number Notation

| Notation   | Example    | Meaning                        |
|------------|------------|--------------------------------|
| `$`        | `$20`      | Hexadecimal (base 16)          |
| `%`        | `%10101010`| Binary (base 2)                |
| `#`        | `#$20`     | Immediate value (literal byte) |
| Decimal    | `42`       | Interpreted as decimal         |
| `'A'`      | `'A'`      | ASCII character → byte value   |

---

## 📦 6502 Addressing Modes (with Examples)

| Mode                | Syntax         | Example         | Description                                                 |
|---------------------|----------------|------------------|-------------------------------------------------------------|
| **Immediate**        | `#value`       | `LDA #$01`       | Load literal value directly                                 |
| **Zero Page**        | `addr`         | `LDA $10`        | Load from zero page address (`$0000–$00FF`)                 |
| **Zero Page,X**      | `addr,X`       | `LDA $10,X`      | Zero page address + X register                              |
| **Zero Page,Y**      | `addr,Y`       | `LDX $10,Y`      | Zero page address + Y register                              |
| **Absolute**         | `addr`         | `LDA $1234`      | Load from 16-bit address                                    |
| **Absolute,X**       | `addr,X`       | `LDA $1234,X`    | Absolute address offset by X                                |
| **Absolute,Y**       | `addr,Y`       | `LDA $1234,Y`    | Absolute address offset by Y                                |
| **Indirect**         | `(addr)`       | `JMP ($1234)`    | Jump to address stored at address (used only with `JMP`)    |
| **Indexed Indirect** | `(addr,X)`     | `LDA ($20,X)`    | Add X to zero page address, then load from resulting address |
| **Indirect Indexed** | `(addr),Y`     | `LDA ($20),Y`    | Read address from zero page, then add Y offset              |
| **Accumulator**      | (implicit)     | `ASL`            | Operates directly on accumulator (A)                        |
| **Implied**          | (no operand)   | `CLC`            | Instruction has no operand                                  |
| **Relative**         | (label/offset) | `BEQ label`      | Used with branches (offset from PC)                         |

---
