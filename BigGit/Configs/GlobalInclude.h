#ifndef CONFIGS_GLOBALINCLUDE_H_
#define CONFIGS_GLOBALINCLUDE_H_

#include "driverlib.h"
#include "Settings.h"
#include "Modules.h"
#include "Eventer.h"


#define TRUE    1
#define FALSE   0

#define SET_BIT(val, bitIndex)      val |= ((Uint32)1 << bitIndex)
#define CLEAR_BIT(val, bitIndex)    val &= ~((Uint32)1 << bitIndex)
#define TOGGLE_BIT(val, bitIndex)   val ^= ((Uint32)1 << bitIndex)
#define BIT_IS_SET(val, bitIndex)   (val >> bitIndex) & 1

/********* For compatibility between C2000, MSP430, and TM4C (Tiva) processors ***************/
struct LNG_REG {
    unsigned int  LSW;
    unsigned int  MSW;
};

union LNG_GROUP {
    unsigned long  all;
    struct  LNG_REG  half;
};


#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

typedef unsigned int    Uint16;
typedef unsigned long   Uint32;





#endif /* CONFIGS_GLOBALINCLUDE_H_ */
