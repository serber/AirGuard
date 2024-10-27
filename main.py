import time
from machine import UART, Pin

uart = UART(1, baudrate=9600, tx=Pin(8), rx=Pin(9))

def read_co2():
    command = b'\xff\x01\x86\x00\x00\x00\x00\x00\x79'  # Команда запроса CO₂
    uart.write(command)  # Отправка команды
    time.sleep(0.1)  # Задержка для получения ответа
    if uart.any() >= 9:  # Проверка, достаточно ли данных
        response = uart.read(9)  # Чтение 9 байт
        if response[0] == 0xff and response[1] == 0x86:  # Проверка корректности ответа
            co2 = response[2] * 256 + response[3]  # Расчет уровня CO₂
            return co2
    return None  # Если не удалось считать данные

while True:
    co2_level = read_co2()
    if co2_level is not None:
        print("CO2 Level:", co2_level, "ppm")  # Печать уровня CO₂
    else:
        print("Error reading CO2 level")  # Ошибка чтения
    time.sleep(2)  # Задержка перед следующей попыткой