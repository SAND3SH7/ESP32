#define BLYNK_TEMPLATE_ID "TMPL62ZIFtGdg"
#define BLYNK_TEMPLATE_NAME "day4"
#define BLYNK_AUTH_TOKEN "6OeSClv8tlQ0eyYjQwSZacC1LAAa6UUq"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi Credentials
char ssid[] = "Engineers_2.4";
char pass[] = "#All_is_well";

// Built-in LED
#define LED_PIN 2

// Motor Driver Pins
#define IN1 18
#define IN2 19

// Blynk Switch V0 controls LED and Motor
BLYNK_WRITE(V0)
{
    int state = param.asInt();

    // LED Control
    digitalWrite(LED_PIN, state);

    // Motor Control
    if (state == 1)
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        Serial.println("Motor ON");
    }
    else
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        Serial.println("Motor OFF");
    }

    Serial.print("LED State: ");
    Serial.println(state ? "ON" : "OFF");
}

// Runs when ESP32 connects to Blynk
BLYNK_CONNECTED()
{
    Serial.println("Connected to Blynk!");
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\nESP32 Starting...");

    // LED Setup
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Motor Driver Setup
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // Connect to Blynk
    Serial.println("Connecting to Blynk...");
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    Serial.println("Setup Complete!");
}

void loop()
{
    Blynk.run();
}
