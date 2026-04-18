#ifndef BSP_OLED_ATK_MD0096_H_
#define BSP_OLED_ATK_MD0096_H_

#include "main.h"
#include <stdint.h>

#define ATK_MD0096_OLED_WIDTH       128U
#define ATK_MD0096_OLED_HEIGHT      64U

#define ATK_MD0096_INTERFACE_8080   0
#define ATK_MD0096_INTERFACE_SPI    0
#define ATK_MD0096_INTERFACE_IIC    1

#define ATK_MD0096_FONT_12          1
#define ATK_MD0096_FONT_16          1
#define ATK_MD0096_FONT_24          1

#if (((ATK_MD0096_INTERFACE_8080 != 0) && (ATK_MD0096_INTERFACE_SPI != 0)) || \
     ((ATK_MD0096_INTERFACE_8080 != 0) && (ATK_MD0096_INTERFACE_IIC != 0)) || \
     ((ATK_MD0096_INTERFACE_SPI  != 0) && (ATK_MD0096_INTERFACE_IIC != 0)))
#error "Only one OLED interface can be enabled."
#endif

#if ((ATK_MD0096_INTERFACE_8080 == 0) && (ATK_MD0096_INTERFACE_SPI == 0) && (ATK_MD0096_INTERFACE_IIC == 0))
#undef ATK_MD0096_INTERFACE_IIC
#define ATK_MD0096_INTERFACE_IIC 1
#endif

#define ATK_MD0096_RST_GPIO_PORT    OLED_RST_GPIO_Port
#define ATK_MD0096_RST_GPIO_PIN     OLED_RST_Pin

#define ATK_MD0096_RST(x)           do{ (x) ? \
                                        HAL_GPIO_WritePin(ATK_MD0096_RST_GPIO_PORT, ATK_MD0096_RST_GPIO_PIN, GPIO_PIN_SET) : \
                                        HAL_GPIO_WritePin(ATK_MD0096_RST_GPIO_PORT, ATK_MD0096_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                      }while(0)

#define ATK_MD0096_EOK      0U
#define ATK_MD0096_ERROR    1U
#define ATK_MD0096_EINVAL   2U

typedef enum
{
    ATK_MD0096_OLED_SHOW_MODE_NORMAL = 0x00,
    ATK_MD0096_OLED_SHOW_MODE_REVERSE,
} atk_md0096_oled_show_mode_t;

typedef enum
{
#if (ATK_MD0096_FONT_12 != 0)
    ATK_MD0096_OLED_FONT_SIZE_12,
#endif
#if (ATK_MD0096_FONT_16 != 0)
    ATK_MD0096_OLED_FONT_SIZE_16,
#endif
#if (ATK_MD0096_FONT_24 != 0)
    ATK_MD0096_OLED_FONT_SIZE_24,
#endif
} atk_md0096_oled_font_size_t;

uint8_t atk_md0096_init(void);
void atk_md0096_hw_reset(void);
void atk_md0096_oled_display_on(void);
void atk_md0096_oled_display_off(void);
void atk_md0096_oled_update(void);
void atk_md0096_oled_clear(void);
void atk_md0096_oled_clear_gram(void);
uint8_t atk_md0096_oled_draw_point(uint8_t x, uint8_t y, atk_md0096_oled_show_mode_t mode);
uint8_t atk_md0096_oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, atk_md0096_oled_show_mode_t mode);
uint8_t atk_md0096_oled_fill(uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye, atk_md0096_oled_show_mode_t mode);
uint8_t atk_md0096_oled_show_char(uint8_t x, uint8_t y, atk_md0096_oled_font_size_t font_size, const char ch, atk_md0096_oled_show_mode_t mode);
uint8_t atk_md0096_oled_show_string(uint8_t x, uint8_t y, atk_md0096_oled_font_size_t font_size, const char *str, atk_md0096_oled_show_mode_t mode);
uint8_t atk_md0096_oled_show_num(uint8_t x, uint8_t y, atk_md0096_oled_font_size_t font_size, uint32_t num, uint8_t len, atk_md0096_oled_show_mode_t mode);

#endif /* BSP_OLED_ATK_MD0096_H_ */
