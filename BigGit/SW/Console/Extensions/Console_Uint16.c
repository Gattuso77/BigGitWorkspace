#include "GlobalInclude.h"
#include "SW/Console/Console_Interface.h"

//
// Included Functions and Variables
//
extern char complexMsg[128];
void HAL_Console_TxSync(char * c);
void HAL_Console_TxAsync(char * c, uint8_t length);



void ReportUint16Value(char * msg, uint16_t value, uint8_t mode)
{
    uint8_t i = 0;

    while(*msg != '\0' && i < 200)
    {
        complexMsg[i++] = *msg++;
    }


    if(value >= 10000)
    {
        complexMsg[i++] = '0' + (value / 10000);
        complexMsg[i++] = '0' + ((value % 10000) / 1000);
        complexMsg[i++] = '0' + ((value % 1000) / 100);
        complexMsg[i++] = '0' + ((value % 100) / 10);
        complexMsg[i++] = '0' + (value % 10);
    }
    else if(value >= 1000)
    {
        complexMsg[i++] = '0' + (value / 1000);
        complexMsg[i++] = '0' + ((value % 1000) / 100);
        complexMsg[i++] = '0' + ((value % 100) / 10);
        complexMsg[i++] = '0' + (value % 10);
    }
    else if(value >= 100)
    {
        complexMsg[i++] = '0' + (value / 100);
        complexMsg[i++] = '0' + ((value % 100) / 10);
        complexMsg[i++] = '0' + (value % 10);
    }
    else if(value >= 10)
    {
        complexMsg[i++] = '0' + (value / 10);
        complexMsg[i++] = '0' + (value % 10);
    }
    else
    {
        complexMsg[i++] = '0' + value;
    }

    complexMsg[i++] = '\n';
    complexMsg[i++] = '\r';
    complexMsg[i++] = '\0';


    if(mode == CONSOLE_MODE_SYNC)
    {
        //
        // Report in sync mode
        //
        HAL_Console_TxSync(complexMsg);
    }
    else if(mode == CONSOLE_MODE_ASYNC)
    {
        //
        // Report in async mode
        //
        HAL_Console_TxAsync(complexMsg, i);
    }
}
