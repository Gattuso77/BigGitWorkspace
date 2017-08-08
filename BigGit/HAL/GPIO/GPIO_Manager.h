#ifndef HAL_GPIO_GPIO_MANAGER_H_
#define HAL_GPIO_GPIO_MANAGER_H_

//
// GPIO Generals Request Structure that should be used by modules to request PIN Initialization
//
enum GPIO_PRIORITY_LEVEL_EN {
    NOT_SET,
    GPIO_PRIORITY_HIGH,
    GPIO_PRIORITY_NORMAL,
    GPIO_PRIORITY_LOW,
    GPIO_PRIORITY_CRITICAL
};


enum GPIO_MODES_EN          {       GPIO_MODE_INPUT,
                                    GPIO_MODE_OUTPUT,
                                    GPIO_MODE_PERIPHERAL
};

enum GPIO_OPTIONS_EN          {     GPIO_OPTION_NONE        = 0x00,
                                    GPIO_OPTION_PULL_UP     = 0x01,
                                    GPIO_OPTION_PULL_DOWN   = 0x02
};

//
// GPIO Single Pin Descriptor that should be used by modules to request PIN initialization
//
typedef struct      {       const uint32_t    SelectedPort;
                            const uint32_t    SelectedPin;
                            const uint8_t     PinType;
                            const uint8_t     Options;
                            const char *      Description;
}GPIO_SPD;


//
// GPIO Generals Request Structure that should be used by modules to request PIN initialization
//
typedef struct      {       const GPIO_SPD *    GPIOs;
                            const uint8_t       Count;
                            uint8_t             Priority;
}GPIO_GRS;





#endif /* HAL_GPIO_GPIO_MANAGER_H_ */
