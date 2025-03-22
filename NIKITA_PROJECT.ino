#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Threshold for detecting fall (tune based on your setup)
#define FALL_THRESHOLD 20000  // Example threshold, adjust as needed

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize the MPU6050
  mpu.initialize();
  
  // Check if MPU6050 is connected properly
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 connection successful.");
}

void loop() {
  // Get accelerometer data
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Print accelerometer data
  /*Serial.print(" Ax: ");
  Serial.print(ax);
  Serial.print(" Ay: ");
  Serial.print(ay);
  Serial.print(" Az: ");
  Serial.println(az);
  */
  // Calculate the magnitude of the acceleration vector
  float magnitude = sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2));
   Serial.println(magnitude);

  // The expected magnitude for the sensor in normal conditions is ~9.81 (gravity)
  // When a fall happens, it will be significantly less due to free fall or sudden shock
  if (magnitude > FALL_THRESHOLD) {
    Serial.println("Fall detected!");
    digitalWrite(12,HIGH);
    delay(10000);
    digitalWrite(12,LOW);
    delay(10000);
    // You can add further action here (e.g., trigger a buzzer or send an alert)
  }

  delay(100);  // Delay between readings (100ms)
}
