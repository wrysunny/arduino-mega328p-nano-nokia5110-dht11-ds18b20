#include <Adafruit_PCD8544.h>
// or use library: https://github.com/pbaja/AvrPCD8544/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#define DHTPIN 8
#define DHTTYPE DHT11 
// ds 18b20 Temperature sensor
#define ONE_WIRE_BUS 2

DHT dht(DHTPIN, DHTTYPE, 6);
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Initialize the Nokia 5110 LCD driver library
// @param sclk_pin SCLK pin  DIN pin  DC pin  CS pin  RST pin 
// https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/blob/master/Adafruit_PCD8544.cpp
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  // lcd bl
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  delay(1000);
  dht.begin();
  Serial.println("Arduino Digital Temperature will start."); //Print a message
  sensors.begin();
  // Initialize the Nokia 5110 display
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.display();

  // Print a message on the display
  display.setCursor(0, 0);
  display.println("Programe Start...");
  display.display();
  digitalWrite(9, LOW);
  delay(1000);
  digitalWrite(9, HIGH);
}

void loop() {
  display.clearDisplay();
  sensors.requestTemperatures();  
  float temperature = dht.readTemperature();
  delay(5000);
  float humidity = dht.readHumidity(); 
  display.print("Temp 1: ");
  display.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  display.print("Temp 2: ");
  display.println(temperature);
  display.print("Hum 2: ");
  display.display();
  delay(5000);
}


