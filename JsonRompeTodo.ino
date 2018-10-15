
#include <ArduinoJson.h>
#include <LoRa.h>
#include <DHT.h>


const int ledverde=5;
const int ledrojo=6;
const int  sensor = A0;
long temperatura;
long milivoltios;
int brillo;
int counter;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  //LoRa.setPins(ss, reset, dio0);

  LoRa.begin(433E6);
  Serial.begin(9600);
   pinMode(ledrojo, OUTPUT);
   pinMode(ledverde, OUTPUT);
   dht.begin();


  
}

void loop() {
  // put your main code here, to run repeatedly:



float t =dht.readTemperature();
Serial.print(t);
  Serial.print(" *C ");  
  Serial.println("");  
//lo que sigue no estoy segura si es legal
//para enviar
 Serial.print("Sending packet: ");
  Serial.println(counter);

const int BUFFER_SIZE = JSON_ARRAY_SIZE(2);
StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
JsonObject& json = jsonBuffer.createObject();

 json["GRUPO"] = "J4";
 json["Temperatura"] = t;


  
 LoRa.beginPacket();
 LoRa.print( json.printTo(Serial));
  LoRa.endPacket();

counter++;

delay(30000);

  
}
