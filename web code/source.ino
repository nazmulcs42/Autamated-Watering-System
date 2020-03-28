#include "SoftwareSerial.h"

#define pump 8
#define sensor_input A0
SoftwareSerial esp(1, 0);

int watering_duration=0;
String con = "", tc = "", data = "";
String server = "192.168.1.109";
String url_sensor_value = "/receive.php";
String url_watering_duration = "/receive_watering_duration.php";

void setup()
{
  esp.begin(9600);
  pinMode(sensor_input, INPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump,LOW);
  esp.println("AT+CWQAP");
  delay(1000);
  wifi_init();
}

void loop()
{
  int v=sensor_value();
  Serial.println(v);
  delay(1000);
  send_data();
  delay(2000);
  if(check_moisture()){
    bool check=true;
    while(check){
      delay(2000);
      check=check_moisture();
    }
    //Serial.print("Watering time: ");
    //Serial.print(watering_duration);
    //Serial.println(" sec");
    send_watering_time();
    watering_duration=0;
  }
  delay(10000);
}

void wifi_init()
{
  //Serial.println("Connecting to wifi....");
  delay(1000);
  esp.println("AT+RST");
  delay(1000);
  esp.println("AT+CWMODE=3");
  delay(1000);
  //esp.println("AT+CWJAP=\"CSE_PUST\",\"descse721\"");
  esp.println("AT+CWJAP=\"C S E 7\",\"unique07\"");
  delay(8000);
  //Serial.println("Connected to wifi");
  esp  .println("Connected to wifi");
  delay(1000);
}

int sensor_value()
{
  delay(1000);
  int sensor_val = analogRead(sensor_input);
  delay(1000);
  return sensor_val;
}

void send_data()
{
  //Serial.println("Sending data...");
  delay(1000);
  data="sensor_value=" + (String)sensor_value();
  delay(1000);
  tc="AT+CIPSTART=\"TCP\",\"192.168.1.109\",80";
  esp.println(tc);
  delay(3000);
  String postRequest =
  
  "POST " + url_sensor_value + " HTTP/1.1\r\n" +
  
  "Host: " + server + "\r\n" +
  
  "Accept: *" + "/" + "*\r\n" +
  
  "Content-Length: " + data.length() + "\r\n" +
  
  "Content-Type: application/x-www-form-urlencoded\r\n" +
  
  "\r\n" + data;
  
  esp.print("AT+CIPSEND=");
  delay(100);
  esp.println(postRequest.length());
  delay(2000);
  esp.println(postRequest);
  delay(3000);
  //Serial.println("Sensor value sent");
}

void send_watering_time()
{
  //Serial.println("Sending Watering duration...");
  delay(1000);
  data="watering_time=" + (String)watering_duration;
  delay(1000);
  tc="AT+CIPSTART=\"TCP\",\"192.168.1.109\",80";
  esp.println(tc);
  delay(3000);
  String postRequest =
  
  "POST " + url_watering_duration + " HTTP/1.1\r\n" +
  
  "Host: " + server + "\r\n" +
  
  "Accept: *" + "/" + "*\r\n" +
  
  "Content-Length: " + data.length() + "\r\n" +
  
  "Content-Type: application/x-www-form-urlencoded\r\n" +
  
  "\r\n" + data;
  
  esp.print("AT+CIPSEND=");
  delay(100);
  esp.println(postRequest.length());
  delay(2000);
  esp.println(postRequest);
  delay(3000);
  //Serial.println("Watering duration sent");
}


bool check_moisture()
{
    int sensor_val=sensor_value();
    //Serial.print("Sensor value --> ");
    //Serial.println(sensor_val);
    //esp.println("AT");
    if(sensor_val <1200 && sensor_val >=600){
        watering_duration+=5;
        //Serial.println("Plant need to be watered");
        //esp.println("AT");
        digitalWrite(pump,HIGH);
        delay(5000);
        digitalWrite(pump,LOW);
        //esp.println("AT");
        return true;
    }
    else if(sensor_val <600 && sensor_val >=500){
        watering_duration+=2;
        //Serial.println("Plant need to be watered");
        digitalWrite(pump,HIGH);
        delay(2000);
        digitalWrite(pump,LOW);
        return true;
    }
    else{
        //Serial.println("Plant is healthy...Soil contains sufficient water...");
        return false;
    }
}