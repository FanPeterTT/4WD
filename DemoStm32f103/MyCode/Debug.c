#include "Debug.h"
#include "usart.h"

#include <string.h>

void debug_data(unsigned char *data, int len)
{
    HAL_UART_Transmit(&huart1, data, len, 100);
}

void debug_str(char *str)
{
    HAL_UART_Transmit(&huart1, (unsigned char *)str, strlen(str), 100);
}
