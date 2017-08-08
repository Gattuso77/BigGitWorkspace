//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************

#include "GlobalInclude.h"
#include "UART/UART_Interface.h"
#include "UART/UART_Manager.h"

//
// UART Modules available
//
extern struct UartRegister UART_A1;

//
// General Module Handler
//
struct UartRegister *   UartRegs[UART_MODULE_COUNT] =  { &UART_A1 };
struct UartRegister *   UartReg;

//
// Module parameters (that are defined in the application modules that need UART)
//
#if MODULE_CONSOLE_LOGGER
extern struct UartParams Console_Uart;
#endif


//*****************************************************************************
//
// Initialization of the console UART that should be called from some outer module (GPIO manager) before all others peripherals are initialized
//
//*****************************************************************************
void Initialize_ConsoleUart()
{
#if MODULE_CONSOLE_LOGGER
    //
    // Initialize UART for Console, only if other modules do not utilize the UART port already
    //
    UART_A1.Initialization(&Console_Uart);
#endif
}


//*****************************************************************************
//
// Initializing all other UART modules
// Baudrates/parity/stopbits and other settings are set within the UART specific module initialization routine
//
//*****************************************************************************
void Initialize_UARTs()
{
}



//*****************************************************************************
//
// Synchronous Transmission
//
//*****************************************************************************
bool UART_SyncTransmission(uint8_t module, char * c)
{
    //
    // Checking selection sanity
    //
    if(module >= UART_MODULE_COUNT)
    {
        while(1) {};
    }
    UartReg = UartRegs[module];


    //
    // If asynchronous transmission is currently running: return false
    //
    if(UartReg->IsBusy == true)
        return false;

    //
    // Send chars synchronously
    //
    while(*c != '\0')
        USCI_A_UART_transmitData(UartReg->BaseAddress, *c++);


    return true;
}



//*****************************************************************************
//
// Asynchronous transmission
//
//*****************************************************************************
bool UART_AsyncTransmission(uint8_t module, char * c, uint8_t length, bool sendInstantly)
{
    //
    // Checking selection sanity
    //
    if(module >= UART_MODULE_COUNT)
    {
        while(1) {};
    }
    UartReg = UartRegs[module];


    if(UartReg->ActiveNode->MsgLength > 0)
    {
        UartReg->MsgDiscarded++;
            return false;     // Discard as there is space available in transmit list
    }

    //
    // Filling the structure
    //
    UartReg->ActiveNode->Index = 0;
    while(UartReg->ActiveNode->Index < length)
        UartReg->ActiveNode->Buffer[UartReg->ActiveNode->Index++] = *c++;


    //
    // Resetting parameters to the initial state
    //
    UartReg->ActiveNode->Index = 0;
    UartReg->ActiveNode->MsgLength = length;


    //
    // We should now point to the next structure
    //
    UartReg->ActiveNode = UartReg->ActiveNode->Next;

    if(sendInstantly == false)
        SetEvent(UartReg->Event, EVENTER_EVENT_MSG_TRANSMITTED);
    else
        UART_CheckForNewMsg(module);

    return true;
}



//*****************************************************************************
//
// Checking for a new message and setting Tx interrupt if any is pending
// Boolean return: were we able to send a data or the transmit module is busy and we need to wait
//
//*****************************************************************************
bool UART_CheckForNewMsg(uint8_t module)
{
    //
    // Checking selection sanity
    //
    if(module >= UART_MODULE_COUNT)
    {
        while(1) {};
    }
    UartReg = UartRegs[module];

    if(UartReg->SendingNode->MsgLength > 0 && UartReg->IsBusy == false)
    {
        UartReg->IsBusy = true;
        UartReg->SendingNode->Counter++;

        //
        // Enable Tx Interrupts, inside the interrupt we will also insert the character
        //
        USCI_A_UART_enableInterrupt(UartReg->BaseAddress, USCI_A_UART_TRANSMIT_INTERRUPT);

        return true;
    }
    else
        return false;
}
