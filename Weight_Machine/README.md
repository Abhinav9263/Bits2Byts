# ESP8266 Weight Scale with HX711 & I2C LCD

A simple yet effective digital weight scale built using **ESP8266**, **HX711 Load Cell Amplifier**, and an **I2C LCD display**. This project reads weight from a load cell, displays it on a 16x2 LCD, and outputs debug data via Serial Monitor.

## 📋 Features
- Real-time weight measurement using HX711 and load cell
- I2C LCD (16x2) for local display
- Serial debugging with periodic updates
- Auto-tare on startup
- Non-blocking updates (smooth performance)
- Built for ESP8266 (NodeMCU, Wemos D1, etc.)

## 🧰 Hardware Requirements
| Component               | Example Model |
|------------------------|-------------|
| ESP8266 Board          | NodeMCU, Wemos D1 Mini |
| HX711 Load Cell Amplifier | HX711 Module |
| Load Cell              | 5kg, 10kg, or 20kg (strain gauge) |
| I2C LCD (16x2)         | 1602 LCD with I2C adapter (PCF8574) |
| Breadboard & Jumper Wires | — |

## 🔌 Wiring Connections

| ESP8266 (NodeMCU) | HX711       | I2C LCD       |
|-------------------|------------|---------------|
| `D5` (GPIO14)     | `DOUT`     | —             |
| `D6` (GPIO12)     | `SCK`      | —             |
| `D1` (GPIO5)      | —          | `SCL`         |
| `D2` (GPIO4)      | —          | `SDA`         |
| `3.3V`            | `VCC` (HX711 & LCD) | `VCC` |
| `GND`             | `GND` (all components) | `GND` |

> ⚠️ **Note**: HX711 typically runs on 5V, but many modules work with 3.3V. For best results, power HX711 and load cell from 5V if available, and use a logic level shifter for DOUT if needed.

## 📦 Software Setup

