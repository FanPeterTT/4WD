#include "Delay.h"
#include "main.h"

static unsigned int fac_us = 0;

void delay_init(unsigned int sysClk)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    fac_us = sysClk;
}

void delay_us(unsigned int nus)
{
    unsigned int ticks;
    unsigned int tOld, tNow, tCnt = 0;
    unsigned int reload = SysTick->LOAD;

    ticks = nus * fac_us;
    tOld = SysTick->VAL;

    while(1) {
        tNow = SysTick->VAL;
        if (tNow != tOld) {
            if (tNow < tOld) tCnt += tOld - tNow;
            else tCnt += reload - tNow + tOld;
            tOld = tNow;
            if (tCnt >= ticks)
                break;
        }
    }
}
void delay_ms(unsigned int nms)
{
    unsigned int i;

    for (i = 0; i < nms; i++)
        delay_us(1000);
}

