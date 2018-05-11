#include "SoftwareSerial.h"
#include "LiquidCrystal.h"
#include "Wire.h"
#include <DS3231.h>
#include <dht11.h>
#include <Servo.h>

#define dht11pin 7
dht11 DHT11;
Servo servol_1;
Servo servol_2;


const int  rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
DS3231  rtc(SDA,SCL);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
SoftwareSerial HS(10,11); // Rx-pin 10 , TxPin 11


void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);
  Wire.begin();
  rtc.begin();
 // rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
 // rtc.setTime(0, 51, 00);     // Set the time to 12:00:00 (24hr format)
 //rtc.setDate(10, 5, 2018);   // Set the date , month, 
  
}

void loop() 
{
//========================================================================Soil humidity sensor
int HS = analogRead(A0);
int HSpercent = HS/7;
Serial.print("HS: " + String(HSpercent)+ "%    ");


// Servo1 pin5
servol_1.attach(5);
if(HSpercent <31){servol_1.write(40);}
if(HSpercent >31){servol_1.write(26);}




//servo2 pin 6
servol_2.attach(6);
servol_2.write(10);
servol_2.write(23);
if(HSpercent >31){servol_2.write(24);}


 
//========================================================================Photo Rister
  int PR = analogRead(A1);
  Serial.print("PR: " + String(PR) + "     ");


/*
// =======================================================================LM35 temprature sensor
  int tp_0 = analogRead(A2);
  int tp_1 = tp_0*125>>8;//Calculate the actual tempereature based on tp_0.
  Serial.print("Tep: " + String(tp_1)+"C    ");
*/

 

//========================================================================ds 3231 Clock Module
 Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.print(String(rtc.getTimeStr()) + "  ");


//========================================================================DHT11 Tempreature and humidity sensor

int chk = DHT11.read(dht11pin);
Serial.print("Temp: " + String(DHT11.temperature) + ("C  " ));
Serial.println("Humidity: " + String(DHT11.humidity) + "%  ");



//  =====================================================================Lcd display
 
  lcd.setCursor(0,0);
  lcd.print("Time: " + String(rtc.getTimeStr()) + " Tep:" + String(DHT11.temperature)+ "C Air Humidity:"+ String(DHT11.humidity)+"% ");
  
  lcd.setCursor(0,1);
  lcd.print("Soil humidity: " + String (HSpercent) + "% ");
  delay(1000);
  lcd.scrollDisplayLeft();
  }
  


