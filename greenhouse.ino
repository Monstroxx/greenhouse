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
const int servoPin = 3;
const int rele_pin = 7;
const uint8_t soil_moisture_pin = A6;

// Settings
const int max_temp = 25;
const int min_temp = 18;
const int temp_margin = 2;

const int window_close_pos = 90;
const int window_open_pos = 180;

// TODO: globals -> local machen
const char* lighttext = "off";
int window_angle = 0;
long soil = 0;

float temp = 0.0;
float hum = 0.0;
float pres = 0.0;

bool discoEnabled = false;
bool displayPage = false;
float discoHue = 0.0f;

unsigned long lastSensorMs = 0;
unsigned long lastDisplayMs = 0;
unsigned long lastDiscoMs = 0;

const unsigned long SENSOR_INTERVAL_MS = 1000;
const unsigned long DISPLAY_INTERVAL_MS = 1000;
const unsigned long DISCO_INTERVAL_MS = 10;

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
      //throw 404;
    }
  }

  setupdisplay();

  pinMode(rele_pin, OUTPUT);
  digitalWrite(rele_pin, HIGH); // Pumpe aus beim Start

  pinMode(light_sensor_pin, INPUT);

  pinMode(soil_moisture_pin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Add Servo to WindowServo
  WindowServo.attach(servoPin);
  window_angle = 90;
}

void loop() {
  unsigned long now = millis();

  if (now - lastSensorMs >= SENSOR_INTERVAL_MS) {
    lastSensorMs = now;

    // Read BME 280 Sensor
    temp = bme.readTemperature();
    hum = bme.readHumidity();
    pres = bme.readPressure() / 100.0; // hPa

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
  }

  if (discoEnabled && (now - lastDiscoMs >= DISCO_INTERVAL_MS)) {
    lastDiscoMs = now;
    discoStep();
  }

  if (now - lastDisplayMs >= DISPLAY_INTERVAL_MS) {
    lastDisplayMs = now;
    displayPage = !displayPage;

    if (!displayPage) {
      showtext("S: " + String(soil) + " L: " + String(lighttext), false);
    } else {
      showtext("T: " + String(temp, 1) + " H: " + String(hum, 1), false);
    }
  }
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
    lighttext = "off";
    discoEnabled = true;
  }
  else{
    lighttext = "on";
    discoEnabled = false;
    setColor(0,0,0);
  }
  Serial.print("Light sensor value: ");
  Serial.println(lighttext);
}

void showtext(String text, bool scroll) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();      // Show initial text

  if (scroll) {
    display.startscrollleft(0x00, 0x0F);
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

void discoStep() {
  int r, g, b;

  hsvToRgb(discoHue, 1.0, 1.0, r, g, b);

  // optional: verhindert hartes "Einspringen" von Blau bei billigen LEDs
  if (b > 0 && b < 5)
    b = 5;

  setCorrectedRgb(r, g, b);

  discoHue += 0.001f;
  if (discoHue >= 1.0f) {
    discoHue = 0.0f;
  }
}
