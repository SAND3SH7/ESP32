
#include <DHT.h>

#define DHTPIN 4      // GPIO connected to DHT11 DATA pin
#define DHTTYPE DHT11 // Sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    dht.begin();

    Serial.println("DHT11 Sensor Test");
}

void loop()
{
    delay(2000); // DHT11 requires slow sampling

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(); // Celsius

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT11!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
}