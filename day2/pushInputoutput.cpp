const int buttonPin = 4; // GPIO: 4,,5,18,19,21,22,23,25,26,27,32,33

void setup()
{
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(23, OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(23, HIGH);
    Serial.println("Button Pressed");
  }
  else
  {
    Serial.println("Button Released");
    digitalWrite(23, LOW);
  }

  delay(100);
}