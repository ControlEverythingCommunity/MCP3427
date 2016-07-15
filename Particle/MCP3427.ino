// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP3427
// This code is designed to work with the MCP3427_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=MCP3427_I2CADC#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// MCP3427 I2C address is 0x68(104)
#define Addr 0x68

int raw_adc = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "MCP3427");
  Particle.variable("rawADC", raw_adc);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Start serial communication and set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration command
  // Continuous conversion mode, Channel-1, 12-bit Resolution
  Wire.write(0x10);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  raw_adc = (data[0] & 0x0F) * 256 + data[1];
  if (raw_adc > 2047)
  {
    raw_adc -= 4096;
  }

  // Output data to dashboard
  Particle.publish("Digital Value of Analog input : ", String(raw_adc));
  delay(1000);
}
