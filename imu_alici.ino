#include <Deneyap_Servo.h>
#include "WiFi.h"
#include "esp_now.h"

#define SERVOPITCH D9
#define SERVOYAW D8
#define SERVOROLL D12
#define MOTOR D13

Servo pitchServo;
Servo yawServo;
Servo rollServo;

Servo motor;

int posPitch = 0;
int oposPitch = posPitch;
int posRoll = 0;
int oposRoll = posRoll;
int posYaw = 0;
int oposYaw = posYaw;

typedef struct struct_message {
  float pitch;
  float roll;
  float yaw;
  float gaz;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Pitch Veri: ");
  Serial.println(myData.pitch);
  Serial.println();
  Serial.print("Roll Veri: ");
  Serial.println(myData.roll);
  Serial.println();
  Serial.print("Yaw Veri: ");
  Serial.println(myData.yaw*10);
  Serial.print("GAZ Veri: ");
  Serial.println(myData.gaz);
  Serial.println();
  
}

void setup() {
  Serial.begin(115200);

  pitchServo.attach(SERVOPITCH);
  yawServo.attach(SERVOYAW,1);
  rollServo.attach(SERVOROLL,2);
  motor.attach(MOTOR,3,1000,2000);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  posPitch=90+int(myData.pitch);
  posRoll=90+int(myData.roll);
  posYaw=90+int(myData.yaw*10);

  int gazDeger=map(myData.gaz,0,100,0,180);
  motor.write(gazDeger);

  if(abs(posPitch-oposPitch) >= 4)
    {
      oposPitch = posPitch;
      pitchServo.write(posPitch);
    } 

  if(abs(posRoll-oposRoll) >= 4)
    {
      oposRoll = posRoll;
      yawServo.write(posRoll);
    } 

  if(abs(posYaw-oposYaw) >= 4)
    {
      oposYaw = posYaw;
      rollServo.write(posYaw);
    }

  delay(10);
  
}
