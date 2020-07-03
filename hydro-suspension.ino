#define AVG_SIZE 64 // 1..255

struct Wheel {
  int values[AVG_SIZE];
  long int sum;
  byte vptr;
};

enum {
  WHEEL_BEGIN = 0,
  WHEEL_FRONT_LEFT = 0,
  WHEEL_FRONT_RIGHT,
  WHEEL_REAR_LEFT,
  WHEEL_REAR_RIGHT,
  WHEEL_END
};

Wheel wheels[WHEEL_END];

void updateWheel(Wheel &w, int value) {
  w.sum -= w.values[w.vptr];
  w.sum += value;
  w.values[w.vptr++] = value;
  if (w.vptr >= AVG_SIZE)
    w.vptr = 0;
}

void cbInterrupt() {
  Serial.println("INTERRUPT");
}

void setup() {
  Serial.begin(115200);

  // button
  attachInterrupt(digitalPinToInterrupt(2), cbInterrupt, CHANGE);

  // Timer
  cli();      // disable interrupts
  TCCR1A = 0; // Timer counter control register
  TCCR1B = 1<<CS12 | 1<<CS10 | 1<<WGM12; // Timer counter control register
  OCR1A = 15;  // output compare register
  OCR1B = 0;  // output compare register
  TCNT1 = 0;  // timer counter
  TIMSK1 = 1<<OCIE1A; // timer interrupt mask
  sei();      // enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  Serial.println("TIMER INTERRUPT");
}

void loop() {
  updateWheel(wheels[WHEEL_FRONT_LEFT ], analogRead(A0));
  updateWheel(wheels[WHEEL_FRONT_RIGHT], analogRead(A1));
  updateWheel(wheels[WHEEL_REAR_LEFT  ], analogRead(A2));
  updateWheel(wheels[WHEEL_REAR_RIGHT ], analogRead(A3));

  Serial.print("\ec");
  Serial.println(wheels[WHEEL_FRONT_LEFT].sum/AVG_SIZE);
  delay(3000);
}
