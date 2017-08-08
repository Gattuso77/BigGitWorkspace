//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"


//*****************************************************************************
//
// Included functions
//
//*****************************************************************************
void Initialize_Timers();       // From Timers/Timer_Manager.c
void Initialize_UARTs();        // From UART/UART_Manager.c
void Initialize_ConsoleUart();  // From UART/UART_Manager.c

//*****************************************************************************
//
// These are peripherals that are initialized before all other GPIOs/Peripherals/interrups are initialized
// Make sure that appropriate GPIOs are initialized in GPIO_Manager
// Warning: yet no interrupts are available after peripheral initialization, GIE is set only after all others peripherals are initialized
//
//*****************************************************************************
void Initialize_CriticalPeripherals()
{
#if MODULE_CONSOLE_LOGGER
    Initialize_ConsoleUart();
#endif
}


//*****************************************************************************
//
// All peripheral initialization
//
//*****************************************************************************
void Initialize_Peripherals()
{
    //
    // Initialize timers
    //
    Initialize_Timers();

    //
    // Initialize UARTs
    //
    Initialize_UARTs();
}
