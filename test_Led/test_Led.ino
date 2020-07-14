String WARNING_TEXTS[2] = {
  "Value is correct",
  "Be careful this value not in range"
};

void setup() {
  Serial.begin(19200);
}

void loop() {
  turnLedAccordingAnalogValue(200, 220, A0, 1000);
}

/* 
 * method turnLedAccordingAnalogValue - turn LED and print value
 * param 'min' - min possible value,
 * param 'max' - max possible value,
 * param 'port' - analog port for read values, 
 * param 'delay' - delay between request in MS,
 */
void turnLedAccordingAnalogValue(int minValue, int maxValue, char port, int delayMs) {
  int sensorValue = analogRead(port);
  int ledValue = getLedValue(minValue, maxValue, sensorValue);

  printMessages(sensorValue, ledValue);
  digitalWrite(LED_BUILTIN, ledValue);

  delay(delayMs);
}

int getLedValue(int minValue, int maxValue, int value) {
  return value > maxValue | value < minValue ? HIGH : LOW;
}

String getWarningText(int value) {
  return WARNING_TEXTS[value];
}

void printMessages(int value, int messageIndex) {
  Serial.println(value);
  Serial.println(getWarningText(messageIndex));
}
