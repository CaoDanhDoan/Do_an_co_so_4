#include <Arduino_FreeRTOS.h>

#define LED_PIN 13

TaskHandle_t LedTaskHandle;
TaskHandle_t SerialTaskHandle;
TaskHandle_t SensorTaskHandle;
TaskHandle_t ComplexTaskHandle;

void ledTask(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void serialTask(void *pvParameters) {
  while (1) {
    Serial.println("Hello, RTOS!");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void sensorTask(void *pvParameters) {
  while (1) {
    int sensorValue = analogRead(A0);
    Serial.print("Sensor value: ");
    Serial.println(sensorValue);
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void complexTask(void *pvParameters) {
  while (1) {
    long fib1 = 0, fib2 = 1, fib3;
    Serial.println("Fibonacci sequence:");
    Serial.print(fib1); Serial.print(" ");
    Serial.print(fib2); Serial.print(" ");
    for (int i = 2; i < 10; i++) {
      fib3 = fib1 + fib2;
      Serial.print(fib3); Serial.print(" ");
      fib1 = fib2; fib2 = fib3;
    }
    Serial.println();
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void setup() {
  Serial.begin(9600);

  xTaskCreate(ledTask, "LedTask", 128, NULL, 1, &LedTaskHandle);
  xTaskCreate(serialTask, "SerialTask", 128, NULL, 2, &SerialTaskHandle);
  xTaskCreate(sensorTask, "SensorTask", 128, NULL, 1, &SensorTaskHandle);
  xTaskCreate(complexTask, "ComplexTask", 128, NULL, 3, &ComplexTaskHandle);

  vTaskStartScheduler();
}

void loop() {
  // Empty
}
