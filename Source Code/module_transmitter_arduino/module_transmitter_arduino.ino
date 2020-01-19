#include <RF24.h>
#include <DHT.h>

RF24 radio(7, 8);   //ce,cs pin 7 8
const byte data_pipe[7] = "181219";

const int DHTPIN = A5;       
const int DHTTYPE = DHT11; //Type of sensor 
DHT SmartRoomDHT(DHTPIN, DHTTYPE);

const int Outside = 2;
const int Inside = 4;

float People_Status;

float value[3];
float Temperature, Humidity;

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  pinMode(Outside,INPUT);
  pinMode(Inside,INPUT);
  SmartRoomDHT.begin();
  radio.begin();
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(data_pipe);
}

void loop() {
  Humidity = SmartRoomDHT.readHumidity();    
  Temperature = SmartRoomDHT.readTemperature(); 
  
  //-----------------------------------------------
  
  if(check_Outside())
    {
      if(check_Inside())
      {
        People_Status = 1;
        Serial.println("Come in - Hello!");
        Serial.print("Send... ");
        Serial.print(Temperature);
        Serial.print(" - ");
        Serial.print(Humidity);
        Serial.print(" - ");
        Serial.println(People_Status);
      }
      else
      {
        People_Status = 0;
      }
    }

    if(check_Inside())
    {
      if(check_Outside())
      {
        People_Status = -1;
        Serial.println("Get out - Goodbye!");
        Serial.print("Send... ");
        Serial.print(Temperature);
        Serial.print(" - ");
        Serial.print(Humidity);
        Serial.print(" - ");
        Serial.println(People_Status);
      }
      else
      {
        People_Status = 0;
      }
    }
  
  //-----------------------------------------------

  value[0] = Temperature;
  value[1] = Humidity;
  value[2] = People_Status;
  radio.write(&value, sizeof(value));
  
  People_Status = 0;
}

//------------------------------------

int check_Outside()
{
  int result = 0;
  while (digitalRead(Outside) == 0)
  {
    delay(5);
    result = 1;
  }
  return result;
}

int check_Inside()
{
  int result = 0;
  while (digitalRead(Inside) == 0)
  {
    delay(5);
    result = 1;
  }
  return result;
}
