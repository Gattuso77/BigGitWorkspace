//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"


//*****************************************************************************
//
// Included functions
// This module should contain only application specific initialisation functions from the appropriate HAL modules of specific modules
//
//*****************************************************************************
void InitApp_OnBoardLEDs();             // From SW/OnBoardLEDs/HAL_LEDs.c


//*****************************************************************************
//
// Initialising application specific data
//
//*****************************************************************************
void Initialize_AppData()
{
    //
    // Initialize Connectors LEDs
    //
#if MODULE_ONBOARD_LEDS
    InitApp_OnBoardLEDs();
#endif
}
