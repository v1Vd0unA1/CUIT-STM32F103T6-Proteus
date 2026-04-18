#ifndef BSP_OLED_ATK_MD0096_IIC_H_
#define BSP_OLED_ATK_MD0096_IIC_H_

#include "main.h"
#include <stdint.h>

#define ATK_MD0096_IIC_ADDR_3C  1
#define ATK_MD0096_IIC_ADDR_3D  0

#if ((ATK_MD0096_IIC_ADDR_3C != 0) && (ATK_MD0096_IIC_ADDR_3D != 0))
#error "Only one OLED IIC address can be enabled."
#endif

#if ((ATK_MD0096_IIC_ADDR_3C == 0) && (ATK_MD0096_IIC_ADDR_3D == 0))
#undef ATK_MD0096_IIC_ADDR_3C
#define ATK_MD0096_IIC_ADDR_3C 1
#endif

#define ATK_MD0096_IIC_SA0_GPIO_PORT      OLED_SA0_GPIO_Port
#define ATK_MD0096_IIC_SA0_GPIO_PIN       OLED_SA0_Pin
#define ATK_MD0096_IIC_SCL_GPIO_PORT      OLED_SCL_GPIO_Port
#define ATK_MD0096_IIC_SCL_GPIO_PIN       OLED_SCL_Pin
#define ATK_MD0096_IIC_SDAIN_GPIO_PORT    OLED_SDAIN_GPIO_Port
#define ATK_MD0096_IIC_SDAIN_GPIO_PIN     OLED_SDAIN_Pin
#define ATK_MD0096_IIC_SDAOUT_GPIO_PORT   OLED_SDAOUT_GPIO_Port
#define ATK_MD0096_IIC_SDAOUT_GPIO_PIN    OLED_SDAOUT_Pin

#define ATK_MD0096_IIC_SA0(x)     do{ (x) ? \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SA0_GPIO_PORT, ATK_MD0096_IIC_SA0_GPIO_PIN, GPIO_PIN_SET) : \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SA0_GPIO_PORT, ATK_MD0096_IIC_SA0_GPIO_PIN, GPIO_PIN_RESET); \
                                    }while(0)
#define ATK_MD0096_IIC_SCL(x)     do{ (x) ? \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SCL_GPIO_PORT, ATK_MD0096_IIC_SCL_GPIO_PIN, GPIO_PIN_SET) : \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SCL_GPIO_PORT, ATK_MD0096_IIC_SCL_GPIO_PIN, GPIO_PIN_RESET); \
                                    }while(0)
#define ATK_MD0096_IIC_SDAIN(x)   do{ (x) ? \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SDAIN_GPIO_PORT, ATK_MD0096_IIC_SDAIN_GPIO_PIN, GPIO_PIN_SET) : \
                                      HAL_GPIO_WritePin(ATK_MD0096_IIC_SDAIN_GPIO_PORT, ATK_MD0096_IIC_SDAIN_GPIO_PIN, GPIO_PIN_RESET); \
                                    }while(0)
#define ATK_MD0096_IIC_READ_SDAOUT() HAL_GPIO_ReadPin(ATK_MD0096_IIC_SDAOUT_GPIO_PORT, ATK_MD0096_IIC_SDAOUT_GPIO_PIN)

void atk_md0096_iic_init(void);
uint8_t atk_md0096_iic_write_cmd(uint8_t cmd);
uint8_t atk_md0096_iic_write_data(uint8_t dat);

#endif /* BSP_OLED_ATK_MD0096_IIC_H_ */
