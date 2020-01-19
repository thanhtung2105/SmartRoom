#include <DHT.h>        

const int DHTPIN = A5;       
const int DHTTYPE = DHT11; //Type of sensor 

DHT SmartRoomDHT(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  SmartRoomDHT.begin();
}

void loop() {
  float Humidity = SmartRoomDHT.readHumidity();    
  float Temperature = SmartRoomDHT.readTemperature(); 

  Serial.print("Nhiet do: ");
  Serial.println(Temperature);     
  Serial.print("Do am: ");
  Serial.println(Humidity);        
  
  Serial.println();                
  delay(1000);                     
}
