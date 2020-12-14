#include "Ds18b20.h"
#include "main.h"

void ds18b20_reset(void)
{
    DS18B20_IO_OUT();
    DS18B20_DQ_OUT(0x00);
    delay_us(720);
    DS18B20_DQ_OUT(0x01);
    delay_us(15);
}

char ds18b20_check(void)
{
    unsigned char retry = 0;
    DS18B20_IO_IN();
    while (DS18B20_DQ_IN() && retry < 200) {
        retry++;
        delay_us(1);
    };
    if (retry >= 200) return -1;
    else retry = 0;
    while (!DS18B20_DQ_IN() && retry < 240) {
        retry++;
        delay_us(1);
    }
    if (retry >= 240) return -1;
    return 0;
}

static char ds18b20_readBit(void)
{
    unsigned char data;

    DS18B20_IO_OUT();
    DS18B20_DQ_OUT(0x00);
    delay_us(2);
    DS18B20_DQ_OUT(0x01);
    DS18B20_IO_IN();
    delay_us(12);
    data = DS18B20_DQ_IN();
    delay_us(50);

    return data;
}

char ds18b20_readByte(void)
{
    unsigned char i, bit, data = 0;

    for (i = 0; i < 8; i++) {
        bit = ds18b20_readBit();
        data = bit << 7 | data >> 1;
    }

    return data;
}

static void ds18b20_writeBit(unsigned char bit)
{
    if ((bit & 0x01) == 0x01) {
        DS18B20_DQ_OUT(0x00);
        delay_us(2);
        DS18B20_DQ_OUT(0x01);
        delay_us(60);
    } else {
        DS18B20_DQ_OUT(0x00);
        delay_us(60);
        DS18B20_DQ_OUT(0x01);
        delay_us(2);
    }
}

void ds18b20_writeByte(unsigned char data)
{
    unsigned char i, bit;

    for (i = 0; i < 8; i++) {
        bit = data & 0x01;
        data = data >> 1;
        ds18b20_writeBit(bit);
    }
}

void ds18b20_start(void)
{
    ds18b20_reset();
    ds18b20_check();
    ds18b20_writeByte(0xCC);
    ds18b20_writeByte(0x44);
}

char ds18b20_initial(void)
{
    ds18b20_reset();
    return ds18b20_check();
}

short ds18b20_getTemp(void)
{
    unsigned char tempH, tempL;
    unsigned char isNegtive = 0x00;

    ds18b20_start();
    ds18b20_reset();
    ds18b20_check();
    ds18b20_writeByte(0xCC);
    ds18b20_writeByte(0xBE);
    tempL = ds18b20_readByte();
    tempH = ds18b20_readByte();
    if (tempH > 7) {
        tempH = ~tempH;
        tempL = ~tempL;
        isNegtive = 0x01;
    }

    return (double)((((short)tempH) << 8) + tempL) * 0.625 * ((isNegtive == 0x01) ? (-1) : 1);
}


