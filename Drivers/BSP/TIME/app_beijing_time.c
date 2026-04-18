#include "app_beijing_time.h"
#include <stdio.h>

static APP_Time_t g_time =
{
    .year  = 2026,
    .month = 4,
    .day   = 17,
    .hour  = 20,
    .min   = 30,
    .sec   = 0
};

static uint8_t is_leap_year(uint16_t year)
{
    return ((year % 4 == 0U && year % 100 != 0U) || (year % 400 == 0U));
}

static uint8_t days_in_month(uint16_t year, uint8_t month)
{
    static const uint8_t days_tbl[12] =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (month == 2U)
    {
        return days_tbl[1] + is_leap_year(year);
    }

    return days_tbl[month - 1U];
}

void APP_Time_InitDefault(void)
{
    g_time.year  = 2026;
    g_time.month = 4;
    g_time.day   = 17;
    g_time.hour  = 20;
    g_time.min   = 30;
    g_time.sec   = 0;
}

void APP_Time_Tick1s(void)
{
    g_time.sec++;
    if (g_time.sec >= 60U)
    {
        g_time.sec = 0;
        g_time.min++;
        if (g_time.min >= 60U)
        {
            g_time.min = 0;
            g_time.hour++;
            if (g_time.hour >= 24U)
            {
                g_time.hour = 0;
                g_time.day++;
                if (g_time.day > days_in_month(g_time.year, g_time.month))
                {
                    g_time.day = 1;
                    g_time.month++;
                    if (g_time.month > 12U)
                    {
                        g_time.month = 1;
                        g_time.year++;
                    }
                }
            }
        }
    }
}

void APP_Time_GetString(char *buf, size_t len)
{
    snprintf(buf, len, "%04u-%02u-%02u %02u:%02u:%02u",
             g_time.year, g_time.month, g_time.day,
             g_time.hour, g_time.min, g_time.sec);
}
