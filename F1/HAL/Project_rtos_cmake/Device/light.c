#include "light.h"
#include "main.h"
#include "stm32f1xx_hal_gpio.h"

void hello(void) { HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); }