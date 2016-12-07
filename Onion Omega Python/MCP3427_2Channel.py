# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MCP3427
# This code is designed to work with the MCP3427_I2CADC I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Analog-Digital-Converters?sku=MCP3427_I2CADC#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# MCP3427 address, 0x68(104)
# Send configuration command
#		0x10(16)	Continuous conversion mode, Channel-1, 12-bit Resolution
data = [0x10]
i2c.write(0x68, data)

# MCP3427 address, 0x68(104)
# Read data back from 0x00(0), 2 bytes
# raw_adc MSB, raw_adc LSB
data = i2c.readBytes(0x68, 0x00, 2)

# Convert the data to 12-bits
raw_adc = (data[0] & 0x0F) * 256 + data[1]
if raw_adc > 2047 :
	raw_adc -= 4095

# Output data to screen
print "Digital Value of Analog Input on Channel-1: %d" %raw_adc

# MCP3427 address, 0x68(104)
# Send configuration command
#		0x30(48)	Continuous conversion mode, Channel-2, 12-bit Resolution
data = [0x30]
i2c.write(0x68, data)

# MCP3427 address, 0x68(104)
# Read data back from 0x00(0), 2 bytes
# raw_adc MSB, raw_adc LSB
data = i2c.readBytes(0x68, 0x00, 2)

# Convert the data to 12-bits
raw_adc = (data[0] & 0x0F) * 256 + data[1]
if raw_adc > 2047 :
	raw_adc -= 4095

# Output data to screen
print "Digital Value of Analog Input on Channel-2: %d" %raw_adc
