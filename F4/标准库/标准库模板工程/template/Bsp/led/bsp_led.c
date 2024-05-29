#include "bsp_led.h"

// 定义一个包含所有 GPIO 时钟的数组
static const uint32_t GPIO_CLOCKS[] = {
    RCC_AHB1Periph_GPIOA,
    RCC_AHB1Periph_GPIOB,
    RCC_AHB1Periph_GPIOC,
    RCC_AHB1Periph_GPIOD,
    RCC_AHB1Periph_GPIOE,
    RCC_AHB1Periph_GPIOF,
    RCC_AHB1Periph_GPIOG,
    RCC_AHB1Periph_GPIOH,
    RCC_AHB1Periph_GPIOI};

// 获取 GPIO 端口对应的索引
#define GPIO_INDEX(GPIOx) ((uint32_t)(GPIOx) - (uint32_t)GPIOA) / ((uint32_t)GPIOB - (uint32_t)GPIOA)

static void Gpio_Config(GPIO_TypeDef *GPIOx, uint16_t pin, GPIOMode_TypeDef mode, GPIOOType_TypeDef oType, GPIOSpeed_TypeDef speed, GPIOPuPd_TypeDef puPd)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(GPIO_CLOCKS[GPIO_INDEX(GPIOx)], ENABLE);
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_OType = oType;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_InitStructure.GPIO_PuPd = puPd;

    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/**
 * @brief 初始化BSP开关
 *
 * 该函数初始化了车内的各种开关和显示设备的GPIO引脚，配置它们为输出模式，并设置为高电平。
 * 包括LED运行指示灯、座位显示、声音信号、行李架控制等设备。
 *
 * @note 无参数
 * @note 无返回值
 */
void Bsp_Switch_Init(void)
{
    // LED run
    Gpio_Config(GPIOF, GPIO_Pin_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // Seat1_Display
    Gpio_Config(GPIOE, GPIO_Pin_2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // Seat2_Display
    Gpio_Config(GPIOB, GPIO_Pin_7, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // Sound_Signal
    Gpio_Config(GPIOB, GPIO_Pin_6, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // 行李架
    Gpio_Config(GPIOE, GPIO_Pin_3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // other
    Gpio_Config(GPIOE, GPIO_Pin_6, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // led1
    Gpio_Config(GPIOE, GPIO_Pin_5, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    // led2
    Gpio_Config(GPIOE, GPIO_Pin_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
}


// void pwm_config(void){
//     // led_pwm1
//     Gpio_Config(GPIOE, GPIO_Pin_5, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
//     GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
//     /* Time base configuration */
//     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
//     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 时钟分频系数: 180M/4 = 45M
//     TIM_TimeBaseStructure.TIM_Period = 1000 - 1;                // 分成1000份
//     TIM_TimeBaseStructure.TIM_Prescaler = 1800 - 1;             // 1KHz
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
//     TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

//     /*输出比较初始化*/
//     TIM_OCInitTypeDef TIM_OCInitStructure;  // 定义结构体变量
//     TIM_OCStructInit(&TIM_OCInitStructure); // 结构体初始化，若结构体没有完整赋值
//                                             // 则最好执行此函数，给结构体所有成员都赋一个默认值
//                                             // 避免结构体初值不确定的问题
//     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             // 输出比较模式，选择PWM模式1
//     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;      // 输出极性，选择为高，若选择极性为低，则输出高低电平取反
//     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
//     TIM_OCInitStructure.TIM_Pulse = 700;                          // 初始的CCR值
//     TIM_OC1Init(TIM9, &TIM_OCInitStructure);                      // 将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
//     TIM_ARRPreloadConfig(TIM9, ENABLE);
//     TIM_Cmd(TIM9, ENABLE);
// }
