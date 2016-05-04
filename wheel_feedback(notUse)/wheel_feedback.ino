
// Note for me.......... Delete later
// This code is for digital sensor, and wrong for analog IR sensor. 
// You can use Photosensor code which is in EECS class folder




int SensorPin=2;
int SensorValue=LOW;

// NTR: note. This encoder only allows you to count ticks and holes. It means you cannot know it rotates clockwise or reverse, so you need to give forward or back based on the input data.
#define SENSOR_THRESHOLD 3000  //3000 or more means nothing was reflected.
int tick_cnt = 0;  // NTR: Need to initialize for every operation. Also, the position of wheel should start from tick, not hole (if it's hole, it will count +1 soon and it shouldn't be counted)
int prev_SensorValue;  // NTR: Need to initialize every operation
# define TICKS_AND_HOLES 64 // Currently, using 32 ticks wheel
# define RADIUS_OF_WHEEL 2.186  // Inch

// Count every tick or hole on the wheel
int count_tick(int SensorValue)
{
  if (prev_SensorValue >= SENSOR_THRESHOLD)
  {
    if (SensorValue < SENSOR_THRESHOLD)
    {
      tick_cnt++;
      prev_SensorValue = SensorValue;
      }
  }
  else
  {
    if (SensorValue >= SENSOR_THRESHOLD)
    {
      tick_cnt++;
      prev_SensorValue = SensorValue;
    }
  } 
  return tick_cnt;
}

// Convert the number of ticks and holes to angle (radius)
float convert_to_angle(int cur_tick_cnt, int prev_tick_cnt)
{
  float converted_angle = ((float)(cur_tick_cnt - prev_tick_cnt)) / (float)TICKS_AND_HOLES * 2.0 * 3.14;
  return converted_angle;
}

// Convert from angle (radius) to distance (inch)
float convert_to_distance(float angle)
{
  return RADIUS_OF_WHEEL * angle;
}

void setup()
{
    pinMode(13,OUTPUT); 
    Serial.begin(9600);
}

void loop()
{
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.

    pinMode(2,OUTPUT);
    digitalWrite(2,HIGH);
    delayMicroseconds(10);
    pinMode(2,INPUT);
    long time = micros();
    //time how long the input is HIGH, but quit after 3ms as nothing happens after that
    while (digitalRead(SensorPin) == HIGH && micros() - time < SENSOR_THRESHOLD);
    int diff = micros() - time;
    SensorValue=diff;
    if(Serial.available()>0);
    {
//        Serial.print(digitalRead(SensorPin));
//        Serial.print("\t");
//        Serial.print(micros());
//        Serial.print("\t");
//        Serial.print(time);
//        Serial.print("\t");        
        Serial.println(SensorValue); 
    }
    
    Serial.println("count_tick"); 
    Serial.println(count_tick(SensorValue));
    Serial.println("convert_to_angle"); 
    Serial.println(convert_to_angle(count_tick(SensorValue), 0));
    Serial.println("convert_to_distance"); 
    Serial.println(convert_to_distance(convert_to_angle(count_tick(SensorValue), 0)));
    
    delay(50);
}
