#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Инициализация BME680 с использованием I2C
Adafruit_BME680 bme;

// Структура для хранения данных с датчика
struct BME680SensorData {
  float temperature;
  float pressure;
  float humidity;
  float gasResistance;
  float altitude;
  float lastReadTime;
};

bool BME680Ready = false;

void setup() {
  // Инициализация Serial
  Serial.begin(115200);

  // Попытка инициализировать BME680
  initializeBME680();
}

void loop() {
  // Считываем данные с датчика
  BME680SensorData bme680SensorData = readBME680SensorData();

  // Выводим данные в Serial
  printBME680SensorData(bme680SensorData);

  // Задержка между измерениями
  delay(2000);
}

// Функция для инициализации датчика
bool initializeBME680() {
  // Инициализация BME680
  if (!bme.begin()) {
    Serial.println("Ошибка инициализации BME680!");
    BME680Ready = false;
  }

  // Настройка параметров BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // 320°C for 150 ms

  BME680Ready = true;

  return true;
}

// Функция для считывания данных с датчика
BME680SensorData readBME680SensorData() {
  BME680SensorData data;

  if (BME680Ready && bme.performReading()) {
    data.temperature = bme.temperature;
    data.pressure = bme.pressure / 100.0;  // Преобразование давления в hPa
    data.humidity = bme.humidity;
    data.gasResistance = bme.gas_resistance / 1000.0;                      // Преобразование в кОм
    data.altitude = 44330 * (1.0 - pow(bme.pressure / 101325.0, 0.1903));  // Расчет высоты
    data.lastReadTime = millis() / 1000.0;                                 // Сохранение времени последнего чтения
  }

  return data;
}

// Функция для вывода данных в Serial
void printBME680SensorData(const BME680SensorData& data) {
  Serial.print("Температура = ");
  Serial.print(data.temperature);
  Serial.println(" °C");

  Serial.print("Давление = ");
  Serial.print(data.pressure);
  Serial.println(" hPa");

  Serial.print("Влажность = ");
  Serial.print(data.humidity);
  Serial.println(" %");

  Serial.print("Качество воздуха (сопротивление газа) = ");
  Serial.print(data.gasResistance);
  Serial.println(" кОм");

  Serial.print("Высота над уровнем моря = ");
  Serial.print(data.altitude);
  Serial.println(" метров");

  // Вывод времени последнего чтения
  Serial.print("Последнее чтение через ");
  Serial.print(data.lastReadTime, 2);
  Serial.println(" секунд с момента запуска.");

  Serial.println();
}