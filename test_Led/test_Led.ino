String WARNING_TEXTS[2] = {
  "value is correct",
  "be careful this value not in range"
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  turnLedAccordingAnalogValue(200, 220, A0, 1000);
}

void turnLedAccordingAnalogValue(int minValue, int maxValue, char port, int delayMs) {
  int sensorValue = analogRead(port);
  int ledValue = getLedValue(minValue, maxValue, sensorValue);

  Serial.println(sensorValue);
  Serial.println(getWarningText(ledValue));
  digitalWrite(LED_BUILTIN, ledValue);

  delay(delayMs);
}

int getLedValue(int minValue, int maxValue, int value) {
  if (value > maxValue | value < minValue) {
    return HIGH;
  } else {
    return LOW;
  }
}

String getWarningText(int value) {
  return WARNING_TEXTS[value];
}
