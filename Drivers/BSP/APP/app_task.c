#include "app_task.h"
#include "delay_us.h"
#include "ds18b20.h"
#include "ph_meter.h"
#include "app_beijing_time.h"
#include "atk_md0096.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>

static float g_last_temp = 0.0f;
static uint8_t g_temp_valid = 0;
static uint8_t g_oled_ready = 0;

static void format_fixed(char *buf, size_t len, float value, uint8_t frac_digits)
{
    int32_t scale = 1;
    for (uint8_t i = 0; i < frac_digits; i++)
    {
        scale *= 10;
    }

    int negative = 0;
    if (value < 0)
    {
        negative = 1;
        value = -value;
    }

    int32_t iv = (int32_t)value;
    int32_t fv = (int32_t)((value - (float)iv) * scale + 0.5f);

    if (fv >= scale)
    {
        iv++;
        fv = 0;
    }

    if (negative)
    {
        snprintf(buf, len, "-%ld.%0*ld", (long)iv, frac_digits, (long)fv);
    }
    else
    {
        snprintf(buf, len, "%ld.%0*ld", (long)iv, frac_digits, (long)fv);
    }
}

void APP_UserInit(void)
{
    delay_us_init();
    HAL_ADCEx_Calibration_Start(&hadc1);

    DS18B20_Init();
    PH_Init();
    APP_Time_InitDefault();

    if (atk_md0096_init() == ATK_MD0096_EOK)
    {
        g_oled_ready = 1;
        atk_md0096_oled_clear_gram();
        atk_md0096_oled_show_string(0, 0, ATK_MD0096_OLED_FONT_SIZE_12, "PH Meter Start", ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_update();
        HAL_Delay(800);
        atk_md0096_oled_clear();
    }
}

void APP_Timer1sISR(void)
{
    APP_Time_Tick1s();
}

void APP_Task1s(void)
{
    float temp = 0.0f;
    float voltage = 0.0f;
    float ph = 7.00f;
    uint8_t temp_valid = 0;

    char time_str[32];
    char ph_str[16];
    char temp_str[16];
    char volt_str[16];
    char line[32];

    if (DS18B20_ReadTemperature(&temp))
    {
        g_last_temp = temp;
        g_temp_valid = 1;
        temp_valid = 1;
    }
    else if (g_temp_valid)
    {
        temp = g_last_temp;
        temp_valid = 1;
    }

    if (temp_valid)
    {
        ph = PH_ReadPH(temp, &voltage);
        format_fixed(ph_str, sizeof(ph_str), ph, 2);
        format_fixed(temp_str, sizeof(temp_str), temp, 2);
    }
    else
    {
        voltage = PH_ReadVoltage();
        snprintf(ph_str, sizeof(ph_str), "ERR");
        snprintf(temp_str, sizeof(temp_str), "ERR");
    }

    format_fixed(volt_str, sizeof(volt_str), voltage, 3);
    APP_Time_GetString(time_str, sizeof(time_str));

    if (g_oled_ready)
    {
        atk_md0096_oled_clear_gram();

        snprintf(line, sizeof(line), "PH:%s", ph_str);
        atk_md0096_oled_show_string(0, 0, ATK_MD0096_OLED_FONT_SIZE_12, line, ATK_MD0096_OLED_SHOW_MODE_NORMAL);

        snprintf(line, sizeof(line), "T:%sC", temp_str);
        atk_md0096_oled_show_string(0, 16, ATK_MD0096_OLED_FONT_SIZE_12, line, ATK_MD0096_OLED_SHOW_MODE_NORMAL);

        snprintf(line, sizeof(line), "V:%sV", volt_str);
        atk_md0096_oled_show_string(0, 32, ATK_MD0096_OLED_FONT_SIZE_12, line, ATK_MD0096_OLED_SHOW_MODE_NORMAL);

        atk_md0096_oled_show_string(0, 48, ATK_MD0096_OLED_FONT_SIZE_12, time_str, ATK_MD0096_OLED_SHOW_MODE_NORMAL);
        atk_md0096_oled_update();
    }

    printf("%s,PH=%s,T=%sC,V=%sV\r\n", time_str, ph_str, temp_str, volt_str);
}
