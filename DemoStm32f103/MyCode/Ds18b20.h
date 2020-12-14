#ifndef DS18B20_H
#define DS18B20_H

#include "main.h"

#define DS18B20_IO_IN()     {   \
                                GPIOB->CRH &= ~(3 << (5 * 2));\
                                GPIOB->CRH |= 0 << 5 * 2; \
                            }

#define DS18B20_IO_OUT()    {   \
                                GPIOB->CRH &= ~(3 << (5 * 2));\
                                GPIOB->CRH |= 1 << (5 * 2); \
                            }

#define DS18B20_DQ_OUT(val) HAL_GPIO_WritePin(DS18b20_DQ_GPIO_Port, DS18b20_DQ_Pin, val == 0x00 ? GPIO_PIN_RESET : GPIO_PIN_SET)

#define DS18B20_DQ_IN()     HAL_GPIO_ReadPin(DS18b20_DQ_GPIO_Port, DS18b20_DQ_Pin)


char ds18b20_initial(void);
short ds18b20_getTemp(void);

#endif
