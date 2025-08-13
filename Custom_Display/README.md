# 📢 ESP32 Bluetooth LED Matrix Display (8x32) with EEPROM

A **Bluetooth-controlled scrolling LED matrix display** built using:
- **ESP32 (30-pin)**
- **4x 8x8 LED modules (FC16)** → 8x32 display
- **Bluetooth Serial (BT Classic)**
- **EEPROM** (for saving message, speed, brightness)
- **MD_Parola Library**

Perfect for DIY signs, notifications, or smart displays.

---

## 🎯 Features
- ✅ **Bluetooth control** via serial app (e.g., "Serial Bluetooth Terminal")
- ✅ **Save settings & message in EEPROM** – survives power loss
- ✅ **Adjust scroll speed (1–100)** and **brightness (0–100)**
- ✅ **Remote restart** (`R` command)
- ✅ **Status feedback** (`w` command)
- ✅ **Auto-load saved data on boot**

---

## 🧰 Hardware Required

| Component | Notes |
|--------|------|
| ESP32 Dev Board (30-pin) | WROOM/WROVER |
| 8x32 LED Matrix | Made from 4x 8x8 modules (FC16 type) |
| Breadboard & Jumper Wires | — |
| 3.3V Power Supply | At least 1A for stable display |

---

## 🔌 Wiring (ESP32 to MAX7219/FC16)

| FC16 Pin | ESP32 GPIO |
|--------|----------|
| VCC    | 3.3V     |
| GND    | GND      |
| DIN    | GPIO23 (MOSI) |
| CLK    | GPIO18 (SCK)  |
| CS     | GPIO5    |

> ✅ Uses **Hardware SPI** – efficient and stable.

---

## 📱 Bluetooth Commands

Send messages in format:  
`/SPEED/NEW MESSAGE,`

### Examples:

/150/Welcome!,

→ Sets speed to 50, message to "Hello World"

→ Sets brightness to 49 (150–101), message to "Welcome!"

### Special Commands:
- `R` → Restart ESP32
- `w` → Get current status: `SAVED_TEXT/SPEED/BRIGHTNESS/`

---

## ⚙️ Settings Range
| Setting | Range |
|-------|-------|
| Speed | 1 (fastest) to 100 (slowest) |
| Brightness | 101–201 → maps to 0–100 (sent as 101+value) |
| Message | Up to 99 characters |

---

## 📦 Libraries Required

Install via **Arduino Library Manager**:
- `BluetoothSerial` (for ESP32)
- `MD_Parola` – by Marco Schwartz
- `MD_MAX72XX` – required by Parola

> 🔗 [MD_Parola GitHub](https://github.com/MajicDesigns/MD_Parola)

---

## 🚀 How to Use

1. Upload the code to ESP32.
2. Open **Serial Monitor** to see boot logs.
3. Pair with **"LED_MATRIX_DISPLAY"** via Bluetooth.
4. Use a Bluetooth serial app to send commands.
5. Message and settings are saved automatically.

---

## 🛠 Troubleshooting

| Issue | Solution |
|------|----------|
| Blank display | Check wiring, contrast, power |
| Text not saving | Ensure `EEPROM.commit()` is called |
| Bluetooth not pairing | Restart ESP32 or clear Bluetooth cache |
| Flickering | Use external 3.3V power (USB may not be enough) |

---

## 📂 Project Files
- `ESP32_LEDMatrix_Bluetooth.ino` – Main code
- `README.md` – This file

---

## 🤝 Contributing
PRs welcome! Add features like:
- Wi-Fi + Web interface
- Multiple zones
- Font selection
- Animation effects

## 📄 License
MIT – Free to use, modify, and share.

---

💡 **Made by Abhinav**  
"From Idea To Execution" 🚀