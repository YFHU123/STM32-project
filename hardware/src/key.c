#include "stm32f10x.h"
#include "key.h"
#include "led.h" // 用于调用 Led_Set

/*
 * 按键初始化，按键接在 PA1，配置为上拉输入
 */
void Key_Init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpio_initstruct.GPIO_Pin  = GPIO_Pin_1;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &gpio_initstruct);
}

/*
 * 定时器2初始化，每10ms触发一次中断
 * 系统时钟 72MHz，预分频设置为71后定时器时钟为1MHz，周期9999对应10ms
 */
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef tim_initstruct;
    NVIC_InitTypeDef nvic_initstruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    tim_initstruct.TIM_Period        = 10000 - 1;
    tim_initstruct.TIM_Prescaler     = 72 - 1;
    tim_initstruct.TIM_ClockDivision = 0;
    tim_initstruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &tim_initstruct);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    nvic_initstruct.NVIC_IRQChannel                   = TIM2_IRQn;
    nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_initstruct.NVIC_IRQChannelSubPriority        = 1;
    nvic_initstruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&nvic_initstruct);

    TIM_Cmd(TIM2, ENABLE);
}

/*
 * TIM2中断服务程序，用于扫描按键
 */
void TIM2_IRQHandler(void)
{
    static uint8_t debounce  = 0;
    static uint8_t key_state = 1; // 1：之前处于释放状态，0：之前处于按下状态

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        uint8_t current = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
        if (current == 0) // 按键按下（低电平）
        {
            if (debounce < 255)
                debounce++;
            // 持续低电平达到20次（约200ms），且之前为释放状态时触发
            if (debounce >= 5 && key_state == 1) {
                static _Bool led_status = LED_OFF;
                led_status              = !led_status;
                Led_Set(led_status);
                key_state = 0;
            }
        } else // 按键释放
        {
            debounce  = 0;
            key_state = 1;
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}