//Einrichtung des Servos und DHT-Sensors
#include <Servo.h>
Servo myservo;
#include "DHT.h"
#include "Adafruit_Sensor.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Variable für map-Befehl unten
float servostellung;

//Variablen für RGB LED
int red_light_pin = 11;
int green_light_pin = 10;
int blue_light_pin = 9;                   

void setup() {
//Servo Einstellung
myservo.attach(3);

//Serieller Monitor
Serial.begin(9600);
dht.begin();

//Einstellung der RGB LED
pinMode(red_light_pin, OUTPUT);
pinMode(green_light_pin, OUTPUT);
pinMode(blue_light_pin, OUTPUT);


}

void loop() {
//Variablen für Luftfeuchtigkeit/Temperatur
float Luftfeuchtigkeit = dht.readHumidity();
float Temperatur = dht.readTemperature();

//Werte der Luftfeuchtigkeit (0 bis 100%) werden für Servostellung gemappt (0 bis 180°)
servostellung = map(Luftfeuchtigkeit, 0, 100, 0, 180);

//Proportional zum Wert der Luftfeuchtigkeit dreht sich der Servo bis zu 180 Grad 
//und gibt die Werte im seriellen Monitor an.
if( Luftfeuchtigkeit >= 0 ){
  delay(1000);
  myservo.write(0);
  myservo.write(servostellung);
  Serial.print("Luftfeuchtigkeit -> " );
  Serial.print(Luftfeuchtigkeit);
  Serial.println("%");
}
//Temperatur wird im seriellen Monitor angezeigt
Serial.print("Temperatur -> " );
Serial.print(Temperatur);
Serial.println("°C");
delay(500);

//Ist die Temperatur bei 24° (oder drunter), leuchtet LED grün
//Ist die Temperatur bei 25° (oder darüber), leuchtet LED rot
//Ist die Temperatur dazwischen, leuchtet LED gelb
float min = 24.0;
float max = 25.0;

if (Temperatur <= min) {
  RGB_color(0, 255, 0);
}
else if (Temperatur >= max) {
  RGB_color(255, 0, 0);
}
else {
  RGB_color(255, 255, 0);
}


}
//Deklarieren von "RGB_color"
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
