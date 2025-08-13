# 🌡️ ESP Weather Meter — Temperature & Humidity Display

A simple **ESP8266/ESP32** project that reads **temperature** and **humidity** from a **DHT11 sensor** and displays it on a **16x2 I2C LCD**.  
Perfect for learning IoT basics or building your own room weather station.  

---

## 📷 Project Overview
- Reads **temperature (°C)** and **humidity (%)** every 2 seconds.
- Displays readings on a **16x2 I2C LCD**.
- Shows live data in the **Serial Monitor**.
- Handles sensor read errors gracefully.

---

## 🛠 Hardware Requirements
| Component             | Quantity | Notes |
|-----------------------|----------|-------|
| ESP8266 (NodeMCU) or ESP32 | 1 | Main microcontroller |
| DHT11 Temperature & Humidity Sensor | 1 | Can also use DHT22 |
| 16x2 LCD with I2C module | 1 | Address usually `0x27` or `0x3F` |
| Jumper wires           | As needed | For connections |
| Breadboard (optional)  | 1 | For prototyping |

---

## 📦 Library Dependencies
Install the following libraries in Arduino IDE (**Sketch → Include Library → Manage Libraries...**):

- **Wire** (built-in) — I2C communication
- **LiquidCrystal_I2C**  
- **DHT sensor library** by Adafruit  

---

## 🔌 Wiring Diagram

**ESP8266 Pinout**  
| DHT11 Pin | ESP8266 Pin |
|-----------|-------------|
| VCC       | 3V3         |
| GND       | GND         |
| Data      | D4 (GPIO4)  |

**I2C LCD Pinout (ESP8266)**  
| LCD Pin | ESP8266 Pin |
|---------|-------------|
| SDA     | D2 (GPIO4)  |
| SCL     | D1 (GPIO5)  |
| VCC     | 5V / 3V3    |
| GND     | GND         |

For **ESP32**, use:
- SDA = GPIO21  
- SCL = GPIO22  


## 📜 Code Explanation
### Main Features:
1. **Setup**
   - Initializes serial communication.
   - Starts DHT11 sensor and LCD.
   - Shows splash screen.
   
2. **Loop**
   - Reads temperature & humidity every 2 seconds.
   - Displays values on LCD.
   - Prints readings to Serial Monitor.
   - Displays "ERR" if sensor read fails.

3. **LCD Update**
   - Clears old values before writing new ones.
   - Shows temperature with °C symbol and humidity with %.



## 🚀 Getting Started
1. Connect your hardware as per wiring diagram.
2. Install required libraries.
3. Copy this code into Arduino IDE.
4. Select your **board** and **COM port**.
5. Upload and open Serial Monitor (`115200 baud`).



## 🖼️ Output Preview
**Serial Monitor**
🌡️ Temp: 28.3°C | 💧 Humidity: 65.0%
🌡️ Temp: 28.5°C | 💧 Humidity: 64.8%



**LCD Display**
Temp: 28.3°C
Humidity: 65.0%


## ⚠️ Notes
- If LCD shows nothing, try changing the I2C address in:
  ```cpp
  LiquidCrystal_I2C lcd(0x27, 16, 2);
to:



LiquidCrystal_I2C lcd(0x3F, 16, 2);
You can also use DHT22 for better accuracy, just change:


#define DHT_TYPE DHT22
📄 License
This project is licensed under the MIT License — feel free to modify and share.

