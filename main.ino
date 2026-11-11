#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <LiquidCrystal_I2C.h>

// 1. Initialize RF Module (nRF24L01+)
RF24 radio(22, 21); // CE, CSN
const byte address[6] = "00001";

// 2. Initialize Sensors (Accelerometer & LCD)
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27

void setup() {
  Serial.begin(115200);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Booting..");

  // Initialize NRF24L01+
  if (!radio.begin()) {
    Serial.println("RF Module initialization failed!");
    lcd.setCursor(0, 1);
    lcd.print("RF Error");
    while (1);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Initialize ADXL345
  if (!accel.begin()) {
    Serial.println("No ADXL345 detected!");
    lcd.setCursor(0, 1);
    lcd.print("IMU Error");
    while (1);
  }

  lcd.clear();
  lcd.print("Init Complete");
  delay(1000);
  lcd.clear();
}

void loop() {
  String currentLocation = "Unknown";
  
  // STEP 1: Read Beacon Signal (Zone Detection)
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    
    // Process Beacon ID / RSSI mapping
    if(String(text) == "BEACON_A") {
       currentLocation = "Zone A";
    } else if (String(text) == "BEACON_B") {
       currentLocation = "Zone B";
    }
  }

  // STEP 2: Read IMU Data (Movement Detection)
  sensors_event_t event;
  accel.getEvent(&event);
  
  // Basic Sensor Fusion Logic: Check if moving
  bool isMoving = (abs(event.acceleration.x) > 0.5 || abs(event.acceleration.y) > 0.5);

  // STEP 3: Display Real-Time Status
  lcd.setCursor(0, 0);
  lcd.print("Loc: " + currentLocation + "    ");
  
  lcd.setCursor(0, 1);
  if(isMoving) {
    lcd.print("Status: Moving  ");
  } else {
    lcd.print("Status: Static  ");
  }

  delay(500);
}
