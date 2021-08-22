#include "CRSF.h"

//// PINS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define channel_1 36
#define channel_2 39
#define channel_3 34
#define channel_4 35
#define channel_5 32
#define channel_6 33
#define channel_7 25
#define channel_8 26


#define CRSFinterval 4000 //in us, ie 250hz update
#define uartCRSFinverted true

CRSF crsf;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  crsf.PackedRCdataOut.ch0 = map(analogRead(channel_1), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch1 = map(analogRead(channel_2), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch2 = map(analogRead(channel_3), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch3 = map(analogRead(channel_4), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch4 = map(analogRead(channel_5), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch5 = map(analogRead(channel_6), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch6 = map(analogRead(channel_7), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.PackedRCdataOut.ch7 = map(analogRead(channel_8), 0, 4095, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
  crsf.sendRCFrameToFC();
  portEXIT_CRITICAL_ISR(&timerMux);
}

void StartTimer()
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, CRSFinterval, true);
  timerAlarmEnable(timer);
}

void setup()
{
  Serial.begin(115200);
  crsf.Begin();
  StartTimer();
}

void loop()
{
  delay(50);
  Serial.print(crsf.PackedRCdataOut.ch0);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch1);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch2);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch3);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch4);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch5);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch6);
  Serial.print(" ");
  Serial.print(crsf.PackedRCdataOut.ch7);
  Serial.print(" ");

  Serial.println("");
}
