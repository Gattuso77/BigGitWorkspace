#ifndef HAL_PERIPHERALS_UART_UART_MANAGER_H_
#define HAL_PERIPHERALS_UART_UART_MANAGER_H_


#define UART_BUFFER_SIZE    128

//
// Receive register
//
struct UartRxReg       {    char            Buffer[UART_BUFFER_SIZE];
                            uint8_t         Index;
                            uint8_t         StopReceiveFlag;
                            uint32_t        Counter;
};

#define UART_RX_REG_INIT(v)     v.Index = 0;                \
                                v.Counter = 0;              \
                                v.StopReceiveFlag = 0;



//
// Transmit register
//
struct TxNode        {      struct TxNode * Next;
                            char            Buffer[UART_BUFFER_SIZE];
                            uint32_t        Counter;
                            uint8_t         MsgLength;
                            uint8_t         Index;
                            uint8_t         UID;
};
#define UART_TX_REG_INIT(v)     v.Counter = 0;                  \
                                v.MsgLength = 0;                \
                                v.Index = 0;                    \
                                v.UID = i;


//
// UART Register Structure
//
struct UartRegister {       void                (* Initialization)(struct UartParams * params);
                            uint16_t            BaseAddress;
                            struct TxNode *     ActiveNode;
                            struct TxNode *     SendingNode;
                            bool                IsDefined;
                            uint32_t            MsgDiscarded;
                            uint32_t            IntCnt;
                            uint16_t            IsBusy:1;
                            struct Eventer  *   Event;
};



#endif /* HAL_PERIPHERALS_UART_UART_MANAGER_H_ */
