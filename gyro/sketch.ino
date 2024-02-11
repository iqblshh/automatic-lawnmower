#define BLYNK_TEMPLATE_ID "TMPL6zut9Pbyy"
#define BLYNK_TEMPLATE_NAME "Gyro"
#define BLYNK_AUTH_TOKEN "_rP9XRQ-mIl6KJvxm505jeArZp2py0ZP"

#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "macammacamhal - 2.4GHz";
char pass[] = "Sasukekun1234";

BlynkTimer timer;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 m_p_u;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendGyroData);

  while(!Serial)
  delay(20);
  if(!m_p_u.begin()){
    while(1){
      delay(20);
    }
  }
}

void sendGyroData() {
  sensors_event_t acc, gcc, temp;
  m_p_u.getEvent(&acc, &gcc, &temp);

  int gx = (gcc.gyro.x)*180/3.14;
  int gy = (gcc.gyro.y)*180/3.14;
  int gz = (gcc.gyro.z)*180/3.14;

  if ( gx >= -10 && gx <= 10 && gy >= -10 && gy <= 10 && gz >= -10 && gz <= 10 ) {
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, "Working Properly");
  }
  else {
    Blynk.virtualWrite(V0, 1);
    Blynk.virtualWrite(V1, "Sumthin Wrong");  
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
