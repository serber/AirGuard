import time
from machine import UART, Pin

uart = UART(1, baudrate=9600, tx=Pin(8), rx=Pin(9))

def debug_read_co2():
    command = b'\xff\x01\x86\x00\x00\x00\x00\x00\x79'
    uart.write(command)
    time.sleep(0.1)
    if uart.any() >= 9:
        response = uart.read(9)
        print("Response:", response)  # Печать всего ответа для отладки
        if response[0] == 0xff and response[1] == 0x86:
            co2 = response[2] * 256 + response[3]
            return co2
    return None

while True:
    co2_level = debug_read_co2()
    if co2_level is not None:
        print("CO₂ Level:", co2_level, "ppm")
    else:
        print("Error reading CO₂ level")
    time.sleep(2)
