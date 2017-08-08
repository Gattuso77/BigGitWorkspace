//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "SW/Console/Console_Interface.h"

//
// Firmware version
//
#define FW_VERSION_ID   "GIT_TEST_0.1"


//*****************************************************************************
//
// Included functions
//
//*****************************************************************************
void SpinEventLoop();               // From Eventer/Eventer.c
void Initialize_Peripherals();      // From Peripherals/Per_Manager.c
void Initialize_Events();           // From Eventer/Eventer.c
void Initialize_GPIOs();            // From GPIO/GPIO.c
void Initialize_AppData();          // From AppInitializer/App.c
void CheckModulesConflict();        // From Configs/Modules.c

uint16_t counter;

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    Initialize_GPIOs();
    Initialize_Peripherals();
    Initialize_Events();
    Initialize_AppData();
    CheckModulesConflict();
    // Setting P2.2 as SMCLK output
    P2DIR |= BIT2;
    P2SEL |= BIT2;

    __bis_SR_register(GIE);       // Enable interrupts
    __no_operation();             // For debugger

#if MODULE_CONSOLE_LOGGER
    Console.Log("Starting the GIT Testing Application!\n\r", CONSOLE_MODE_SYNC);
    Console.Log("Firmware version is: ", CONSOLE_MODE_SYNC);
    Console.Log(FW_VERSION_ID, CONSOLE_MODE_SYNC);
#endif

    while(true)
    {
        if(Console.IsBusy == false)
        {
            Console.ReportUint16Value("The counter value is: ", counter++, CONSOLE_MODE_ASYNC);
            Console.Log("New Counter Value has been logged\n\r", CONSOLE_MODE_ASYNC);
        }
        SpinEventLoop();
    }
}
