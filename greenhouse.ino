#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Defining soil moisture reading threshold
// From 0 to 400 - wet soil
// Above 400 - dry soil
#define THRESHOLD 400
#define RELE_PIN 7 //Relè is connected to digital pin 7
#define SOIL_MOISTURE_PIN A6 //Soil moisture sensor connected to analog pin A6
long soil = 0;

int redPin = 9;
int greenPin = 6;
int bluePin = 5;

#define LIGHT_SENSOR_PIN 2
int light = 0;
String lighttext = "";

void setup() {
  Serial.begin(9600);

  digitalWrite(RELE_PIN, HIGH);  // Pumpe aus beim Start

  setupdisplay();

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);

  pinMode(SOIL_MOISTURE_PIN, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
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
    soil += analogRead(SOIL_MOISTURE_PIN);
  }
  soil = soil / 100;

  // Print the sensor reading values
  Serial.print("Soil moisture sensor value: ");
  Serial.println(soil);

  if (soil > THRESHOLD) {
    // Turn on the water pump
    digitalWrite(RELE_PIN, LOW);
  } else {
    // Turn off the water pump
    digitalWrite(RELE_PIN, HIGH);
  }
}

void lightcontrol(void) {
  light = digitalRead(LIGHT_SENSOR_PIN);
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

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void discoFade(int wait) {

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