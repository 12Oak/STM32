/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_GeneralTim.h" 


/* Global Variable ------------------------------------------------------------*/
extern Time_FlagTypeDef TIME_Flag_Struct;   //定时标志结构体

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
    USART_SendData(DEBUG_USARTx,ucTemp);    
	}	 
}

volatile Time_FlagTypeDef TimerStruct;  
/**
  * @brief  产生1ms、10ms、20ms、100ms、500ms、1s标志，保存在TIME_Flag_Struct结构体中
  * @param  None
  * @retval None
  */
void  GENERAL_TIM_IRQHandler (void)
{
	//1ms进一次中断
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		TimerStruct.Timer_1ms_flag++;
		TimerStruct.Timer_10ms_flag++;
		TimerStruct.Timer_20ms_flag++;
		TimerStruct.Timer_100ms_flag++;
		TimerStruct.Timer_150ms_flag++;
		TimerStruct.Timer_500ms_flag++;
		TimerStruct.Timer_1s_flag++;

		//1ms标志位
		if(TimerStruct.Timer_1ms_flag >= 1)
		{
			TimerStruct.Timer_1ms_flag = 0;
			TIME_Flag_Struct.Timer_1ms_flag = 1;
		}
		//10ms标志位
		if(TimerStruct.Timer_10ms_flag >= 10)
		{
			TimerStruct.Timer_10ms_flag = 0;
			TIME_Flag_Struct.Timer_10ms_flag = 1;
		}
		//20ms标志位
		if(TimerStruct.Timer_20ms_flag >= 20)
		{
			TimerStruct.Timer_20ms_flag = 0;
			TIME_Flag_Struct.Timer_20ms_flag = 1;
		}
		//100ms标志位
		if(TimerStruct.Timer_100ms_flag >= 100)
		{
			TimerStruct.Timer_100ms_flag = 0;
			TIME_Flag_Struct.Timer_100ms_flag = 1;
		}
		if(TimerStruct.Timer_150ms_flag >= 150)
		{
			TimerStruct.Timer_150ms_flag = 0;
			TIME_Flag_Struct.Timer_150ms_flag = 1;
		}
		//500ms标志位
		if(TimerStruct.Timer_500ms_flag >= 500)
		{
			TimerStruct.Timer_500ms_flag = 0;
			TIME_Flag_Struct.Timer_500ms_flag = 1;
		}
		//1s标志位		
		if(TimerStruct.Timer_1s_flag >= 1000)
		{
			TimerStruct.Timer_1s_flag = 0;
			TIME_Flag_Struct.Timer_1s_flag = 1;
		}		
		//清除标志位
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update);  		 
	}		 	
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
