// source: https://github.com/futureshocked/TE-Arduino-SbS-Getting-Serious/blob/master/_1218b_-_Bluetooth_connectivity_with_the_HC-06_module/_1218b_-_Bluetooth_connectivity_with_the_HC-06_module.ino
// hc 05 vs hc 06: https://robocraze.com/blogs/post/hc-05-vs-hc-06-vs-wf-05-bluetooth-modules

/*  1218b - Bluetooth connection demo with the HC-06
 * 
 * This sketch shows you how to control an LED from the serial monitor and to
 * display readings from an analog sensor (photoresistor) using a wireless serial 
 * connection with the HC-06 module.
 * 
 * Once you have the connections completed, with the HC-06 not powered, upload 
 * this sketch via the USB cable. Then disconnect the USB cable, and power up the 
 * HC-06. Connect the HC-06 to your computer as you do with any Bluetooth device.
 * The pairing key is "1234". 
 * 
 * In the Arduino IDE, select the HC-06 from the list of available devices. Then,
 * start the serial monitor. Ensure that there is no line ending in the monitor.
 * In the input field, type "H" to turn the LED on, and press Enter. The LED should
 * turn on. Send any other character to turn off the LED.
 * 
 * The Arduino will send regular updates with the value of the photoresistor.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 1 x 330 Ohm resistor for the LED
 *  - 1 x LED
 *  - 1 x 10 kOhm resistor for the photoresistor
 *  - 1 x photoresistor
 *  - 1 x HC-06 Bluetooth module
 *  - An external power supply for the Arduino
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
*  Arduino Uno and HC-06:
 *  
 *  Arduino Uno   |     HC-06
 *  ------------------------------
 *        5V      |       VCC
 *        GND     |       GND
 *        1       |       RXD
 *        2       |       TXD
 *
 * Coneect the 330 Ohm resistor in series with the LED. 
 * 
 * Connect the anode of the LED to Arduino digital pin 8, and 
 * its cathode to GND.
 * 
 * Connect the photoresistor and the 10 kOhm resistor in series. Connect
 * the junction of the photoresistor and resistor to analog pin A0 on the
 * Arduino. Connect GND and 5V to the other two ends of the 
 * resistor-photoresistor segment (it does not matter which goes where
 * for this example).
 *        
 *  Created on October 16 2017 by Peter Dalmaris
 * 
 */

char val;       // variable to receive data from the serial port
int ledpin = 8; // LED connected to pin 8

int sensorpin = 0; //Analog pin

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1000;


void setup() {

  pinMode(ledpin, OUTPUT);  // pin 8 as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
}

void loop() {

  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
  
  if((millis() - lastConnectionTime > postingInterval)) {
      int ana_A = analogRead(sensorpin);
      Serial.print("Sensor reading: ");
      Serial.println(ana_A);
      lastConnectionTime = millis();
  }
} 
