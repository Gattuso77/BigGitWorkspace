//******************************************************************************
//   HW: MSP-EXP430F5529LP
//   FW: BigGitTest
//******************************************************************************

#include "GlobalInclude.h"
#include "GPIO_Manager.h"
#include "SW\Console\Console_Interface.h"


//*****************************************************************************
//
// Included functions
//
//*****************************************************************************
void Initialize_CriticalPeripherals();

#define TOTAL_PIN_COUNT 80
const GPIO_SPD * GPIO_MAPPER[TOTAL_PIN_COUNT];

//
// External variables from modules that define GPIO usage
//
#define MODULE_COUNT    2
extern GPIO_GRS USCI1_HWModule;
extern GPIO_GRS OnBoardLED_HWModule;



GPIO_GRS * HW_Modules[MODULE_COUNT] = { &USCI1_HWModule, &OnBoardLED_HWModule };



//*****************************************************************************
//
// The MSP430F..5..6 families have PORT mapping feature, that allows a specific port pins to be configured to many different functions
// this should be done in this function and it should be called before GPIO initialisation
//
//*****************************************************************************
void PortMap()
{

}


//*****************************************************************************
//
// Function that checks, if there are GPIO conflicts
//
//*****************************************************************************
bool NoPinConflict()
{
    // TODO
    return true;
}


//*****************************************************************************
//
// Function that checks, is used to initialize a single GPIO
//
//*****************************************************************************
void InitializeSingleGpio(const GPIO_SPD * gpio)
{
    //
    // Checking if either of the options (pull-up/down/etc.) are enabled
    //
    if(gpio->Options != 0)
    {
        if(gpio->Options & GPIO_OPTION_PULL_UP)
            GPIO_setAsInputPinWithPullUpResistor(gpio->SelectedPort, gpio->SelectedPin);
        if(gpio->Options & GPIO_OPTION_PULL_DOWN)
            GPIO_setAsInputPinWithPullDownResistor(gpio->SelectedPort, gpio->SelectedPin);
    }

    switch(gpio->PinType)
    {
    case GPIO_MODE_INPUT:
        GPIO_setAsInputPin(gpio->SelectedPort, gpio->SelectedPin);
        break;
    case GPIO_MODE_OUTPUT:
        GPIO_setAsOutputPin(gpio->SelectedPort, gpio->SelectedPin);
        GPIO_setOutputLowOnPin(gpio->SelectedPort, gpio->SelectedPin);
        break;
    case GPIO_MODE_PERIPHERAL:
        GPIO_setAsPeripheralModuleFunctionInputPin(gpio->SelectedPort, gpio->SelectedPin);
        break;
    default:
        while(1) {};    // TODO: fatal error
    }
}


//*****************************************************************************
//
// Function that performs any action when the pin has been already configured
//
//*****************************************************************************
void PostProcessPin(const GPIO_SPD * gpio)
{
#if MODULE_CONSOLE_LOGGER
    Console.ReportGPIOInit(gpio);
#endif
}


//*****************************************************************************
//
// First:   do all MCU-specific tasks
// Second:  perform GPIO pre-initialisation, i.e. harvest information from modules and initialise only those, that have critical priority
// Third:   check that there are no conflict requirements within all modules and perform all other modules GPIO initialisation
//
//*****************************************************************************
void Initialize_GPIOs()
{
    uint8_t i, j;
    uint8_t gpioCnt = 0;

    // Run all platform specific pre-initialization
    PortMap();


    //
    // Get all GPIOs (harvest info from all modules)
    //
    for(i = 0; i < MODULE_COUNT; i++)
    {
        for(j = 0; j < HW_Modules[i]->Count; j++)
            GPIO_MAPPER[gpioCnt++] = &HW_Modules[i]->GPIOs[j];

        if(HW_Modules[i]->Priority == GPIO_PRIORITY_CRITICAL)
        {
            for(j = 0; j < HW_Modules[i]->Count; j++)
                InitializeSingleGpio(&HW_Modules[i]->GPIOs[j]);
        }
    }

    //
    // Initializing critical peripherals, such as console
    //
    Initialize_CriticalPeripherals();
#if MODULE_CONSOLE_LOGGER
    Console.Log("Console Logger has been initialized\n\r", CONSOLE_MODE_SYNC);
    PostProcessPin(&USCI1_HWModule.GPIOs[0]);
    PostProcessPin(&USCI1_HWModule.GPIOs[1]);
#endif


    //
    // Check that there is no PIN conflict, if that's true: initialise all GPIO's and continue to run program normally
    // If not, any about the collision with either of possible methods
    //
    if(NoPinConflict() == true)
    {
        for(i = 0; i < MODULE_COUNT; i++)
        {
            if(HW_Modules[i]->Priority != GPIO_PRIORITY_CRITICAL)
            {
                for(j = 0; j < HW_Modules[i]->Count; j++)
                {
                    InitializeSingleGpio(&HW_Modules[i]->GPIOs[j]);
                    PostProcessPin(&HW_Modules[i]->GPIOs[j]);
                }
            }
        }
    }
    else
    {
        while(1)
        {
#if MODULE_CONSOLE_LOGGER
            Console.Log("There is a pin conflict! Can not start the program!\n\r", CONSOLE_MODE_SYNC);
            // TODO: add which pins are conflicting
            __delay_cycles(1000000);
#endif
        }
    }
}
