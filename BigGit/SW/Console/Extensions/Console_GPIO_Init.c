#include "GlobalInclude.h"
#include "GPIO_Manager.h"
#include "SW/Console/Console_Interface.h"


//
// Included Functions and Variables
//
extern char complexMsg[128];
void HAL_Console_TxSync(char * c);


const char * GPIOmsgTemplate = "has been initialised as ";
const char * GPIOmsgTemplateAsIn = "Input";
const char * GPIOmsgTemplateAsOut = "Output";
const char * GPIOmsgTemplateAsPeripheral = "Peripheral";
const char * GPIOmsgTemplateAsErr = "Error";

//*****************************************************************************
//
// Function that checks, if there are GPIO conflicts
//
//*****************************************************************************
void ReportGPIOInit(const GPIO_SPD * gpio)
{
    uint8_t i = 0;
    const char * seeker = GPIOmsgTemplate;

    complexMsg[i++] = 'G';
    complexMsg[i++] = 'P';
    complexMsg[i++] = 'I';
    complexMsg[i++] = 'O';
    complexMsg[i++] = ' ';
    complexMsg[i++] = gpio->SelectedPort + 0x30;
    complexMsg[i++] = '.';

    switch(gpio->SelectedPin)
    {
    case GPIO_PIN0:
        complexMsg[i++] = 0x30 + 0;
        break;
    case GPIO_PIN1:
        complexMsg[i++] = 0x30 + 1;
        break;
    case GPIO_PIN2:
        complexMsg[i++] = 0x30 + 2;
        break;
    case GPIO_PIN3:
        complexMsg[i++] = 0x30 + 3;
        break;
    case GPIO_PIN4:
        complexMsg[i++] = 0x30 + 4;
        break;
    case GPIO_PIN5:
        complexMsg[i++] = 0x30 + 5;
        break;
    case GPIO_PIN6:
        complexMsg[i++] = 0x30 + 6;
        break;
    case GPIO_PIN7:
        complexMsg[i++] = 0x30 + 7;
        break;
    case GPIO_PIN8:
        complexMsg[i++] = 0x30 + 8;
        break;
    case GPIO_PIN9:
        complexMsg[i++] = 0x30 + 9;
        break;
    default:
        complexMsg[i++] = 0x30;
    }

    complexMsg[i++] = ' ';

    seeker = GPIOmsgTemplate;
    while(*seeker != '\0')
        complexMsg[i++] = *seeker++;

    switch(gpio->PinType)
    {
    case GPIO_MODE_INPUT:
        seeker = GPIOmsgTemplateAsIn;
        break;
    case GPIO_MODE_OUTPUT:
        seeker = GPIOmsgTemplateAsOut;
        break;
    case GPIO_MODE_PERIPHERAL:
        seeker = GPIOmsgTemplateAsPeripheral;
        break;
    default:
        seeker = GPIOmsgTemplateAsErr;
        break;
    }

    while(*seeker != '\0')
        complexMsg[i++] = *seeker++;

    //
    // If some additional info is passed
    //
    if(gpio->Description != 0)
    {
        complexMsg[i++] = ' ';
        seeker = gpio->Description;

        while(*seeker != '\0')
            complexMsg[i++] = *seeker++;
    }

    complexMsg[i++] = '\n';
    complexMsg[i++] = '\r';
    complexMsg[i++] = '\0';

    //
    // GPIO Mode should be always reported in sync mode
    //
    HAL_Console_TxSync(complexMsg);
}
