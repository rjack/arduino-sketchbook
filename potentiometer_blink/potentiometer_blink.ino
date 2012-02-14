#define     LED               13
#define     POTENTIOMETER     A0
#define     THRESHOLD          5




int led_on;
int input;
int prev_input;
unsigned long now;
unsigned long blink_delay;
unsigned long prev_state_change_time;


void setup () {
  pinMode(LED, OUTPUT);
  pinMode(POTENTIOMETER, INPUT);
  Serial.begin(9600);

  led_on = 0;


  prev_input = analogRead(POTENTIOMETER);
  prev_state_change_time = millis();
  blink_delay = prev_input;
}


void loop () {
  now = millis();
  input = analogRead(POTENTIOMETER);

  if (abs(input - prev_input) >= THRESHOLD) {
    //Serial.println(input);
    blink_delay = input;
    prev_input = input;
  }

  if (now - prev_state_change_time >= blink_delay) {
    digitalWrite(LED, (led_on ? LOW : HIGH));
    led_on = 1 - led_on;
    prev_state_change_time = now;
  }
}
