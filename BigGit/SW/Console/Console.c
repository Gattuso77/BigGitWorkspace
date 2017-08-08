//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************
#include "GlobalInclude.h"
#include "SW/Console/Console_Interface.h"


//
// Function prototypes from HAL
//
void HAL_Console_TxSync(char * c);
void HAL_Console_TxAsync(char * c, uint8_t length);

//
// Available functions for Console Module
//
void Log(char * data, uint8_t mode);
void ReportGPIOInit(const GPIO_SPD * gpio);
void ReportUint16Value(char * msg, uint16_t value, uint8_t mode);

//
// Structure that is responsible  for Console operation handling
//
struct Console Console = {false, Log, ReportGPIOInit, ReportUint16Value};
char complexMsg[128];


//*****************************************************************************
//
// General function that transmit data to the host-system via interface
//
//*****************************************************************************
void Log(char * data, uint8_t mode)
{
    uint8_t length = 0;
    char *initAddr = data;

    if(mode == CONSOLE_MODE_SYNC)
    {
        HAL_Console_TxSync(data);
    }
    else if(mode == CONSOLE_MODE_ASYNC)
    {
        while(*data++ != '\0')
            length++;
        HAL_Console_TxAsync(initAddr, length);
    }
    else
    {
        HAL_Console_TxSync("Error: firmware tried to run unsupported transmit mode!");
    }
}
