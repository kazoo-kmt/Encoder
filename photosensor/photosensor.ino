
// NTR: Need to initialize for every operation. 
int tick_cnt = 0;  // variable to be updated by the interrupt
# define TICKS_AND_HOLES 64 // Currently, using 32 ticks wheel
# define RADIUS_OF_WHEEL 2.186  // unit: Inch


//int ledPin = 6;  // LED is attached to digital pin 6 (you can choose)

void setup() {                
  //enable interrupt 0 (pin 2) which is connected to a button for right wheel
  //enable interrupt 1 (pin 3) which is connected to a button for left wheel
  
  //jump to the increment function on change edge
  attachInterrupt(0, increment, CHANGE);
  Serial.begin(9600);  //turn on serial communication
}

void loop() {
//  tick_cnt = 0;  // NTR: initialize every time 
//  digitalWrite(ledPin, LOW);
  delay(100); //pretend to be doing something useful
    Serial.println("tick_cnt"); 
    Serial.println(tick_cnt, DEC); //print tick_cnt to serial monitor
//    Serial.println("convert_to_angle"); 
//    Serial.println(convert_to_angle(tick_cnt));
//    Serial.println("convert_to_distance"); 
//    Serial.println(convert_to_distance(convert_to_angle(tick_cnt)));
//
//    Serial.println("---------------------"); 
    
    delay(50);

  
}

// Interrupt service routine for interrupt 0
// Count every tick or hole on the wheel
void increment() {
    tick_cnt++;
//    digitalWrite(ledPin, HIGH);
}

// Convert the number of ticks and holes to angle (radius)
float convert_to_angle(int tick_cnt)
{
  float converted_angle = (float)tick_cnt / (float)TICKS_AND_HOLES * 2.0 * 3.14;
  return converted_angle;
}

// Convert from angle (radius) to distance (inch)
float convert_to_distance(float angle)
{
  return RADIUS_OF_WHEEL * angle;
}
