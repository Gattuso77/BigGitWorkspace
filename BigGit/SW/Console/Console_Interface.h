#ifndef SW_CONSOLE_CONSOLE_INTERFACE_H_
#define SW_CONSOLE_CONSOLE_INTERFACE_H_


#include "GPIO_Manager.h"

enum CONSOLE_MODE_EN        {   CONSOLE_MODE_SYNC,
                                CONSOLE_MODE_ASYNC
};

struct Console  {   bool                        IsBusy;
                    void    (* Log)             (char * data, uint8_t mode);
                    void    (* ReportGPIOInit)  (const GPIO_SPD * gpio);
                    void    (*ReportUint16Value)(char * msg, uint16_t value, uint8_t mode);
};

//
// Structure that can be used by all modules that need Console functionality
//
extern struct Console Console;




#endif /* SW_CONSOLE_CONSOLE_INTERFACE_H_ */
