//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#ifndef EVENTER_EVENTER_H_
#define EVENTER_EVENTER_H_

enum EVENT_FLAGS_EN      {      EVENT_FLAG_BUSY_WITH_PROCESSING   = 0x01,
                                EVENT_FLAG_BUSY_WITH_EVENT        = 0x02
};

//
// Events are set as a flags for the 32-bit variable "Events" in structure Eventer
// Please, use first 16 bits(flags) as only standard Hardware specific and common events, such as timer/rx/tx/overflow/etc. that are defined HERE
// Please, for custom events use upper 16 bits from 0x00010000 to 0xf0000000 and override them in your specific module
//
enum POSSIBLE_EVENTS_EN  {  EVENTER_EVENT_TIMER             =   0x0001,
                            EVENTER_EVENT_CHAR_RECEIVED     =   0x0002,
                            EVENTER_EVENT_MSG_TRANSMITTED   =   0x0004,
                            EVENTER_EVENT_OVERFLOW          =   0x0008,
                            EVENTER_EVENT_RECEIVE_COLLISION =   0x0010,
                            /* Application Specific Events from 0x00010000 */
};


struct Eventer  {   uint32_t    Events;
                    uint32_t    EventsShdw;
                    uint32_t    Flags;
                    void        (* EventCB)(void);
};

//
// Function prototype to utilize by other module that uses events
//
void SetEvent(struct Eventer * eventer, uint32_t event);


#endif /* EVENTER_EVENTER_H_ */
