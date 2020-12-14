#ifndef INA219_H
#define INA219_H

typedef struct {
    short voltage;
    long shunt;
    long current;
    long power;
}Ina219Data;

int ina219_initial(void);

int ina219_getVoltage_uV(void);

int ina219_getCurrent_mA(void);

int ina219_getPower_mW(void);

#endif
