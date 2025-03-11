# 📌 IoT Sensor Monitoring 
```cpp
Name : Ananda Setiawati Abidin  
NIM : 233140707111122  
Information Technology  
University of Brawijaya  
```

# 🌡️ IoT Sensor Monitoring with ESP32 
This project monitors temperature, humidity, and light intensity using ESP32, DHT22, and LDR sensors. 
The data is displayed on an LCD 16x2 and can be monitored in real-time using the Wokwi Simulator. 

# 🔧 Features 
1. Uses ESP32 as the main microcontroller
2. DHT22 for temperature and humidity sensing 🌡️
3. LDR sensor for measuring light intensity 💡
4. LCD 16x2 with I2C module for data display
5. Runs on Wokwi Simulator without physical hardware

# 🖥️ Wokwi Diagram 

# 💡 How It Works? 

1. DHT22 sensor reads temperature and humidity data.
2. LDR sensor measures light intensity.
3. ESP32 processes the data and sends it to LCD 16x2.
4. The data updates every 2 seconds to reflect real-time readings.

# 📜 ESP32 Code 
```cpp 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Ubah ke 0x3F kalau perlu

// Inisialisasi sensor DHT22
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi LDR
#define LDR_PIN 34

// Variabel untuk ganti tampilan
bool tampilanSuhu = true;  // Awalnya tampil suhu & kelembaban

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi LCD
  lcd.init();
  delay(500);
  lcd.backlight();
  
  // Inisialisasi DHT22
  dht.begin();

  // Tampilkan pesan awal
  lcd.setCursor(0, 0);
  lcd.print("Mengukur...");
}

void loop() {
  // Baca data dari sensor
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  int cahaya = analogRead(LDR_PIN);

  // Konversi cahaya ke persen (0-100%)
  int cahayaPersen = map(cahaya, 0, 4095, 0, 100);

  // Cek apakah data valid
  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Gagal membaca DHT22!");
    lcd.setCursor(0, 0);
    lcd.print("DHT22 Error!   ");
    delay(2000);
    return;
  }

  // Bersihkan LCD sebelum menampilkan data
  lcd.clear();

  // Ganti tampilan setiap 3 detik
  if (tampilanSuhu) {
    // Tampilkan Suhu & Kelembaban
    lcd.setCursor(0, 0);
    lcd.print("Suhu: ");
    lcd.print(suhu);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Kelembaban: ");
    lcd.print(kelembaban);
    lcd.print(" %");

    Serial.print("Suhu: "); Serial.print(suhu); Serial.print(" C, ");
    Serial.print("Kelembaban: "); Serial.print(kelembaban); Serial.println(" %");

  } else {
    // Tampilkan Cahaya
    lcd.setCursor(0, 0);
    lcd.print("Cahaya: ");
    lcd.print(cahayaPersen);
    lcd.print(" %");

    Serial.print("Cahaya: "); Serial.print(cahayaPersen); Serial.println(" %");
  }

  // Tunggu 3 detik lalu ubah tampilan
  delay(3000);
  tampilanSuhu = !tampilanSuhu;  // Flip tampilan
}

```
# 🚀 How to Run in Wokwi 
1. Open Wokwi ESP32 Simulator
2. Create a new project and select ESP32
3. Copy and paste the JSON diagram into diagram.json
4. Copy and paste the C++ code into main.cpp
5. Click the RUN ▶️ button to start the simulation

# 📌 Conclusion 
This project successfully demonstrates IoT-based environmental monitoring using ESP32.
With the Wokwi Simulator, we can visualize sensor readings in real-time without requiring physical hardware! 🚀💡

