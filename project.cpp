void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensors.begin();

  if (!tmp117.begin()) {
    Serial.println("Could not find TMP117 sensor!");
    while (1);
  }

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Initialization failed!");
    return;
  }

  dataFile = SD.open("data.csv", FILE_WRITE);
  dataFile.println("Temperature (C),Ultrasonic Sensor 1 Distance (cm),Ultrasonic Sensor 2 Distance (cm),Vibration Sensor Value");
  dataFile.close();
}

void loop() {
  float temperatureCelsius = tmp117.readTempC();

  long duration, distance1;
  digitalWrite(ULTRASONIC_TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIGGER_PIN_1, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN_1, HIGH);
  distance1 = (duration / 2) / 29.1;

  long distance2;
  digitalWrite(ULTRASONIC_TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIGGER_PIN_2, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN_2, HIGH);
  distance2 = (duration / 2) / 29.1;

  int vibrationValue = analogRead(VIBRATION_SENSOR_PIN);

  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  Serial.print("Ultrasonic Sensor 1 Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Ultrasonic Sensor 2 Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.print("Vibration Sensor Value: ");
  Serial.println(vibrationValue);

  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(temperatureCelsius);
    dataFile.print(",");
    dataFile.print(distance1);
    dataFile.print(",");
    dataFile.print(distance2);
    dataFile.print(",");
    dataFile.println(vibrationValue);
    dataFile.close();
  } else {
    Serial.println("Error opening file!");
  }

  delay(1000);
}