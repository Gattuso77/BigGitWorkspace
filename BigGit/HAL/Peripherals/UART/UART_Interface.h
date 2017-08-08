#ifndef HAL_PERIPHERALS_UART_UART_INTERFACE_H_
#define HAL_PERIPHERALS_UART_UART_INTERFACE_H_


enum UART_MODULES_EN    {       UART_MODULE_A1,
                                UART_MODULE_COUNT
};


//
// The UART Parameters that are passed from the other modules
//
struct UartParams  {    struct Eventer      *Event;
                        char                *RxBuffer;
                        uint8_t             *RxIndex;
                        uint8_t             *StopReceiveFlag;
                        uint8_t             ModuleIndex;
                        bool                IsInitialized;
};


//*****************************************************************************
//
// Public Functions For The Outside World
//
//*****************************************************************************
bool UART_SyncTransmission(uint8_t module, char * c);
bool UART_AsyncTransmission(uint8_t module, char * c, uint8_t length, bool sendInstantly);
bool UART_CheckForNewMsg(uint8_t module);




#endif /* HAL_PERIPHERALS_UART_UART_INTERFACE_H_ */
