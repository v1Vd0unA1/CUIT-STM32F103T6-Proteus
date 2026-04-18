#include "delay_us.h"

static uint32_t g_ticks_per_us = 0;

void delay_us_init(void)
{
    g_ticks_per_us = HAL_RCC_GetHCLKFreq() / 1000000U;
    if (g_ticks_per_us == 0U)
    {
        g_ticks_per_us = 1U;
    }
}

void delay_us(uint32_t us)
{
    uint32_t reload = SysTick->LOAD + 1U;
    uint32_t ticks = us * g_ticks_per_us;
    uint32_t elapsed = 0U;
    uint32_t last = SysTick->VAL;

    while (elapsed < ticks)
    {
        uint32_t now = SysTick->VAL;

        if (now != last)
        {
            if (now < last)
            {
                elapsed += last - now;
            }
            else
            {
                elapsed += last + (reload - now);
            }
            last = now;
        }
    }
}
