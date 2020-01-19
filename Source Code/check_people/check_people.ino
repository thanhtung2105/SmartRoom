float light = A0;
int outside = 7;
int inside = 8;
int number_of_people = 0;
int alarm = 9;
int bulb_state;

void setup()
{
  Serial.begin(9600);
  pinMode(outside,INPUT);
  pinMode(inside,INPUT);
  pinMode(light,INPUT);
  pinMode(alarm,OUTPUT);
}

int check_outside()
{
  int result = 0;
  while (digitalRead(outside) == 0)
  {
    delay(5);
    result = 1;
  }
  return result;
}

int check_inside()
{
  int result = 0;
  while (digitalRead(inside) == 0)
  {
    delay(5);
    result = 1;
  }
  return result;
}

void loop()
{
    float li_level = analogRead(light);
    if (li_level>1000&&number_of_people>0)
    {
      digitalWrite(alarm,HIGH);
      bulb_state = 1;
    }
    else
    {
       digitalWrite(alarm,LOW);
       bulb_state = 0;
//       Serial.println("Light state: OFF");
    }
//    Serial.println(li_level);
    if(check_outside())
    {
      if(check_inside())
      {
        number_of_people++;
        Serial.print("Có người mới vào phòng! Số người hiện tại trong phòng là: ");
        Serial.println(number_of_people);
      }
      else
      {
        Serial.println("Có người chạm vào cửa nhà bạn");
      }
    }

    if(check_inside())
    {
      if(check_outside())
      {
        number_of_people--;
        if (number_of_people<0)
          number_of_people = 0;
        Serial.print("Có người mới rời khỏi phòng! Số người hiện tại trong phòng là: ");
        Serial.println(number_of_people);
      }
      else
      {
        Serial.println("Có trẻ em đang tìm cách trốn khỏi phòng!");
      }
    }
}
