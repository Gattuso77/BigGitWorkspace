#ifndef HAL_PERIPHERALS_PER_MANAGER_H_
#define HAL_PERIPHERALS_PER_MANAGER_H_


//
// Peripheral Priorities
//
enum GPIO_PRIORITY_LEVEL_EN {
    NOT_SET,
    PERIPHERAL_PRIORITY_HIGH,
    PERIPHERAL_PRIORITY_NORMAL,
    PERIPHERAL_PRIORITY_LOW,
    PERIPHERAL_PRIORITY_CRITICAL
};


//
//  Single Module Descriptor that should be used by modules to request their initialization
//
struct      {               bool IsInitialized;
                            void (* Initialize)();
}Periph_SMD;



#endif /* HAL_PERIPHERALS_PER_MANAGER_H_ */
