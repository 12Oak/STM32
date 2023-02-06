#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"

/*****************************��ʱ��־�ṹ��*****************************/
typedef struct
{
	uint16_t Timer_1ms_flag;
	uint16_t Timer_10ms_flag;
	uint16_t Timer_20ms_flag;
	uint16_t Timer_100ms_flag;
	uint16_t Timer_150ms_flag;
	uint16_t Timer_500ms_flag;
	uint16_t Timer_1s_flag;
}Time_FlagTypeDef;

/*****************************��ʱ��־�ṹ��*****************************/


/**************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��4��5************/
/** 
  *@brief  ѡ��TIM2,4,5����֮һ��ͨ���궨�壩����TIM3
  *        TIM2,4,5�ṩ��Ҫʱ����1ms�жϣ�,TIM3�ṩ��ʱ����us����1us����һ�Σ�
  */
#define GENERAL_TIM2    1
#define GENERAL_TIM3    0
#define GENERAL_TIM4    0
#define GENERAL_TIM5    0

#if  GENERAL_TIM2
#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_Period            (1000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_IRQHandler        TIM2_IRQHandler

#elif GENERAL_TIM3
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            (2-1)
#define            GENERAL_TIM_Prescaler         (36-1)
#define            GENERAL_TIM_IRQ               TIM3_IRQn
#define            GENERAL_TIM_IRQHandler        TIM3_IRQHandler

#elif   GENERAL_TIM4
#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_Period            (1000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM4_IRQn
#define            GENERAL_TIM_IRQHandler        TIM4_IRQHandler

#elif   GENERAL_TIM5
#define            GENERAL_TIM                   TIM5
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM5
#define            GENERAL_TIM_Period            (1000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM5_IRQn
#define            GENERAL_TIM_IRQHandler        TIM5_IRQHandler

#endif
/**************************��������********************************/

void GENERAL_TIM_Init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif	/* __BSP_GENERALTIME_H */


