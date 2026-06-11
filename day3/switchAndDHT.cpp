#define BLYNK_TEMPLATE_ID "TMPL3ucKyE3BW"
#define BLYNK_TEMPLATE_NAME "day4"
#define BLYNK_AUTH_TOKEN "PrLhp2SzsKiw8J6XrDO0_w3kVnUq0Lr1"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi Credentials
char ssid[] = "Your_wifi_SSID" char pass[] = "Your_wifi_password";

// DHT11 Configuration
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ESP32 Built-in LED
#define LED_PIN 2

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

    // Send to Blynk
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);

    // Print to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
}

// Blynk Button V0 controls LED
BLYNK_WRITE(V0)
{
    int state = param.asInt();

    digitalWrite(LED_PIN, state);

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

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("\nESP32 Starting...");

    dht.begin();

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