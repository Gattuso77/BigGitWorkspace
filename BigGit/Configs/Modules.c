//******************************************************************************
//   HW: MFC-204 or MFC-204_revisionB, MSP430F5659
//   FW: MFC204_0.1
//******************************************************************************
#include "GlobalInclude.h"
#include "SW/Console/Console_Interface.h"


void CheckModulesConflict()
{
    bool moduleConflicts = false;


    //
    // Report about module conflicts: program should not start in case of the module conflicts
    //
    if(moduleConflicts)
    {
        while(true)
        {
#if MODULE_CONSOLE_LOGGER

            Console.Log("The program can not be started!\n\rIncompatible modules are activated simultaneously.\n\r", CONSOLE_MODE_SYNC);
#endif
            __delay_cycles(4000000);
        }
    }
}
