#define BLYNK_TEMPLATE_ID "TMPL62ZIFtGdg"
#define BLYNK_TEMPLATE_NAME "day4"
#define BLYNK_AUTH_TOKEN "6OeSClv8tlQ0eyYjQwSZacC1LAAa6UUq"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi Credentials
char ssid[] = "Engineers_2.4";
char pass[] = "#All_is_well";

// DHT11 Configuration
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Built-in LED
#define LED_PIN 2

// Motor Driver Pins
#define IN1 18
#define IN2 19
#define ENA 5
#define IN3 21
#define IN4 22
#define ENB 23

// PWM Config
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8 // 8-bit: 0–255

// ✅ Set your desired speed here (0–255)
#define MOTOR_SPEED 180

BlynkTimer timer;

// ── Sensor ──────────────────────────────────────────────
void sendSensor()
{
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT11!");
        return;
    }

    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);

    Serial.printf("Temp: %.1f C\tHumidity: %.1f %%\n", temperature, humidity);
}

// ── V0 – Single button: LED + Both Motors ───────────────
BLYNK_WRITE(V0)
{
    int state = param.asInt();

    // LED
    digitalWrite(LED_PIN, state);

    if (state == 1)
    {
        // Set speed
        ledcWrite(ENA, MOTOR_SPEED);
        ledcWrite(ENB, MOTOR_SPEED);

        // Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        // Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        Serial.printf("Motors ON — Speed: %d\n", MOTOR_SPEED);
        Serial.println("LED: ON");
    }
    else
    {
        // Stop both motors
        ledcWrite(ENA, 0);
        ledcWrite(ENB, 0);

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);

        Serial.println("Motors OFF");
        Serial.println("LED: OFF");
    }
}

// ── Connected callback ───────────────────────────────────
BLYNK_CONNECTED()
{
    Serial.println("Connected to Blynk!");
    Blynk.syncVirtual(V0); // restore button state on reconnect
}

// ── Setup ────────────────────────────────────────────────
void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\nESP32 Starting...");

    // LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Motor A direction pins
    pinMode(IN1, OUTPUT);
    digitalWrite(IN1, LOW);
    pinMode(IN2, OUTPUT);
    digitalWrite(IN2, LOW);

    // Motor B direction pins
    pinMode(IN3, OUTPUT);
    digitalWrite(IN3, LOW);
    pinMode(IN4, OUTPUT);
    digitalWrite(IN4, LOW);

    // PWM for ENA and ENB (Core v3.x API)
    ledcAttach(ENA, PWM_FREQ, PWM_RESOLUTION);
    ledcAttach(ENB, PWM_FREQ, PWM_RESOLUTION);
    ledcWrite(ENA, 0);
    ledcWrite(ENB, 0);

    // DHT
    dht.begin();

    // WiFi
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Blynk
    Serial.println("Connecting to Blynk...");
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    // Sensor timer – every 2 seconds
    timer.setInterval(2000L, sendSensor);

    Serial.println("Setup Complete!");
}

// ── Loop ─────────────────────────────────────────────────
void loop()
{
    Blynk.run();
    timer.run();
}