//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "GPIO_Manager.h"
#include "UART/UART_Interface.h"
#include "UART/UART_Manager.h"

#define TX_NODES_COUNT  8

//
// Function Prototypes
//
void UART_A1_Initialization();


//
// Dedicated GPIOs for UART0
//
const GPIO_SPD GPIO_USCI1[2] =   {{GPIO_PORT_P4, GPIO_PIN5, GPIO_MODE_PERIPHERAL, GPIO_OPTION_NONE, "UCA1:RX"},
                                  {GPIO_PORT_P4, GPIO_PIN4, GPIO_MODE_PERIPHERAL, GPIO_OPTION_NONE, "UCA1:TX"}};

//
// Hardware module to pass to GPIO manager and System Manager
//
GPIO_GRS USCI1_HWModule = {GPIO_USCI1, 2, GPIO_PRIORITY_CRITICAL};

//
// Tx and Rx Structures
//
static struct UartRxReg        RxReg;
static struct TxNode TxNodes[TX_NODES_COUNT] = { {&TxNodes[1]}, {&TxNodes[2]}, {&TxNodes[3]}, {&TxNodes[4]}, {&TxNodes[5]}, {&TxNodes[6]}, {&TxNodes[7]}, {&TxNodes[0]} };


//
// UART Descriptor
//
struct UartRegister UART_A1 = {UART_A1_Initialization, USCI_A1_BASE, TxNodes, TxNodes, 0, 0, 0, 0};



//*****************************************************************************
//
// UART A0 Initialization
//
//*****************************************************************************
void UART_A1_Initialization(struct UartParams * params)
{
    uint8_t i;
    //Baudrate = 9600, clock source = SMCLK, clock freq = 1.048MHz
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 3;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if(STATUS_FAIL == USCI_A_UART_init(UART_A1.BaseAddress, &param))
    {
        return;
    }

    //Enable UART module for operation
    USCI_A_UART_enable(UART_A1.BaseAddress);

    //Enable Receive Interrupt
    USCI_A_UART_clearInterrupt(UART_A1.BaseAddress,
                               USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(UART_A1.BaseAddress,
                                USCI_A_UART_RECEIVE_INTERRUPT);


    UART_RX_REG_INIT(RxReg);
    for(i = 0; i < TX_NODES_COUNT; i++)
    {
        UART_TX_REG_INIT(TxNodes[i]);
    }

    params->RxBuffer = &RxReg.Buffer[0];
    params->RxIndex =  &RxReg.Index;
    params->StopReceiveFlag = &RxReg.StopReceiveFlag;
    params->ModuleIndex = UART_MODULE_A1;
    params->IsInitialized = true;


    //
    // Associating the event that will be fired in UART interrupt
    //
    UART_A1.Event = params->Event;
    UART_A1.IsDefined = true;
}


//******************************************************************************
//
//This is the USCI_A1 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A1_VECTOR)))
#endif
void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV,4))
    {
    case 0:break;                             // Vector 0 - no interrupt
    case 2:                                   // Vector 2 - RXIFG
        RxReg.Counter++;
        if(RxReg.StopReceiveFlag == 1)
        {
            if(UART_A1.IsDefined)
                SetEvent(UART_A1.Event, EVENTER_EVENT_RECEIVE_COLLISION);
        }
        else if(RxReg.Index < UART_BUFFER_SIZE)
        {
            RxReg.Buffer[RxReg.Index++] = USCI_A_UART_receiveData(UART_A1.BaseAddress);
            if(UART_A1.IsDefined)
                SetEvent(UART_A1.Event, EVENTER_EVENT_CHAR_RECEIVED);
        }
        else
        {
            if(UART_A1.IsDefined)
                SetEvent(UART_A1.Event, EVENTER_EVENT_OVERFLOW);
        }
        break;
    case 4:                                   // Vector 2 - TXIFG
        if(UART_A1.SendingNode->Index < UART_A1.SendingNode->MsgLength)
                USCI_A_UART_transmitData(UART_A1.BaseAddress, UART_A1.SendingNode->Buffer[UART_A1.SendingNode->Index++]);
        else
        {
            UART_A1.SendingNode->MsgLength = 0;
            UART_A1.SendingNode->Index = 0;
            UART_A1.SendingNode = UART_A1.SendingNode->Next;
            UART_A1.IsBusy = false;

            //
            // Report the event
            //
            if(UART_A1.IsDefined)
            {
                SetEvent(UART_A1.Event, EVENTER_EVENT_MSG_TRANSMITTED);
            }

            //
            // Disable Tx Interrupts
            //
            USCI_A_UART_disableInterrupt(UART_A1.BaseAddress, USCI_A_UART_TRANSMIT_INTERRUPT);
            UCA1IFG |= UCTXIFG;         // setting once again the Tx flag TODO: mask it somehow, so there is no direct register access
        }
        break;
    default: break;
    }
}
