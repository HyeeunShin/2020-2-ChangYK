#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(7 , OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
 toggle = 0;
 digitalWrite(7, toggle);
  
}

void loop() {
  delay(1000);
  
  toggle = 1;
  digitalWrite(7, toggle);
  delay(1000);
  
  for (int i = 0; i<10; i ++) {
    toggle =toggle_state(toggle); //toggle LED value.
    digitalWrite(7 , toggle); // update LED status.
    delay(100);// wait for 250 milliseconds
  }

  while (1) {
    digitalWrite(7, toggle);
  }
}



int toggle_state(int toggle) {

  if (toggle == 0)
  {
    toggle = 1;
  }
  else
  {
    toggle = 0;
   }
  return toggle;
}
