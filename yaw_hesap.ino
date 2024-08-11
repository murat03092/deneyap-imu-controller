#include "lsm6dsm.h"
LSM6DSM IMU;
float posx, posy, posz;

void setup() {
  Serial.begin(115200);
  IMU.begin();

}

void loop() {
  float ax_g = IMU.readFloatAccelX() / 16384.0;
  float ay_g = IMU.readFloatAccelY() / 16384.0;
  float az_g = IMU.readFloatAccelZ() / 16384.0;

  float gx_dps = IMU.readFloatGyroX() / 131.0;
  float gy_dps = IMU.readFloatGyroY() / 131.0;
  float gz_dps = IMU.readFloatGyroZ() / 131.0;

  float pitch = atan2(-ay_g, sqrt(pow(ax_g,2) + pow(az_g,2))) * 180.0 / PI;
  float roll = atan2(ax_g, sqrt(pow(ay_g,2) + pow(az_g,2))) * 180.0 / PI;

  static float yaw = 0;
  float dt = 0.01; // Zaman adımı, 10 ms
  yaw += gz_dps * dt*100;
  //yaw=map(yaw,-4,6,0,180);

   // Seri monitöre yazdır
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("°, Pitch: ");
  Serial.print(pitch);
  Serial.print("°, Yaw: ");
  Serial.print(yaw);
  Serial.println("°");

  delay(10); // 10 ms gecikme

  // posx = atan( IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  // posy = atan(-1* IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  // posz = atan(IMU.readFloatAccelZ() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelY(), 2)+0.001)) * 180 / PI;

}
