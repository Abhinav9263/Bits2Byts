#include <HX711.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === PIN CONFIGURATION FOR ESP8266 ===
#define DOUT_PIN  D5  // HX711 DOUT pin - GPIO14
#define SCK_PIN   D6  // HX711 SCK pin - GPIO12

// I2C LCD (usually connects to D1 = SCL, D2 = SDA on ESP8266)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust address if needed (0x27 or 0x3F)

HX711 scale;

// Debug timing variables
unsigned long last_lcd_update = 0;
unsigned long last_serial_update = 0;
int update_counter = 0;

void setup() {
  // Start serial for debugging
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== DEBUG MODE ===");
  Serial.println("Starting initialization...");

  // Initialize I2C - SDA=D2 (GPIO4), SCL=D1 (GPIO5)
  Wire.begin(D2, D1);  // SDA, SCL for ESP8266
  delay(100);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.println("LCD initialized");
  lcd.setCursor(0, 0);
  lcd.print("DEBUG MODE");
  lcd.setCursor(0, 1);
  lcd.print("Init HX711...");

  // Initialize HX711
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_gain(128);
  scale.set_scale(450.0);  // Calibrate later

  delay(1000);

  // Check if HX711 is ready
  if (!scale.is_ready()) {
    Serial.println("HX711 NOT READY!");
    lcd.setCursor(0, 1);
    lcd.print("NO SENSOR!      ");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("HX711 initialized");
  lcd.setCursor(0, 1);
  lcd.print("Taring...");

  scale.tare();
  Serial.println("Tared - System ready");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight Scale");
  lcd.setCursor(0, 1);
  lcd.print("Ready...");

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight:");
}

void loop() {
  unsigned long current_time = millis();

  // Update Serial every 500ms
  if (current_time - last_serial_update >= 500) {
    last_serial_update = current_time;
    update_counter++;

    if (scale.is_ready()) {
      float weight = scale.get_units(3);  // Average of 3 readings

      Serial.print("Update #");
      Serial.print(update_counter);
      Serial.print(" - Weight: ");
      Serial.print(weight, 2);
      Serial.println("g");
    } else {
      Serial.println("HX711 NOT READY");
    }
  }

  // Update LCD every 300ms
  if (current_time - last_lcd_update >= 300) {
    last_lcd_update = current_time;

    if (scale.is_ready()) {
      float weight = scale.get_units(3);

      // Display weight on second line
      lcd.setCursor(0, 1);
      lcd.print("                ");  // Clear line
      lcd.setCursor(0, 1);
      lcd.print(weight, 1);  // One decimal place
      lcd.print("g");

      // Blinking update indicator
      lcd.setCursor(15, 1);
      lcd.print(update_counter % 2 ? "*" : " ");

    } else {
      lcd.setCursor(0, 1);
      lcd.print("SENSOR ERROR!   ");
    }
  }
}