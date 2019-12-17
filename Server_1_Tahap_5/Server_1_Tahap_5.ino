#include <ArduinoJson.h>
#include <SPI.h>
#include <RH_RF95.h>
RH_RF95 rf95;

int Frequency = 868.0;
int TxPower=5;
int thisAddress=105;
int headerTo=101;
int headerFrom=100;
int headerId=5;
float sensor_value;
int sensor_id;

typedef struct {
  int address;
  float sensorvalue;
} paket;

paket *X;

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  if(!rf95.init())
    Serial.println("init failed");
  
  rf95.setFrequency(868.0);
  rf95.setTxPower(TxPower,false);
  rf95.setThisAddress(thisAddress);
  rf95.setHeaderTo(headerTo);
  rf95.setHeaderFrom(headerFrom);
  rf95.setHeaderId(headerId);
}

void loop()
{
  if (rf95.available())
  {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof (buf);
    if (rf95.recv(buf, &len))
    {
      X = (paket*) buf;
      sensor_id = (*X).address;
      sensor_value = (*X).sensorvalue;
      
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject& data = jsonBuffer.createObject();
   data["sensor_id"] = sensor_id;
   data["sensor_value"] = sensor_value;
   data.printTo(Serial);
   Serial.println();
    }
  }   
}
