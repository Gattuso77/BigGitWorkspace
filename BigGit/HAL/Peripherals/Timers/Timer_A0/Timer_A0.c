//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "Timers/Timer_Manager.h"


//
// Timer Descriptor
//
struct TimerEvent Timer_A0_Events[TIMER_A0_EVENT_COUNT] = {{0, &TA0CCTL0, &TA0CCR0}, {0, &TA0CCTL1, &TA0CCR1}, {0, &TA0CCTL2, &TA0CCR2}, {0, &TA0CCTL3, &TA0CCR3}, {0, &TA0CCTL4, &TA0CCR4}};


//*****************************************************************************
//
// Timer Initialization
//
//*****************************************************************************
void Timer_A0_Initialization()
{
    //
    // CTL register
    //
    TA0CTL = TASSEL__ACLK  + MC__CONTINOUS  + TACLR;              // ACLK, upmode, clear TAR
}


//*****************************************************************************
//
// Function that updates the timer status
//
//*****************************************************************************
void Timer_A0_Update(struct TimerParams * timerParam , uint8_t timerCommand)
{
    struct TimerEvent * timer;
    if(timerParam->TimerIndex >= TIMER_A0_EVENT_COUNT)
    {
        while(1) {}; //TODO
    }

    timer = &Timer_A0_Events[timerParam->TimerIndex];
    switch(timerCommand)
    {
    case TIMER_COMMAND_STOP:
        *(timer->CtlReg) &= !CCIE;
        break;
    case TIMER_COMMAND_START:
        timer->PeriodValue = timerParam->Period;
        *(timer->TimeReg) = TA0R + timerParam->Period;
        *(timer->CtlReg) &= !CCIFG;
        *(timer->CtlReg) |= CCIE;
        break;
    case TIMER_COMMAND_RECHARGE:
        *(timer->CtlReg) &= !CCIE;
        timer->PeriodValue = timerParam->Period;
        *(timer->TimeReg) = TA0R + timerParam->Period;
        *(timer->CtlReg) &= !CCIFG;
        *(timer->CtlReg) |= CCIE;
        break;
    default:
        while(1) {};            //TODO
    }
}

//
// Timer interrupt handler
//
#define TIMER_INTERRUPT_EVENT_HANDLER(v)    if(Timer_A0_Events[v].IsDefined)                                                    \
                                            {                                                                                   \
                                                if(Timer_A0_Events[v].TimerType == TIMER_MODE_HIT_AND_STOP)                     \
                                                    *(Timer_A0_Events[v].CtlReg) &= !CCIE;     /* stopping the timer */         \
                                                *(Timer_A0_Events[v].TimeReg) += Timer_A0_Events[v].PeriodValue;                \
                                                SetEvent(Timer_A0_Events[v].Event, EVENTER_EVENT_TIMER);                        \
                                            }


// Timer0 A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    TIMER_INTERRUPT_EVENT_HANDLER(0)
}


// Timer0_A5 Interrupt Vector (TAIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) TIMER0_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(TA0IV,14))
  {
    case  0: break;                         // No interrupt
    case  2:                                // CCR1
        TIMER_INTERRUPT_EVENT_HANDLER(1)
        break;
    case  4:                                // CCR2
        TIMER_INTERRUPT_EVENT_HANDLER(2)
        break;
    case  6:                                // CCR3
        TIMER_INTERRUPT_EVENT_HANDLER(3)
        break;
    case  8:                                // CCR4
        TIMER_INTERRUPT_EVENT_HANDLER(4)
        break;
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;                          // overflow
    default: break;
  }
}
