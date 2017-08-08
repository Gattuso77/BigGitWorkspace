#ifndef HAL_PERIPHERALS_TIMERS_TIMER_MANAGER_H_
#define HAL_PERIPHERALS_TIMERS_TIMER_MANAGER_H_

#include "Timer_Interface.h"


#define TIMER_A0_EVENT_COUNT        5
#define TIMER_A1_EVENT_COUNT        3
#define TIMER_A2_EVENT_COUNT        3
#define TIMER_B_EVENT_COUNT         7


//
// Event that is associated with timer or timer Capture/Compare register
//
struct TimerEvent {     bool                            IsDefined;
                        volatile uint16_t  * const      CtlReg;
                        volatile uint16_t  * const      TimeReg;
                        uint8_t                         TimerType;
                        struct Eventer  *               Event;
                        uint16_t                        PeriodValue;
};




#endif /* HAL_PERIPHERALS_TIMERS_TIMER_MANAGER_H_ */
