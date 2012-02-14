#define     LED                         13
#define     PUSHBUTTON                   2


#define     DEBOUNCE_TIME               30
#define     DEFAULT_WAIT              1000
#define     DEFAULT_LED_STATE         HIGH
#define     DEFAULT_PREV_LED_STATE     LOW

#define     NOT_PRESSED                  1
#define     PRESSING                     2
#define     PRESSED                      3
#define     RELEASING                    4


unsigned long now;
unsigned long wait;
int button_state;
int led_state;
int prev_led_state;
unsigned long button_change_state_time;
unsigned long time_start;
unsigned long time_end;


void setup () {
  led_state = DEFAULT_LED_STATE;
  wait = DEFAULT_WAIT;
  button_state = NOT_PRESSED;
  button_change_state_time = millis();

  pinMode(LED, OUTPUT);
  pinMode(PUSHBUTTON, INPUT);

  Serial.begin(9600);
}


void loop () {
  now = millis();
  prev_led_state = led_state;

  if (digitalRead(PUSHBUTTON) == HIGH) {
    if (button_state == NOT_PRESSED) {
      button_state = PRESSING;
    } else {
      button_state = PRESSED;
    }
  } else {
    if (button_state == PRESSED) {
      button_state = RELEASING;
    } else {
      button_state = NOT_PRESSED;
    }
  }

  if (button_state == PRESSING || button_state == RELEASING) {
    delay(DEBOUNCE_TIME);
  }

  if (button_state == PRESSING) {
    //Serial.println("PRESSING");
    time_start = now;
    led_state = HIGH;
    wait = 250;
  } else if (button_state == RELEASING) {
    //Serial.println("RELEASING");
    time_end = now;
    button_change_state_time = time_end;
    wait = time_end - time_start;
    led_state = LOW;
    //Serial.print("wait = ");
    //Serial.println(wait);
  } else if (now >= button_change_state_time + wait) {
    //Serial.println("TIMEOUT");
    led_state = (led_state == HIGH ? LOW : HIGH);
    button_change_state_time = now;
    //Serial.print("Changing state at ");
    //Serial.println(now);
  }

  if (led_state != prev_led_state) {
    digitalWrite(LED, led_state);
  }
}
