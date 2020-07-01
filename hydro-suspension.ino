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

void setup() {
  Serial.begin(115200);
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
