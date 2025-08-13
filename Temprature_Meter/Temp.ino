// === Include Required Libraries ===
#include <Wire.h>                  // I2C communication
#include <LiquidCrystal_I2C.h>     // For 16x2 I2C LCD
#include <DHT.h>                   // DHT sensor library

// === Pin & Sensor Configuration ===
#define DHT_PIN     D4             // GPIO4 on ESP8266/ESP32 (or use 4)
#define DHT_TYPE    DHT11          // Sensor type: DHT11

// === I2C LCD Settings ===
// Common addresses: 0x27 or 0x3F — try both if not working
LiquidCrystal_I2C lcd(0x27, 16, 2); // (address, cols, rows)

// === DHT Sensor Setup ===
DHT dht(DHT_PIN, DHT_TYPE);

// === Variables ===
float temperature = 0.0;
float humidity = 0.0;
unsigned long lastRead = 0;
const long READ_INTERVAL = 2000; // Read every 2 seconds

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  delay(500);

  Serial.println("\n=== TEMPERATURE & HUMIDITY METER ===");
  Serial.println("Initializing DHT11 and 16x2 I2C LCD...");

  // Initialize DHT sensor
  dht.begin();

  // Initialize I2C (SDA=SCL auto on ESP)
  Wire.begin(); // ESP8266: D2=SDA, D1=SCL | ESP32: GPIO21=SDA, GPIO22=SCL

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Splash screen
  lcd.setCursor(0, 0);
  lcd.print("  Weather Meter ");
  lcd.setCursor(0, 1);
  lcd.print("   Loading...   ");
  delay(1500);

  // Show static labels
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");

  Serial.println("System ready! Starting measurements...");
}

void loop() {
  unsigned long currentMillis = millis();

  // Read sensor only every 2 seconds
  if (currentMillis - lastRead >= READ_INTERVAL) {
    lastRead = currentMillis;

    // Read from DHT11
    humidity = dht.readHumidity();
    temperature = dht.readTemperature(); // in Celsius

    // Check for errors
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("❌ Failed to read from DHT sensor!");

      // Show error on LCD
      lcd.setCursor(7, 0);
      lcd.print("ERR");
      lcd.setCursor(9, 1);
      lcd.print("ERR");
      return;
    }

    // Print to Serial Monitor
    Serial.print("🌡️  Temp: ");
    Serial.print(temperature);
    Serial.print("°C | 💧 Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Update LCD display
    updateLCD();
  }
}

// === Function to update LCD ===
void updateLCD() {
  // Clear and update temperature line
  lcd.setCursor(6, 0);
  lcd.print("        "); // Clear old value
  lcd.setCursor(6, 0);
  lcd.print(temperature, 1); // 1 decimal place
  lcd.print((char)223); // Degree symbol (°)
  lcd.print("C");

  // Clear and update humidity line
  lcd.setCursor(9, 1);
  lcd.print("       "); // Clear old value
  lcd.setCursor(9, 1);
  lcd.print(humidity, 1);
  lcd.print("%");
}