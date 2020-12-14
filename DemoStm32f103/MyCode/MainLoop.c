#include "MainLoop.h"
#include "Debug.h"
#include "main.h"
#include "Delay.h"

static void task_10Ms(unsigned int tickMs)
{
    static unsigned int lastTick;

    if (tickMs - lastTick >= 10) {

        lastTick = tickMs;
    }

    return;
}

static void task_50Ms(unsigned int tickMs)
{
    static unsigned int lastTick;

    if (tickMs - lastTick >= 50) {

        lastTick = tickMs;
    }

    return;
}

static void task_100Ms(unsigned int tickMs)
{
    static unsigned int lastTick;

    if (tickMs - lastTick >= 100) {

        lastTick = tickMs;
    }

    return;
}

static void task_500Ms(unsigned int tickMs)
{
    static unsigned int lastTick;

    if (tickMs - lastTick >= 500) {

        HAL_GPIO_TogglePin(RUN_LED_GPIO_Port, RUN_LED_Pin);

        lastTick = tickMs;
    }

    return;
}

static void task_1000Ms(unsigned int tickMs)
{
    static unsigned int lastTick;

    char strBuf[32] = {'\0'};
    if (tickMs - lastTick >= 1000) {
        sprintf(strBuf, "tickMs = %d ", tickMs);
        debug_str(strBuf);
        debug_str("hello world\r\n");

        lastTick = tickMs;
    }

    return;
}

void mainInitial(void)
{
    delay_init(72);
}

void mainLoop(void)
{
    unsigned int tickMs = 0;

    tickMs = HAL_GetTick();

    task_10Ms(tickMs);
    task_50Ms(tickMs);
    task_100Ms(tickMs);
    task_500Ms(tickMs);
    task_1000Ms(tickMs);

    delay_ms(5);
}

