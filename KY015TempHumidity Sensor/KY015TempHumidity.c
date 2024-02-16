#include <stdint.h>
#include "mcc_generated_files/system/system.h"
#include "KY015TempHumidity.h"

TempHumiditySensor KY015GetData(){
  int8_t data[5];
  TRISC0 = 0;
  LATC0 = 0; //Pull down the bus to send the start signal
  __delay_ms(30); //The delay is greater than 18 ms so that DHT 11 can detect the start signal
  LATC0 = 1;
  __delay_us(40); //Wait for DHT11 to respond
  TRISC0 = 1;
  while(PORTCbits.RC0 == 1);
  __delay_us(80); //The DHT11 responds by pulling the bus low for 80us;
  
  if(PORTCbits.RC0 == 1)
    __delay_us(80); //DHT11 pulled up after the bus 80us to start sending data;
  for(int i = 0; i < 5; i++){ 
    //Receiving temperature and humidity data, check bits are not considered;
    data[i] = _readData();
  }
  TRISC0 = 0;
  LATC0 = 1; //After the completion of a release of data bus, waiting for the host to start the next signal
  TempHumiditySensor result = {
    .humidity = data[0],
    .humidity_d = data[1],
    .temperature = data[2],
    .temperature_d = data[3],
    .checksum = data[4] == data[0] + data[1] + data[2] + data[3]
  };
  return result;
}

int8_t _readData(){
  int8_t i = 0;
  int8_t result = 0;
  for (i = 0; i < 8; i++) {
      while (PORTCbits.RC0 == 0); // wait 50us
      __delay_us(30); //The duration of the high level is judged to determine whether the data is '0' or '1'
      if (PORTCbits.RC0 == 1)
        result |= (1 << (8 - i)); //High in the former, low in the post
      while (PORTCbits.RC0 == 1); //Data '1', waiting for the next bit of reception
  }
  return result;
}
