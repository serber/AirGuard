from sensors.MHZ19B import MHZ19B

import time

mhz19b = MHZ19B(uart_id=1, tx_pin=8, rx_pin=9)
while True:
 co2 = mhz19b.read_co2()
 if co2 is not None:
     print("CO2:", co2, "ppm")
 else:
     print("Failed to read data from sensor")

 time.sleep(2)