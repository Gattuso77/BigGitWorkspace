//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************

#include "GlobalInclude.h"
#include "GPIO_Manager.h"
#include "Timers/Timer_Interface.h"

/************************BEGINNING OF THE MODULE**********************************/
#if MODULE_ONBOARD_LEDS

//
// This Module Function prototypes
//
void OnBoardRedLED_Toggler();
void OnBoardGreenLED_Toggler();

//
// GPIO for LED control
//
const GPIO_SPD GPIO_OnBoardLEDs[2] = {   {GPIO_PORT_P1, GPIO_PIN0, GPIO_MODE_OUTPUT, GPIO_OPTION_NONE, "RED on-board LED"},
                                         {GPIO_PORT_P4, GPIO_PIN7, GPIO_MODE_OUTPUT, GPIO_OPTION_NONE, "GREEN on-board LED"}
                                        };



//
// Hardware module to pass to GPIO manager and System Manager
//
GPIO_GRS OnBoardLED_HWModule = {GPIO_OnBoardLEDs, 2, GPIO_PRIORITY_NORMAL};


//
// Here we define a simple timer that will toggle led: timer type, timer period, our module callback
//
struct Eventer     OnBoardRedLED_Event = { 0, 0, 0, OnBoardRedLED_Toggler};
struct Eventer     OnBoardGreenLED_Event = { 0, 0, 0, OnBoardGreenLED_Toggler};
struct TimerParams OnBoardRedLED_Timer = {TIMER_MODE_SIMPLE_PERIODIC, TIMER_TIME_1_SEC, &OnBoardRedLED_Event, true};
struct TimerParams OnBoardGreenLED_Timer = {TIMER_MODE_SIMPLE_PERIODIC, TIMER_TIME_100_mS, &OnBoardGreenLED_Event, true};


void InitApp_OnBoardLEDs()
{
    GPIO_setOutputLowOnPin(GPIO_OnBoardLEDs[0].SelectedPort, GPIO_OnBoardLEDs[0].SelectedPin);
    GPIO_setOutputLowOnPin(GPIO_OnBoardLEDs[1].SelectedPort, GPIO_OnBoardLEDs[1].SelectedPin);
}

//*****************************************************************************
//
// This function should be called by timer: Toggling RED LED
//
//*****************************************************************************
void OnBoardRedLED_Toggler()
{
    GPIO_toggleOutputOnPin(GPIO_OnBoardLEDs[0].SelectedPort, GPIO_OnBoardLEDs[0].SelectedPin);
}


//*****************************************************************************
//
// This function should be called by timer: Toogling Green LED
//
//*****************************************************************************
void OnBoardGreenLED_Toggler()
{
    GPIO_toggleOutputOnPin(GPIO_OnBoardLEDs[1].SelectedPort, GPIO_OnBoardLEDs[1].SelectedPin);
}



/************************END OF THE MODULE**********************************/
#endif
