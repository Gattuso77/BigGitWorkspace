//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "UART\UART_Interface.h"
#include "SW/Console/Console_Interface.h"


//
// This Module Function prototypes
//
void ConsoleEvents();


//
// Events of Rx and Tx
//
struct Eventer Console_Event = { 0, 0, 0, ConsoleEvents};
struct UartParams Console_Uart = {&Console_Event};



//*****************************************************************************
//
// Sending Console Message Synchronously
//
//*****************************************************************************
void HAL_Console_TxSync(char * c)
{
    if(Console_Uart.IsInitialized == true)
        UART_SyncTransmission(Console_Uart.ModuleIndex, c);
}



//*****************************************************************************
//
// Sending Console Message Asynchronously
//
//*****************************************************************************
void HAL_Console_TxAsync(char * c, uint8_t length)
{
    if(Console_Uart.IsInitialized == true)
        UART_AsyncTransmission(Console_Uart.ModuleIndex, c, length, false);
}


//*****************************************************************************
//
// Possible events: Tx/Rx/Break/Error
//
//*****************************************************************************
void ConsoleEvents()
{
    //
    // Handling receive event
    //
    if(Console_Event.Events & EVENTER_EVENT_CHAR_RECEIVED)
    {
        //TODO: We are not anticipating any receive characters in console
    }


    //
    // Handling transmit event
    //
    if(Console_Event.Events & EVENTER_EVENT_MSG_TRANSMITTED)          // we are ready to transmit?
    {
        Console.IsBusy = UART_CheckForNewMsg(Console_Uart.ModuleIndex);                // then: transmit if possible
    }


    //
    // Handling overflow event
    //
    if(Console_Event.Events & EVENTER_EVENT_OVERFLOW)
    {
        while(true) {};// TODO: inform about error
    }
}
