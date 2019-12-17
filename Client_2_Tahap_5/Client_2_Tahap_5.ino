#include <SPI.h>
#include <RH_RF95.h>
RH_RF95 rf95;

int Frequency = 868;
int TxPower = 5;
int SensorValue;
float NTU;
float voltage;

//Inisialisasi Struct
typedef struct {
  int address;
  float sensorvalue;
} paket;
paket X;

//Pembacaan Sensor
float sensor_reading(){
  float NTU;
  int SensorValue;
  SensorValue = analogRead(A0);
  float voltage = SensorValue * (4.8/1023);
  NTU = (-157.89 * voltage) + (648.25);
  return NTU;
}

//Data yang akan dikirim
float value_of_data(float NTU){
   X.address = 2;
   X.sensorvalue = NTU;
   return (X.address,X.sensorvalue);
}

//Fungsi mengirim data
void sending_data(){
  rf95.send((uint8_t*) &X, sizeof(X));
  rf95.waitPacketSent();
}

void setup()
{

Serial.begin (9600);
while (!Serial);
if (!rf95.init())
    {
      Serial.print("init failed");
    }

  rf95.setFrequency(Frequency);
  rf95.setTxPower(TxPower);
  rf95.setThisAddress(102);
  rf95.setHeaderTo(105);
  rf95.setHeaderId(2);
  

}

void loop()
{
  sensor_reading();
  NTU = sensor_reading();
  value_of_data(NTU);
  sending_data();
  Serial.print("This Address: ");
  Serial.println(X.address);
  Serial.print("Data Sensor yang dikirim: ");
  Serial.println(X.sensorvalue);
  delay(1400);
  }
