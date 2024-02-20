#include <xc.h>
#include "mcc_generated_files/adc/adc.h"

#define MILIVOLTS 3300

float adcToCelsius(adc_channel_t channel){
    uint16_t adcResult = ADC_GetConversion(channel);
    return (float)((adcResult * (MILIVOLTS/1024))-330)/10;
}
float adcToFahrenheit(adc_channel_t channel){
    return (float)(adcToCelsius(channel) * 9.0 /5.0) - 32.0;
}