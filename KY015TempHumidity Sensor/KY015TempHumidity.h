#include <stdint.h>
#include "mcc_generated_files/system/system.h"

typedef struct
{
    int8_t humidity;
    int8_t humidity_d;
    int8_t temperature;
    int8_t temperature_d;
    bool checksum;
} TempHumiditySensor;

int8_t _readData();
TempHumiditySensor KY015GetData();


