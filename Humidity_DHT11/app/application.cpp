#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <Libraries/DHT/DHT.h>

#define WORK_PIN 2 // GPIO02

DHT dht(WORK_PIN, DHT11, READ_INTERVAL_DHT11_DSHEET);

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Allow debug output to serial

	Serial.println("wait 1 second for the sensor to boot up");

	//disable watchdog
	WDT.enable(false);
	//wait for sensor startup
	delay(1000);

	dht.begin();

	/*first reading method (Adafruit compatible) */
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(t) || isnan(h))
	{
		Serial.println("Failed to read from DHT");
	} else {
		Serial.print("\tHumidity: ");
		Serial.print(h);
		Serial.print("% Temperature: ");
		Serial.print(t);
		Serial.print(" *C\n");
	}

}

