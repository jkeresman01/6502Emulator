# 🧠 6502 Emulator Memory Map

This is custom 6502 emulator. 

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

## 📌 Notes

- **Stack** grows downward from `$01FF` to `$0100`.
- **Pixel display** memory is read by the graphics renderer.
- **Switches and LEDs** are user-controlled I/O for interactivity and testing.
- Memory beyond `$0608` is currently unassigned but reserved for expansion.
