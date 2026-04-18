#include "ph_meter.h"
#include "adc.h"

static PH_Calib_t g_ph_cal =
{
    .v4   = 2.360f,
    .v686 = 2.000f,
    .v918 = 1.670f
};

static float g_iir_voltage = 0.0f;
static uint8_t g_iir_initialized = 0;

void PH_Init(void)
{
}

void PH_SetCalibration(PH_Calib_t calib)
{
    g_ph_cal = calib;
}

static float PH_ReadVoltageOnce(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 20);
    uint32_t adc = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return 3.3f * ((float)adc) / 4095.0f;
}

float PH_ReadVoltage(void)
{
    const uint8_t N = 8;
    float buf[N];
    float sum = 0.0f;
    float vmax = -1000.0f;
    float vmin = 1000.0f;

    for (uint8_t i = 0; i < N; i++)
    {
        buf[i] = PH_ReadVoltageOnce();
        HAL_Delay(1);
    }

    for (uint8_t i = 0; i < N; i++)
    {
        sum += buf[i];
        if (buf[i] > vmax) vmax = buf[i];
        if (buf[i] < vmin) vmin = buf[i];
    }

    float avg = (sum - vmax - vmin) / (N - 2);

    if (!g_iir_initialized)
    {
        g_iir_voltage = avg;
        g_iir_initialized = 1;
    }
    else
    {
        g_iir_voltage = 0.3f * g_iir_voltage + 0.7f * avg;
    }

    return g_iir_voltage;
}

float PH_ReadPH(float temp_c, float *voltage_out)
{
    float v = PH_ReadVoltage();

    if (voltage_out)
    {
        *voltage_out = v;
    }

    float k25 = (9.18f - 4.00f) / (g_ph_cal.v918 - g_ph_cal.v4);
    float kt  = k25 * 298.0f / (273.0f + temp_c);
    float ph  = 6.86f + (v - g_ph_cal.v686) * kt;

    if (ph < 0.0f)  ph = 0.0f;
    if (ph > 14.0f) ph = 14.0f;

    return ph;
}
