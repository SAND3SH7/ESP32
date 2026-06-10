const int ldrPin = 34;
const int ledPin = 2;

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    int ldrValue = analogRead(ldrPin);

    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Adjust threshold according to your readings
    if (ldrValue < 1500)
    {
        digitalWrite(ledPin, HIGH); // Dark
    }
    else
    {
        digitalWrite(ledPin, LOW); // Bright
    }

    delay(200);
}
