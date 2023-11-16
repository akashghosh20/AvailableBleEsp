#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

Servo servo1, servo2, servo3, servo4, servo5;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Serial"); // Bluetooth device name

  servo1.attach(2);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(12);
  servo5.attach(19);
}

void loop() {
  if (SerialBT.available()) {
    String receivedData = SerialBT.readStringUntil('\n');
    Serial.println("Received: " + receivedData);

    // Parse and handle the received data
    handleBluetoothData(receivedData);
  }

  // Your other tasks here
}


void handleBluetoothData(String data) {
  // Assuming the received data is a comma-separated string of servo angles
  int angles[5];
  int angleIndex = 0;

  // Parse the received data
  char *ptr = strtok((char *)data.c_str(), ",");
  while (ptr != NULL) {
    angles[angleIndex++] = atoi(ptr);
    ptr = strtok(NULL, ",");
  }

  // Serial.println("Shoulder"+angles[1]);

  // Update servo angles
  servo1.write(angles[0]);
  servo2.write(angles[1]);
  servo3.write(angles[2]);
  servo4.write(angles[3]);
  servo5.write(angles[4]);
}
