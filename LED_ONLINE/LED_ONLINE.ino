#include <Wire.h>

const int LED_A = 4;
const int LED_B = 5;
const int LED_C = 6;
const int LED_D = 7;
unsigned char str[] = "abcdefgh";
enum
{
  MFORWARD = 1,
  MBACK,
  MLEFT,
  MRIGHT,
  MSTOP,
  ONLINE_LEDA_ON = 9,//不明白为啥有些数I2C会有问题
  ONLINE_LEDB_ON,
  ONLINE_LEDC_ON,
  ONLINE_LEDD_ON,
  ONLINE_LEDALL_ON,
  ONLINE_LEDA_OFF,
  ONLINE_LEDB_OFF,
  ONLINE_LEDC_OFF,
  ONLINE_LEDD_OFF,
  ONLINE_LEDALL_OFF,
};

unsigned long prevCount;
unsigned long currentCount = 0;
unsigned long deltaTime = 0;

unsigned char ledData = ' ';

void setup()
{
  pinMode(LED_A, OUTPUT);           //LEDA
  pinMode(LED_B, OUTPUT);           //LEDB
  pinMode(LED_C, OUTPUT);			 //LEDC
  pinMode(LED_D, OUTPUT);			 //LEDD
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop()
{
  if (millis() - deltaTime > 100)
  {
    currentCount++;
    deltaTime = millis();
  }
  if (currentCount != prevCount)
  {
    prevCount = currentCount;
    Wire.begin(8);
  }
  //Serial.println(ledData);
  if (ledData == str[0])
  {
    digitalWrite(LED_A, HIGH);
  }
  if (ledData == str[1])
  {
    digitalWrite(LED_B, HIGH);
  }
  if (ledData == str[2])
  {
    digitalWrite(LED_C, HIGH);
  }
  if (ledData == str[3])
  {
    digitalWrite(LED_D, HIGH);
  }
  if (ledData == str[4])
  {
    digitalWrite(LED_A, LOW);
  }
  if (ledData == str[5])
  {
    digitalWrite(LED_B, LOW);
  }
  if (ledData == str[6])
  {
    digitalWrite(LED_C, LOW);
  }
  if (ledData == str[7])
  {
    digitalWrite(LED_D, LOW);
  }
}

void receiveEvent(int howMany)
{
  while (Wire.available() > 0)
  {
    ledData = Wire.read();
    deltaTime = millis();
  }
}
