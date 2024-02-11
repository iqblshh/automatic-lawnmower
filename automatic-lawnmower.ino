
const int echoRight = 5;	
const int trigRight = 18; 
const int echoLeft = 19;	
const int trigLeft = 23; 

int enablepin_1=35;
int in1L=32;
int in2L=33;
int enablepin_2=27;
int in3R=12;
int in4R=13;

long duraRight, duraLeft;
int distRight, distLeft;

int x = 0;

//----------------------------------------

#define BLYNK_TEMPLATE_ID "TMPL6zut9Pbyy"
#define BLYNK_TEMPLATE_NAME "Gyro"
#define BLYNK_AUTH_TOKEN "_rP9XRQ-mIl6KJvxm505jeArZp2py0ZP"

#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "macammacamhal - 2.4GHz";
//char pass[] = "Sasukekun1234";
char ssid[] = "Redmi";
char pass[] = "password";

BlynkTimer timer;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 m_p_u;

void setup()
{
  Serial.begin(115200);

  pinMode(enablepin_1,OUTPUT);
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  
  pinMode(enablepin_2,OUTPUT);
  pinMode(in3R, OUTPUT);
  pinMode(in4R, OUTPUT);
  
  digitalWrite(enablepin_1,LOW);
  digitalWrite(enablepin_2,LOW);
  	
  pinMode (echoRight, INPUT);
  pinMode (trigRight, OUTPUT);
  pinMode (echoLeft, INPUT);
  pinMode (trigLeft, OUTPUT);

//----------------------------------------

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



void right()
{ 
  digitalWrite (trigRight, LOW);     
  delayMicroseconds (10);           
  digitalWrite (trigRight, HIGH);   
  delayMicroseconds (10);          
  digitalWrite (trigRight, LOW);       

  duraRight = pulseIn (echoRight, HIGH); 
  distRight = duraRight * 0.034 / 2;
  
  if (distRight <= 13)
  {
    digitalWrite(enablepin_1,HIGH);
    digitalWrite(in1L,HIGH);
    digitalWrite(in2L,LOW);

    digitalWrite(enablepin_2,HIGH);
    digitalWrite(in3R,LOW);
    digitalWrite(in4R,HIGH);  
    Serial.println ("right");

    x = 1; 
    delay(500);
  } 
}



void left()
{ 
  digitalWrite (trigLeft, LOW);     
  delayMicroseconds (10);           
  digitalWrite (trigLeft, HIGH);   
  delayMicroseconds (10);          
  digitalWrite (trigLeft, LOW);       

  duraLeft = pulseIn (echoLeft, HIGH); 
  distLeft = duraLeft * 0.034 / 2;
  
  if (distLeft <= 13)
  {
    digitalWrite(enablepin_1,HIGH);
    digitalWrite(in1L,LOW);
    digitalWrite(in2L,HIGH);

    digitalWrite(enablepin_2,HIGH);
    digitalWrite(in3R,HIGH);
    digitalWrite(in4R,LOW);  
    Serial.println ("left"); 

    x = 1;
    delay(500);
  } 
}

void go()
{
  digitalWrite(enablepin_1,HIGH);
  digitalWrite(in1L,HIGH);
  digitalWrite(in2L,LOW);

  digitalWrite(enablepin_2,HIGH);
  digitalWrite(in3R,HIGH);
  digitalWrite(in4R,LOW);  
  Serial.println ("go");
}

void loop()
{
  right();
  left();

  if (x == 0) {
    go();
  }

  x = 0;

//----------------------------------------
  
  Blynk.run();
  timer.run();
}

