#define AVG_SIZE 64 // 1..255
#define LEDPIN 13

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

enum {
  EVENT_READ_SENSORS = 1<<0,
  EVENT_DEBUG        = 1<<1,
  EVENT_BUTTON       = 1<<2,
};

static volatile int event;
static volatile int clock;

void updateWheel(Wheel &w, int value) {
  w.sum -= w.values[w.vptr];
  w.sum += value;
  w.values[w.vptr++] = value;
  if (w.vptr >= AVG_SIZE)
    w.vptr = 0;
}

void cbInterrupt() {
  event |= EVENT_BUTTON;
}

void setup() {
  Serial.begin(115200);

  // button
  attachInterrupt(digitalPinToInterrupt(2), cbInterrupt, CHANGE);

  // Timer
  cli();      // disable interrupts
  TCCR1A = 0; // Timer counter control register
  TCCR1B = 1<<CS12 | 1<<CS10 | 1<<WGM12; // Timer counter control register
  OCR1A = 16;  // output compare register
  OCR1B = 0;  // output compare register
  TCNT1 = 0;  // timer counter
  TIMSK1 = 1<<OCIE1A; // timer interrupt mask
  sei();      // enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  if ( (clock&0x3F) == 0 )
    event |= EVENT_READ_SENSORS;
  if ( (clock&0x3FF) == 0 )
    event |= EVENT_DEBUG;
  clock++;
}

void updateWheels() {
  updateWheel(wheels[WHEEL_FRONT_LEFT ], analogRead(A0));
  updateWheel(wheels[WHEEL_FRONT_RIGHT], analogRead(A1));
  updateWheel(wheels[WHEEL_REAR_LEFT  ], analogRead(A2));
  updateWheel(wheels[WHEEL_REAR_RIGHT ], analogRead(A3));
}

void loop() {
  cli();
  int e = event;
  event = 0;
  sei();

  if ( e & EVENT_READ_SENSORS ) {
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
    updateWheels();
  }
  if ( e & EVENT_DEBUG ) {
    Serial.print("\ec");
    Serial.println("WHEEL VALUES:");
    Serial.print(wheels[WHEEL_FRONT_LEFT].sum/AVG_SIZE) ;Serial.print(" | ");
    Serial.print(wheels[WHEEL_FRONT_RIGHT].sum/AVG_SIZE);Serial.print(" | ");
    Serial.print(wheels[WHEEL_REAR_LEFT].sum/AVG_SIZE)  ;Serial.print(" | ");
    Serial.println(wheels[WHEEL_REAR_RIGHT].sum/AVG_SIZE);
  }
  if ( e & EVENT_BUTTON ) {
    Serial.println("Button action");
  }
}
