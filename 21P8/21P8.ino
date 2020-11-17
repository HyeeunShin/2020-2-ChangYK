#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10
#define PIN_IR A0
#define PIN_LED 9

// configurable parameters
#define _DUTY_MIN 1200 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 1900 // servo full counterclockwise position (180 degree)

#define _POS_START (_DUTY_MIN + 100)
#define _POS_END (_DUTY_MAX - 100)

#define _SERVO_SPEED 60 // servo speed limit (unit: degree/second)
#define INTERVAL 40  // servo update interval

// global variables
unsigned long last_sampling_time; // unit: ms
float duty_chg_per_interval; // maximum duty difference per interval
int toggle_interval, toggle_interval_cnt;
float pause_time; // unit: sec
Servo myservo;
int duty_target, duty_curr;

void setup() {
// initialize GPIO pins
  myservo.attach(PIN_SERVO); 
  duty_target = duty_curr = _POS_START ;
  duty_curr = 1500;
  myservo.writeMicroseconds(duty_curr);
  
// initialize serial port
  Serial.begin(57600);

// convert angle speed into duty change per interval.
  duty_chg_per_interval =(float)(_DUTY_MAX - _DUTY_MIN) * _SERVO_SPEED / 180 * INTERVAL / 1000;


}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
// wait until next sampling time. 
// millis() returns the number of milliseconds since the program started. Will overflow after 50 days.
  float raw_dist = ir_distance();

  
// adjust duty_curr toward duty_target by duty_chg_per_interval
  if(raw_dist < 240.0){
    duty_curr += 7;
    if (duty_curr > _DUTY_MAX) duty_curr =  _DUTY_MAX;
  }
  else if(raw_dist > 100.0){
    duty_curr -= 7;
    if (duty_curr < _DUTY_MIN) duty_curr = _DUTY_MIN;
  }
// update servo position
  myservo.writeMicroseconds(duty_curr);

// output the read value to the serial port

  Serial.print(",duty_curr:");
  Serial.print(duty_curr);
  Serial.print(",raw_dist:");
  Serial.println(raw_dist);



// update last sampling time
}
