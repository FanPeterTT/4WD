#ifndef __PRO_H__
#define __PRO_H__

#define nullptr ((void *)0)

typedef enum {
    PRO_HEAD1 = 0x00,
    PRO_HEAD2,
    PRO_SRC,
    PRO_DST,
    PRO_LEN,
    PRO_CMD,
    PRO_PARA,
    PRO_CHECKSUM,
    PRO_TAIL,
}PRO;

typedef struct {
    char head1;
    char head2;
    char src;
    char dst;
    char len;
    char cmd;
    char checkSum;
    char tail;
    char *para;
}Pro;

typedef union {
    Pro pro;
    char buf[72];
}UPro;

#endif