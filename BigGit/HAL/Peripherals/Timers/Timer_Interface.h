#ifndef HAL_PERIPHERALS_TIMERS_TIMER_INTERFACE_H_
#define HAL_PERIPHERALS_TIMERS_TIMER_INTERFACE_H_


enum TIMER_TYPE_EN  {       TIMER_MODE_SIMPLE_PERIODIC,
                            TIMER_MODE_HIT_AND_STOP
};


enum TIMER_COMMANDS_EN  {   TIMER_COMMAND_STOP,
                            TIMER_COMMAND_START,
                            TIMER_COMMAND_RECHARGE
};


//
// Timer values when the timer is soursced from ACLK and no dividers are applied
//
#define TIMER_TIME_2_SEC    0xffff
#define TIMER_TIME_1_SEC    32768
#define TIMER_TIME_500_mS   16384
#define TIMER_TIME_200_mS   6554
#define TIMER_TIME_100_mS   3277
#define TIMER_TIME_50_mS    1638
#define TIMER_TIME_30_mS    983
#define TIMER_TIME_20_mS    655
#define TIMER_TIME_10_mS    328
#define TIMER_TIME_5_mS     164
#define TIMER_TIME_2_mS     64
#define TIMER_TIME_1_mS     33


//
// Timer values when the timer is soursced from ACLK and divided by 8, hence can make longer tasks
//
#define TIMER_LONG_TIME_250_mSEC 0x0200
#define TIMER_LONG_TIME_1_SEC    0x07ff
#define TIMER_LONG_TIME_2_SEC    0x0FFE
#define TIMER_LONG_TIME_3_SEC    0x17FD
#define TIMER_LONG_TIME_4_SEC    0x1FFC
#define TIMER_LONG_TIME_10_SEC   0x4FF6
#define TIMER_LONG_TIME_20_SEC   0x9FEC
#define TIMER_LONG_TIME_32_SEC   0xffff


//
// The Timer Parameters that are passed from the other modules
//
struct TimerParams  {   uint8_t             TimerType;
                        uint16_t            Period;
                        struct Eventer  *   Event;
                        bool                RunOnStartup;
                        uint8_t             TimerIndex;
                        void                (* TimerUpdate)(struct TimerParams * timerParam , uint8_t timerCommand);
};




#endif /* HAL_PERIPHERALS_TIMERS_TIMER_INTERFACE_H_ */
