# AI-Enhanced Hybrid Indoor Localization System

## 📌 Project Overview
This is a hardware prototype designed to estimate a user's indoor position without relying on GPS. The system uses fixed RF beacon transmitters at known locations and applies sensor fusion techniques on an ESP32 microcontroller to provide accurate real-time location tracking.

## 🛠️ Hardware Components
* **Microcontroller:** ESP32
* **RF Transceiver:** nRF24L01+ (SPI Interface)
* **Inertial Sensors:** ADXL345 Accelerometer & L3G4200D Gyroscope (I2C Interface)
* **Display:** 16x2 LCD with I2C Module
* **Power Supply:** 18650 Li-ion Battery with Power Management Module

## 🚀 Key Features
1. **RSSI-Based Zone Detection:** Detects the active beacon zone using Received Signal Strength Indicator (RSSI) from the nRF24L01+ module.
2. **Sensor Fusion:** Combines beacon-zone data with accelerometer and gyroscope inputs to track movement between beacon locations, reducing inertial drift.
3. **Edge AI / TinyML Ready:** Firmware is designed to be easily extensible for on-device machine learning models.
4. **Real-Time Display:** Live location and movement status are updated continuously on the 16x2 LCD.

## ⚙️ Circuit Connections
| Component | ESP32 Pin |
| :--- | :--- |
| nRF24L01+ CE / CSN | GPIO 22 / GPIO 21 |
| nRF24L01+ MOSI/MISO/SCK | GPIO 23 / GPIO 19 / GPIO 18 |
| ADXL345 SDA / SCL | GPIO 21 / GPIO 22 |
| 16x2 LCD SDA / SCL | GPIO 21 / GPIO 22 |
