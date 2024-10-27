import time
from machine import UART, Pin

uart = UART(1, baudrate=9600, tx=Pin(8), rx=Pin(9))

# Инициализация светодиода на GP2
led = Pin(25, Pin.OUT)

def calibrate_zero():
    command = b'\xff\x01\x87\x00\x00\x00\x00\x00\x78'  # Команда калибровки на 400 ppm
    uart.write(command)

# Подождите 20-30 минут перед запуском
print("Please wait for 20 minutes in clean air...")

for _ in range(10):  # Мигаем 10 раз
    led.toggle()  # Переключаем состояние светодиода
    time.sleep(0.5)  # Задержка 0.5 секунды

led.toggle()

print("Waiting 20 minutes...")

time.sleep(1200)  # Ожидание 20 минут

print("Starting zero calibration...")

calibrate_zero()  # Выполнение калибровки

print("Calibration command sent. Please wait for a moment.")

# Бесконечное мигание светодиода после калибровки
while True:
    led.toggle()  # Переключаем состояние светодиода
    time.sleep(0.5)  # Задержка 0.5 секунды