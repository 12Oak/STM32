/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_GeneralTim.h" 

/* Defines -------------------------------------------------------------------- */
#define Time_share_System  0  /* 时间片 */


/* Global Variable ------------------------------------------------------------ */
volatile Time_FlagTypeDef TIME_Flag_Struct;        /* 定时标志结构体 */

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  USART_Config();       /* 串口1初始化 115200 */
	GENERAL_TIM_Init();   /* 定时器2 */
  while(1)
	{		
		
		
		
#if Time_share_System		
		
		if(TIME_Flag_Struct.Timer_1ms_flag == 1)     //1ms任务
		{
			TIME_Flag_Struct.Timer_1ms_flag = 0;		
		}	
		if(TIME_Flag_Struct.Timer_10ms_flag == 1)    //10ms任务
		{
			TIME_Flag_Struct.Timer_10ms_flag = 0;			
		}	
		if(TIME_Flag_Struct.Timer_20ms_flag == 1)    //20ms任务
		{
			TIME_Flag_Struct.Timer_20ms_flag = 0;				
		}
		if(TIME_Flag_Struct.Timer_100ms_flag == 1)   //100ms任务
		{
			TIME_Flag_Struct.Timer_100ms_flag = 0;						
		}	
		if(TIME_Flag_Struct.Timer_150ms_flag == 1)   //150ms任务
		{
			TIME_Flag_Struct.Timer_150ms_flag = 0;
		}
		
		if(TIME_Flag_Struct.Timer_500ms_flag == 1)   //500ms任务
		{
			TIME_Flag_Struct.Timer_500ms_flag = 0;	
		}
		
		if(TIME_Flag_Struct.Timer_1s_flag == 1)      //1s任务
		{
			TIME_Flag_Struct.Timer_1s_flag = 0;
		}		
		
#endif		/* Time_share_System	*/
		
		
		
	}	
}
/*********************************************END OF FILE**********************/
