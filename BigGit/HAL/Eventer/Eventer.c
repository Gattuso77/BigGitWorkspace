//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"


//
// Module parameters (that are defined in the application modules that need a timer)
//

#define EVENT_COUNT     3
extern struct Eventer       Console_Event;
extern struct Eventer       OnBoardRedLED_Event;
extern struct Eventer       OnBoardGreenLED_Event;
struct Eventer * EventList[EVENT_COUNT] = { &Console_Event, &OnBoardRedLED_Event, &OnBoardGreenLED_Event };


//*****************************************************************************
//
// This function initializes event and MUST be called before running any other functions within this module
//
//*****************************************************************************
void Initialize_Events()
{
}


//*****************************************************************************
//
// Here we are setting an event that was fired during module execution.
// If event fired at the moment when we were processing some other event already,
// then we add current even to the shadow variable, which will be processed later (in the next iteration of super-loop)
//
//*****************************************************************************
void SetEvent(struct Eventer * eventer, uint32_t event)
{
    if(eventer->Flags & EVENT_FLAG_BUSY_WITH_EVENT)
        eventer->EventsShdw |= event;
    else
        eventer->Events |= event;
}


//*****************************************************************************
//
// This function runs our general event loop
//
//*****************************************************************************
void SpinEventLoop()
{
    uint8_t i;

    for(i = 0; i < EVENT_COUNT; i++)
    {
        if(EventList[i]->Events != 0 || EventList[i]->EventsShdw != 0)
        {
            //
            // First: set flag that we are currently busy with events
            //
            EventList[i]->Flags |= EVENT_FLAG_BUSY_WITH_EVENT;

            //
            // Then process all events that have been fired
            //
            EventList[i]->EventCB();

            //
            // Then check for the new events that might have arrived
            //
            EventList[i]->Events = 0;
            if(EventList[i]->EventsShdw != 0)
                EventList[i]->Events = EventList[i]->EventsShdw;

            //
            // Remove the flag: we ain't busy anymore, and just for the sake of full guarantee that we haven't missed anything when we were setting the flag: last line checker
            //
            EventList[i]->Flags &= ~EVENT_FLAG_BUSY_WITH_EVENT;
            EventList[i]->EventsShdw = ((~EventList[i]->Events) & EventList[i]->EventsShdw);   // should be = 0, but this is just for the case when new events fired while we were clearing the last flag
        }
    }
}
