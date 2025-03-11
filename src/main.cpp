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
