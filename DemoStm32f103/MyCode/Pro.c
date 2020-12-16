#include "Pro.h"

#include <stdio.h>

static Pro pro;

int pro_pktSend(char *buf, int bufLen, char cmd, char *para, int paraLen)
{
    if (buf == nullptr)
       return -1;

    int i = 0; 
    int sum = 0;

    buf[PRO_HEAD1] = 0xA5;
    buf[PRO_HEAD2] = 0x5A;
    buf[PRO_SRC] = 0x01;
    buf[PRO_DST] = 0x02;
    buf[PRO_LEN] = paraLen + 1;
    buf[PRO_CMD] = cmd;
    for (i = 0; i < paraLen; i++) {
        buf[PRO_PARA + i] = para[i];
        sum += para[i];
    }
    buf[PRO_CHECKSUM + paraLen - 1] = sum + buf[PRO_SRC] + buf[PRO_DST] + buf[PRO_LEN] + buf[PRO_CMD];
    buf[PRO_TAIL + paraLen - 1] = 0xFE;

    return PRO_TAIL + paraLen + 1;
}

int pro_pktRes(char *buf, int bufLen, char cmd, char sta)
{
    if (buf == nullptr)
       return -1;

    int i = 0; 
    int sum = 0;

    buf[PRO_HEAD1] = 0xA5;
    buf[PRO_HEAD2] = 0x5A;
    buf[PRO_SRC] = 0x01;
    buf[PRO_DST] = 0x02;
    buf[PRO_LEN] = 1 + 1;
    buf[PRO_CMD] = cmd;
    buf[PRO_PARA] = sta;
    buf[PRO_CHECKSUM] = sum + buf[PRO_SRC] + buf[PRO_DST] + buf[PRO_LEN] + buf[PRO_CMD] + buf[PRO_PARA];
    buf[PRO_TAIL] = 0xFE;

    return PRO_TAIL;
}


int main(void)
{
    printf("sizeof(pro) = %d\n", sizeof(Pro));

    char buf[128] = {0};
    char para[64] = {9};

    pro_pktSend(buf, sizeof(buf), 0xFF, para, sizeof(para));

    for (int i = 0; i < sizeof(buf); i++)
        printf("%02x ", buf[i]);
    printf("\n");

    return 0;
}