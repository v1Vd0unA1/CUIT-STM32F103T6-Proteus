#include "atk_md0096_iic.h"
#include "delay_us.h"

#if (ATK_MD0096_IIC_ADDR_3C != 0)
#define ATK_MD0096_IIC_ADDR 0x3CU
#elif (ATK_MD0096_IIC_ADDR_3D != 0)
#define ATK_MD0096_IIC_ADDR 0x3DU
#else
#error "One of ATK_MD0096_IIC_ADDR_3C and ATK_MD0096_IIC_ADDR_3D must be defined."
#endif

#define ATK_MD0096_IIC_WRITE        0U
#define ATK_MD0096_IIC_WRITE_CMD    0x00U
#define ATK_MD0096_IIC_WRITE_DAT    0x40U

static inline void atk_md0096_iic_delay(void)
{
    delay_us(2);
}

static void atk_md0096_iic_start(void)
{
    ATK_MD0096_IIC_SDAIN(1);
    ATK_MD0096_IIC_SCL(1);
    atk_md0096_iic_delay();
    ATK_MD0096_IIC_SDAIN(0);
    atk_md0096_iic_delay();
    ATK_MD0096_IIC_SCL(0);
    atk_md0096_iic_delay();
}

static void atk_md0096_iic_stop(void)
{
    ATK_MD0096_IIC_SDAIN(0);
    atk_md0096_iic_delay();
    ATK_MD0096_IIC_SCL(1);
    atk_md0096_iic_delay();
    ATK_MD0096_IIC_SDAIN(1);
    atk_md0096_iic_delay();
}

static uint8_t atk_md0096_iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;

    ATK_MD0096_IIC_SDAIN(1);
    atk_md0096_iic_delay();
    ATK_MD0096_IIC_SCL(1);
    atk_md0096_iic_delay();

    while (ATK_MD0096_IIC_READ_SDAOUT())
    {
        waittime++;
        if (waittime > 250U)
        {
            atk_md0096_iic_stop();
            rack = 1U;
            break;
        }
    }

    ATK_MD0096_IIC_SCL(0);
    atk_md0096_iic_delay();

    return rack;
}

static void atk_md0096_iic_write_byte(uint8_t dat)
{
    for (uint8_t t = 0; t < 8U; t++)
    {
        ATK_MD0096_IIC_SDAIN((dat & 0x80U) >> 7);
        atk_md0096_iic_delay();
        ATK_MD0096_IIC_SCL(1);
        atk_md0096_iic_delay();
        ATK_MD0096_IIC_SCL(0);
        dat <<= 1;
    }
    ATK_MD0096_IIC_SDAIN(1);
}

void atk_md0096_iic_init(void)
{
#if (ATK_MD0096_IIC_ADDR_3C != 0)
    ATK_MD0096_IIC_SA0(0);
#elif (ATK_MD0096_IIC_ADDR_3D != 0)
    ATK_MD0096_IIC_SA0(1);
#endif
    ATK_MD0096_IIC_SDAIN(1);
    ATK_MD0096_IIC_SCL(1);
    atk_md0096_iic_stop();
}

uint8_t atk_md0096_iic_write_cmd(uint8_t cmd)
{
    atk_md0096_iic_start();
    atk_md0096_iic_write_byte((uint8_t)((ATK_MD0096_IIC_ADDR << 1) | ATK_MD0096_IIC_WRITE));
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_write_byte(ATK_MD0096_IIC_WRITE_CMD);
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_write_byte(cmd);
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_stop();

    return 0U;
}

uint8_t atk_md0096_iic_write_data(uint8_t dat)
{
    atk_md0096_iic_start();
    atk_md0096_iic_write_byte((uint8_t)((ATK_MD0096_IIC_ADDR << 1) | ATK_MD0096_IIC_WRITE));
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_write_byte(ATK_MD0096_IIC_WRITE_DAT);
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_write_byte(dat);
    if (atk_md0096_iic_wait_ack() != 0U)
    {
        return 1U;
    }
    atk_md0096_iic_stop();

    return 0U;
}
