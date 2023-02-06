/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_GeneralTim.h" 

/* Defines -------------------------------------------------------------------- */
#define Time_share_System  0  /* ʱ��Ƭ */


/* Global Variable ------------------------------------------------------------ */
volatile Time_FlagTypeDef TIME_Flag_Struct;        /* ��ʱ��־�ṹ�� */

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  USART_Config();       /* ����1��ʼ�� 115200 */
	GENERAL_TIM_Init();   /* ��ʱ��2 */
  while(1)
	{		
		
		
		
#if Time_share_System		
		
		if(TIME_Flag_Struct.Timer_1ms_flag == 1)     //1ms����
		{
			TIME_Flag_Struct.Timer_1ms_flag = 0;		
		}	
		if(TIME_Flag_Struct.Timer_10ms_flag == 1)    //10ms����
		{
			TIME_Flag_Struct.Timer_10ms_flag = 0;			
		}	
		if(TIME_Flag_Struct.Timer_20ms_flag == 1)    //20ms����
		{
			TIME_Flag_Struct.Timer_20ms_flag = 0;				
		}
		if(TIME_Flag_Struct.Timer_100ms_flag == 1)   //100ms����
		{
			TIME_Flag_Struct.Timer_100ms_flag = 0;						
		}	
		if(TIME_Flag_Struct.Timer_150ms_flag == 1)   //150ms����
		{
			TIME_Flag_Struct.Timer_150ms_flag = 0;
		}
		
		if(TIME_Flag_Struct.Timer_500ms_flag == 1)   //500ms����
		{
			TIME_Flag_Struct.Timer_500ms_flag = 0;	
		}
		
		if(TIME_Flag_Struct.Timer_1s_flag == 1)      //1s����
		{
			TIME_Flag_Struct.Timer_1s_flag = 0;
		}		
		
#endif		/* Time_share_System	*/
		
		
		
	}	
}
/*********************************************END OF FILE**********************/
