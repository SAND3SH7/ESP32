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

// Motor Driver Pins (Single Motor)
#define IN1 18
#define IN2 19
#define ENA 5

// PWM Settings
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8
#define MOTOR_SPEED 180 // 0–255

// Blynk Switch V0
BLYNK_WRITE(V0)
{
    int state = param.asInt();

    // LED Control
    digitalWrite(LED_PIN, state);

    if (state == 1)
    {
        // Set Motor Speed
        ledcWrite(ENA, MOTOR_SPEED);

        // Motor Forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        Serial.printf("Motor ON - Speed: %d\n", MOTOR_SPEED);
        Serial.println("LED ON");
    }
    else
    {
        // Stop Motor
        ledcWrite(ENA, 0);

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);

        Serial.println("Motor OFF");
        Serial.println("LED OFF");
    }
}

BLYNK_CONNECTED()
{
    Serial.println("Connected to Blynk!");
    Blynk.syncVirtual(V0);
}

void setup()
{
    Serial.begin(115200);

    // LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Motor Pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // PWM Setup
    ledcAttach(ENA, PWM_FREQ, PWM_RESOLUTION);
    ledcWrite(ENA, 0);

    // Connect WiFi & Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    Serial.println("System Ready");
}

void loop()
{
    Blynk.run();
}