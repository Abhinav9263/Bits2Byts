#include "BluetoothSerial.h"
#include "EEPROM.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// === DEBUG MODE ===
#define DEBUG 0

// === HARDWARE CONFIGURATION ===
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // FC16 board type (common for 4-in-1 8x8 modules)
#define MAX_DEVICES 4                     // 4 modules = 8x32 display
#define CLK_PIN   18                      // SPI SCK
#define DATA_PIN  23                      // SPI MOSI
#define CS_PIN    5                       // SPI SS (CS)

// === BLUETOOTH & EEPROM ===
BluetoothSerial ESP_BT;
#define EEPROM_SIZE 512

// === GLOBAL VARIABLES ===
int m = 0;                                // Message parsing state
int SCROLL_SPEED = 30;                    // Default scroll speed (lower = faster)
int contrast = 0;                         // Brightness level (0–4)
int state = 0;
char incoming;
String readString1 = "";                  // For settings
String readString2 = "";                  // For new message
String lastvalue = "";                    // Status string sent back

// === DISPLAY OBJECT (Uses Hardware SPI) ===
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// === MESSAGE BUFFER ===
char msg[100] = "Welcome to LED Matrix";

// === SETUP ===
void setup() {
  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Start Serial and Bluetooth
  Serial.begin(115200);
  ESP_BT.begin("LED_MATRIX_DISPLAY");  // Bluetooth device name

  // Initialize LED Matrix
  P.begin();
  P.setIntensity(contrast);
  P.setCharSpacing(P.getCharSpacing() * 2);  // Wider spacing for better readability

  // === Load Saved Data from EEPROM ===

  // Load message
  String savedText = EEPROM.readString(50);
  if (savedText == "" || savedText == "default") {
    savedText = "ABHINAV - From Idea To Execution";
  }
  strcpy(msg, savedText.c_str());
  Serial.println("Loaded Text: " + savedText);

  // Load scroll speed (1–100)
  int savedSpeed = EEPROM.readInt(20);
  if (savedSpeed >= 1 && savedSpeed <= 100) {
    SCROLL_SPEED = 100 - savedSpeed;  // Invert: higher value = slower
  } else {
    SCROLL_SPEED = 30;  // Default
  }
  Serial.print("Loaded Speed: ");
  Serial.println(SCROLL_SPEED);

  // Load brightness (0–100)
  int savedBrightness = EEPROM.readInt(25);
  if (savedBrightness >= 0 && savedBrightness <= 100) {
    contrast = savedBrightness / 20;  // Scale 0–100 → 0–4
  } else {
    contrast = 2;  // Default
  }
  P.setIntensity(contrast);
  Serial.print("Loaded Brightness: ");
  Serial.println(contrast);
}

// === MAIN LOOP ===
void loop() {
  lastvalue = "";  // Reset status
  currentstatus(); // Build current status string

  if (ESP_BT.available()) {
    while (ESP_BT.available()) {
      incoming = (char)ESP_BT.read();
      Serial.print("Received: ");
      Serial.println(incoming);

      // === Special Commands ===
      if (incoming == 'R') {
        ESP_BT.println("Restarting...");
        ESP.restart();
      }

      if (incoming == 'w') {
        ESP_BT.println(lastvalue);  // Send current status
        return;
      }

      // === Message Parsing: Format "/SPEED/TEXT," ===
      if (incoming == '/') {
        m++;
      } else if (m == 1) {
        readString1 += incoming;  // Speed/Brightness
      } else if (m >= 2 && incoming != ',') {
        if (incoming == '/') {
          m++;  // Support future extensions
        } else {
          readString2 += incoming;  // Message
        }
      }
    }

    // === Save New Text ===
    if (readString2.length() > 0) {
      if (readString2.length() < 99) {
        EEPROM.writeString(50, readString2);
        EEPROM.commit();
        strcpy(msg, readString2.c_str());
        P.displayReset();  // Clear and restart animation
        Serial.println("New message saved: " + readString2);
      }
    }

    // === Save New Settings ===
    if (readString1.length() > 0) {
      int val = readString1.toInt();

      // Scroll Speed: 1–100
      if (val >= 1 && val <= 100) {
        SCROLL_SPEED = 100 - val;
        EEPROM.writeInt(20, val);
        EEPROM.commit();
        P.displayReset();
        Serial.print("New speed set: ");
        Serial.println(SCROLL_SPEED);
      }

      // Brightness: 101–201 → maps to 0–100
      else if (val >= 101 && val <= 201) {
        int brightness = val - 101;
        contrast = brightness / 20;  // 0–4
        P.setIntensity(contrast);
        EEPROM.writeInt(25, brightness);
        EEPROM.commit();
        Serial.print("Brightness set: ");
        Serial.println(brightness);
      }

      // Reset for next input
      readString1 = "";
      readString2 = "";
      m = 0;
    }
  }

  // Animate display
  printdis();
}

// === Display Animation ===
void printdis() {
  if (P.getZoneStatus(0)) {
    P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    P.displayText(msg, PA_LEFT, SCROLL_SPEED, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
  P.displayAnimate();
}

// === Send Current Status ===
void currentstatus() {
  lastvalue = "";
  lastvalue += EEPROM.readString(50);
  lastvalue += "/";
  lastvalue += String(EEPROM.readInt(20));
  lastvalue += "/";
  lastvalue += String(EEPROM.readInt(25));
  lastvalue += "/";
}