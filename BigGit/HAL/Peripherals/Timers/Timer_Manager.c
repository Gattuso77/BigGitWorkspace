//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "Timer_Manager.h"


//*****************************************************************************
//
// Included functions
//
//*****************************************************************************
void Timer_A0_Initialization();
void Timer_A0_Update(struct TimerParams * timerParam , uint8_t timerCommand);


//
// Timer Desciptors (indipendant instances)
//
extern struct TimerEvent Timer_A0_Events[TIMER_A0_EVENT_COUNT];


//
// Module parameters (that are defined in the application modules that need a timer)
//
extern struct TimerParams OnBoardRedLED_Timer;
extern struct TimerParams OnBoardGreenLED_Timer;


//
// Macro that is used to initialize timer module
// timerEvents: an array of TimerEvent structures that stores the events of particular timer instance
// updateFunc:  function that updates the status/mode of particular timer instance
// index:       index of the event of the TimerEvent array
// event:       particular event that we want to assign to the timer event (that will be fired in timer interrupt)
//
#define INIT_TIMER_EVENT(timerEvents, updateFunc, index, event)         \
        timerEvents[index].TimerType = event.TimerType;                 \
        timerEvents[index].PeriodValue = event.Period;                  \
        timerEvents[index].Event = event.Event;                         \
        timerEvents[index].IsDefined = true;                            \
        event.TimerIndex = index;                                       \
        event.TimerUpdate = updateFunc;                                 \
        if(event.RunOnStartup)                                          \
            updateFunc(&event, TIMER_COMMAND_START);


//*****************************************************************************
//
//  Initializing all timers
//
//*****************************************************************************
void Initialize_Timers()
{
    //
    // We will sacrifice Timer A0 to the debugger needs, initialize all capture compare registers
    //
    // Diagnostic LED
#if MODULE_ONBOARD_LEDS
    INIT_TIMER_EVENT(Timer_A0_Events, Timer_A0_Update, 0, OnBoardRedLED_Timer)
    INIT_TIMER_EVENT(Timer_A0_Events, Timer_A0_Update, 1, OnBoardGreenLED_Timer)
#endif
    // Initializing Timer A0
    Timer_A0_Initialization();
}
