/**
 ************************************************************
 ************************************************************
 ************************************************************
 *	文件名： 	main.c
 *
 *	作者： 		张继瑞
 *
 *	日期： 		2017-05-08
 *
 *	版本： 		V1.0
 *
 *	说明： 		接入onenet，上传数据和命令控制
 *
 *	修改记录：
 ************************************************************
 ************************************************************
 ************************************************************
 **/

// 单片机头文件
#include "stm32f10x.h"

// 网络协议层
#include "onenet.h"

// 网络设备
#include "esp8266.h"

// 硬件驱动
#include "delay.h"
#include "usart.h"
#include "i2c.h"
#include "led.h"
#include "key.h"
#include "dht11.h"

// C库
#include <string.h>

#define ESP8266_ONENET_INFO "AT+CIPSTART=\"TCP\",\"183.230.40.96\",1883\r\n"

uint8_t temp;
uint8_t humi;

/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断控制器分组设置

    Delay_Init(); // systick初始化

    Usart1_Init(115200); // 串口1，打印信息用

    Usart2_Init(115200); // 串口2，驱动ESP8266用

    // IIC_Init(); // 软件IIC初始化

    Led_Init(); // LED初始化

    Key_Init();  // 按键初始化
    TIM2_Init(); // 定时器2初始化，每10ms扫描一次

    while (DHT11_Init()) {
        UsartPrintf(USART_DEBUG, "DHT11 Error \r\n");
        DelayMs(1000);
    }
    UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
}

/*
************************************************************
*	函数名称：	main
*
*	函数功能：
*
*	入口参数：	无
*
*	返回参数：	0
*
*	说明：
************************************************************
*/
int main(void)
{

    unsigned short timeCount = 0; // 发送间隔变量

    unsigned char *dataPtr = NULL;

    Hardware_Init(); // 初始化外围硬件

    ESP8266_Init(); // 初始化ESP8266

    // OneNET_RegisterDevice();

    // UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
    // while (ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
    //     DelayXms(500);

    // while (OneNet_DevLink()) // 接入OneNET
    //     DelayXms(500);

    Led_Set(LED_ON); // 鸣叫提示接入成功
    DelayMs(500);
    Led_Set(LED_OFF);

    while (1) {
        // DHT11_Read_Data(&temp, &humi); //
        // UsartPrintf(USART_DEBUG, "temp %d ,humi %d\r\n", temp, humi);

        // if (++timeCount >= 500) // 发送间隔5s
        // {
        //     // SHT20_GetValue();

        //     UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
        //     OneNet_SendData(); // 发送数据

        //     timeCount = 0;
        //     ESP8266_Clear();
        // }

        // dataPtr = ESP8266_GetIPD(0);
        // if (dataPtr != NULL)
        //     OneNet_RevPro(dataPtr);

        // DelayXms(10);
    }
}
