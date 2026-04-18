#ifndef BSP_APP_APP_TASK_H_
#define BSP_APP_APP_TASK_H_

#include "stm32f1xx_hal.h"

void APP_UserInit(void);
void APP_Timer1sISR(void);
void APP_Task1s(void);

#endif /* BSP_APP_APP_TASK_H_ */
