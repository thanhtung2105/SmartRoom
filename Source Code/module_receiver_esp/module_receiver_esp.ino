#include <RF24.h>

RF24 radio(2, 15);    //ce,cs pin
const byte address[7] = "181219";
float value[3];
float temperature, humidity;
float check_people = 0;

void setup()
{
    Serial.begin(115200);
    radio.begin();
    radio.setRetries(15, 15);
    radio.setPALevel(RF24_PA_MAX);
    radio.openReadingPipe(1, address);
    radio.startListening();
}

void loop()
{
  if (radio.available())
    {
        memset(&value, ' ', sizeof(value));
        radio.read(&value, sizeof(value));
        temperature = value[0];
        humidity = value[1];
        check_people = value[2];
    }

  if( (check_people==1) || (check_people=-1) )
  {
  Serial.print("Temperature: ");  
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Check people: ");
  Serial.println(check_people);

  check_people = 0;
  }
//  delay(1000);
}
