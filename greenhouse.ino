#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Servo
#include <Servo.h> // Library: "Servo" by Michael Margolis

// BME 280 Sensor
#include <Adafruit_Sensor.h> // Library: '"Adafruit BME280 Library" by Adafruit' / '"Adafruit Unified Sensor" by Adafruit'
#include <Adafruit_BME280.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Defining soil moisture reading threshold
// From 0 to 400 - wet soil
// Above 400 - dry soil
#define MOISTURE_THRESHOLD 400

// Pins
const int redPin = 9;
const int greenPin = 6;
const int bluePin = 5;

const int light_sensor_pin = 2;
const int servoPin = 4;
const int rele_pin = 7;
const uint8_t soil_moisture_pin = A6;

// Settings
const int max_temp = 25;
const int min_temp = 18;
const int temp_margin = 2;

const int window_close_pos = 90;
const int window_open_pos = 180;

// TODO: globals -> local machen
String lighttext = "";
int window_angle = 0;
long soil = 0;

Servo WindowServo;
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);

  // Start BME Sensor and check for errors
  if (!bme.begin(0x76)) // manchmal 0x77
  {
    Serial.println("BME280 nicht gefunden!");
    while (1)
    {
      Serial.println("BME280 nicht gefunden! Bitte fixen und neustarten.");
      throw 404;
    }
  }

  digitalWrite(rele_pin, HIGH);  // Pumpe aus beim Start

  setupdisplay();

  pinMode(rele_pin, OUTPUT);
  digitalWrite(rele_pin, LOW);

  pinMode(soil_moisture_pin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Add Servo to WindowServo
  WindowServo.attach(servoPin);
  window_angle = 90;
}

void loop() {
  // Read BME 280 Sensor
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0; // hPa

  // Window management
  if (temp > max_temp - temp_margin)
  { // To hot
    window_angle = window_open_pos;
  }
  else if (temp < min_temp + temp_margin)
  { // To cold
    window_angle = window_close_pos;
  }

  WindowServo.write(window_angle);

  measureandpour();

  lightcontrol();

  showtext(String(soil)+" "+String(lighttext), false);

  delay(1000);
}

void setupdisplay(void) {
  // Wait for display
  delay(500);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  display.display();
}

void measureandpour(void) {
  soil = 0;
  for (int i = 0; i < 100; i++) {
    soil += analogRead(soil_moisture_pin);
  }
  soil = soil / 100;

  // Print the sensor reading values
  Serial.print("Soil moisture sensor value: ");
  Serial.println(soil);

  if (soil > MOISTURE_THRESHOLD) {
    // Turn on the water pump
    digitalWrite(rele_pin, LOW);
  } else {
    // Turn off the water pump
    digitalWrite(rele_pin, HIGH);
  }
}

void lightcontrol(void) {
  int light = digitalRead(light_sensor_pin);
  if (light == HIGH){ // in front of it
    lighttext = "DARK";
    discoFade(5);
  }
  else{
    lighttext = "LIGHT";
  }
  Serial.print("Light sensor value: ");
  Serial.println(lighttext);
}

void showtext(String text, bool scroll) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(text);
  display.display();      // Show initial text
  delay(100);

  if (scroll) {
    display.startscrollright(0x00, 0x0F);
    delay(2000);
  }
}

void setColor(int redValue, int greenValue, int blueValue) // Only for high quality LEDs
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// Gamma-Korrektur
int gammaCorrect(int value)
{
  float normalized = value / 255.0;       // (0 - 255) to (0.0 - 1.0)
  float corrected = pow(normalized, 2.2); // Flat curve to Exponentially like curve
  return (int)(corrected * 255.0 + 0.5);  // Back to (0 - 255)
}

// Setzt die LED direkt (mit Gamma)
void setCorrectedRgb(int r, int g, int b) // Use for new LEDs
{
  analogWrite(redPin, gammaCorrect(r));
  analogWrite(greenPin, gammaCorrect(g));
  analogWrite(bluePin, gammaCorrect(b));
}

void discoFade(int wait) { // Redundanz

  // Rot -> Gelb
  for(int g = 0; g <= 255; g++){
    setColor(255, g, 0);
    delay(wait);
  }

  // Gelb -> Grün
  for(int r = 255; r >= 0; r--){
    setColor(r, 255, 0);
    delay(wait);
  }

  // Grün -> Cyan
  for(int b = 0; b <= 255; b++){
    setColor(0, 255, b);
    delay(wait);
  }

  // Cyan -> Blau
  for(int g = 255; g >= 0; g--){
    setColor(0, g, 255);
    delay(wait);
  }

  // Blau -> Magenta
  for(int r = 0; r <= 255; r++){
    setColor(r, 0, 255);
    delay(wait);
  }

  // Magenta -> Rot
  for(int b = 255; b >= 0; b--){
    setColor(255, 0, b);
    delay(wait);
  }
}


// ChatGPTs try of disco mode

// HSV -> RGB
void hsvToRgb(float h, float s, float v, int &r, int &g, int &b)
{
  int i = int(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  float rf, gf, bf;

  switch (i % 6)
  {
    case 0:
      rf = v;
      gf = t;
      bf = p;
      break;
    case 1:
      rf = q;
      gf = v;
      bf = p;
      break;
    case 2:
      rf = p;
      gf = v;
      bf = t;
      break;
    case 3:
      rf = p;
      gf = q;
      bf = v;
      break;
    case 4:
      rf = t;
      gf = p;
      bf = v;
      break;
    case 5:
      rf = v;
      gf = p;
      bf = q;
      break;
  }

  r = rf * 255;
  g = gf * 255;
  b = bf * 255;
}

void disco_mode()
{
  int r, g, b;

  for (float h = 0.0; h < 1.0; h += 0.001)
  {
    hsvToRgb(h, 1.0, 1.0, r, g, b);

    // optional: verhindert hartes "Einspringen" von Blau bei billigen LEDs
    if (b > 0 && b < 5)
      b = 5;

    setCorrectedRgb(r, g, b);
    delay(10);
  }
}