### Libraries Required
- [**HX711 Arduino Library**](https://github.com/bogde/HX711) by Bogde
- [**Wire.h**](https://www.arduino.cc/en/Reference/Wire) (comes with IDE)
- [**LiquidCrystal_I2C**](https://github.com/marcoschwartz/LiquidCrystal_I2C)

Install via Arduino Library Manager:
Sketch → Include Library → Manage Libraries → Search and install

### I2C LCD Address
Most common I2C addresses: `0x27` or `0x3F`.  
If the LCD doesn’t display, try changing the address in code:
```cpp
LiquidCrystal_I2C lcd(0x3F, 16, 2);
🚀 How to Use
Upload the code to your ESP8266.
Open Serial Monitor at 115200 baud to view debug output.
The system will:
Initialize the LCD and HX711
Tare the scale (zero out)
Start displaying weight every 300ms
Place weight on the load cell to see readings.
🛠 Calibration
Upload the sketch without any weight (tare happens at startup).
Place a known weight (e.g., 500g).
Observe the Serial output.
Adjust the set_scale() factor:
scale.set_scale(450.0); // ← Change this value
Formula: calibration_factor = current_reading / known_weight
Example: If 500g reads as 600g → factor = 450 * (600 / 500) = 540
🖼 Demo Output
=== DEBUG MODE ===
Starting initialization...
LCD initialized
HX711 initialized
Tared - System ready
Update #1 - Weight: 0.00g
Update #2 - Weight: 0.10g
Update #3 - Weight: 498.50g
LCD Display:
Weight: 498.5g
🤝 Contributing
Feel free to fork, improve, and submit pull requests. Issues and suggestions are welcome!

📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
profile
Qwen3-235B-A22B-2507
7:54 pm
Absolutely! Below is the complete README.md content formatted so you can copy and paste it directly into a README.md file in your GitHub repository. Just copy everything from below and save it as README.md in your project folder.

markdown


1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
⌄
⌄
⌄
⌄
⌄
⌄
⌄
⌄
# ESP8266 Weight Scale with HX711 & I2C LCD

A simple yet effective digital weight scale built using **ESP8266**, **HX711 Load Cell Amplifier**, and an **I2C LCD display**. This project reads weight from a load cell, displays it on a 16x2 LCD, and outputs debug data via Serial Monitor.

## 📋 Features
- Real-time weight measurement using HX711 and load cell
- I2C LCD (16x2) for local display
- Serial debugging with periodic updates
- Auto-tare on startup
- Non-blocking updates (smooth performance)
- Built for ESP8266 (NodeMCU, Wemos D1, etc.)

## 🧰 Hardware Requirements
| Component               | Example Model |
|------------------------|-------------|
| ESP8266 Board          | NodeMCU, Wemos D1 Mini |
| HX711 Load Cell Amplifier | HX711 Module |
| Load Cell              | 5kg, 10kg, or 20kg (strain gauge) |
| I2C LCD (16x2)         | 1602 LCD with I2C adapter (PCF8574) |
| Breadboard & Jumper Wires | — |

## 🔌 Wiring Connections

| ESP8266 (NodeMCU) | HX711       | I2C LCD       |
|-------------------|------------|---------------|
| `D5` (GPIO14)     | `DOUT`     | —             |
| `D6` (GPIO12)     | `SCK`      | —             |
| `D1` (GPIO5)      | —          | `SCL`         |
| `D2` (GPIO4)      | —          | `SDA`         |
| `3.3V`            | `VCC` (HX711 & LCD) | `VCC` |
| `GND`             | `GND` (all components) | `GND` |

> ⚠️ **Note**: HX711 typically runs on 5V, but many modules work with 3.3V. For best results, power HX711 and load cell from 5V if available, and use a logic level shifter for DOUT if needed.

## 📦 Software Setup

### Libraries Required
- [**HX711 Arduino Library**](https://github.com/bogde/HX711) by Bogde
- [**Wire.h**](https://www.arduino.cc/en/Reference/Wire) (comes with IDE)
- [**LiquidCrystal_I2C**](https://github.com/marcoschwartz/LiquidCrystal_I2C)

Install via Arduino Library Manager:
Sketch → Include Library → Manage Libraries → Search and install



1
2
3
4
5
6

### I2C LCD Address
Most common I2C addresses: `0x27` or `0x3F`.  
If the LCD doesn’t display, try changing the address in code:
```cpp
LiquidCrystal_I2C lcd(0x3F, 16, 2);
🚀 How to Use
Upload the code to your ESP8266.
Open Serial Monitor at 115200 baud to view debug output.
The system will:
Initialize the LCD and HX711
Tare the scale (zero out)
Start displaying weight every 300ms
Place weight on the load cell to see readings.
🛠 Calibration
Upload the sketch without any weight (tare happens at startup).
Place a known weight (e.g., 500g).
Observe the Serial output.
Adjust the set_scale() factor:
cpp


1
scale.set_scale(450.0); // ← Change this value
Formula: calibration_factor = current_reading / known_weight
Example: If 500g reads as 600g → factor = 450 * (600 / 500) = 540
🖼 Demo Output


1
2
3
4
5
6
7
8
=== DEBUG MODE ===
Starting initialization...
LCD initialized
HX711 initialized
Tared - System ready
Update #1 - Weight: 0.00g
Update #2 - Weight: 0.10g
Update #3 - Weight: 498.50g
LCD Display:



1
Weight: 498.5g
🤝 Contributing
Feel free to fork, improve, and submit pull requests. Issues and suggestions are welcome!

📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

Made with ❤️ for makers and tinkerers.

---

✅ **Done!**  
Now just:
1. Create a new GitHub repository.
2. Create a file named `README.md`.
3. Paste the above content.
4. Add your Arduino `.ino` file.
5. Push to GitHub!

Let me know if you'd like me to generate:
- A `LICENSE` file (MIT)
- A `.gitignore` for Arduino
- A wiring diagram in text or Markdown

Happy coding! 🚀