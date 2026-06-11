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

BlynkTimer timer;

// Function to send temperature and humidity
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

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
}

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

    // DHT11 Setup
    dht.begin();

    // WiFi Connection
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Connect to Blynk
    Serial.println("Connecting to Blynk...");
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    // Send sensor data every 2 seconds
    timer.setInterval(2000L, sendSensor);

    Serial.println("Setup Complete!");
}

void loop()
{
    Blynk.run();

    timer.run();
}