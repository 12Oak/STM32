/**
  ******************************************************************************
  * @file    bsp_GeneralTim.c
  * @author  �Ƽ�
  * @version V1.0
  * @date    2022-08-02
  * @brief   ��ɶ�ʱ��2�ĳ�ʼ����ÿ1ms����һ���жϣ��жϺ�����stm32f10x_it.c�ļ���
  *          �ж���Ϊ��2���ж����ȼ�Ϊ2,1
  *          ���delay_ms������ʱ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��STM32C8T6���İ�
  *
  ******************************************************************************
  */ 
#include "bsp_GeneralTim.h" 

// �ж����ȼ�����
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
static void GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;
	  // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
		// ʱ�ӷ�Ƶ���� ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
		// ����������жϱ�־λ
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();
}


//��ԭ����ʱ��������systic�ж�
void delay_us(u32 nus)
{
 /* ����һ��Ҫ��32λ */
 u32 temp;  
 /* CTRL_bit2��λֵΪ0��ʱ��ΪAHB/8����Ϊ9Mʱ�ӣ���bit��Ϊ1��ʱ��ΪAHBʱ�� */ 
 SysTick->LOAD = 9*nus; 
 //��ռ�����
 SysTick->VAL=0X00;
 //bit0 = 1ʹ�ܣ����������޶�����bit1δ��Ϊ1��δ�����жϣ������ⲿʱ��Դ
 SysTick->CTRL=0X01;
 do
 {
	//��ȡ��ǰCTRL�Ĵ���ֵ������16λΪ��������־λ��
  temp=SysTick->CTRL;
 }
 //�ȴ�ʱ�䵽�λ16Ϊ0����ʱ��,��bit0 Ϊ1������systick��
 while((temp&0x01)&&(!(temp&(1<<16))));
		//�رռ�����
    SysTick->CTRL=0x00; 
		//��ռ�����
    SysTick->VAL =0X00; 
}
void delay_ms(u16 nms)
{
 u32 temp;
 SysTick->LOAD = 9000*nms;
 SysTick->VAL=0X00;//��ռ�����
 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
 do
 {
  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
    SysTick->CTRL=0x00; //�رռ�����
    SysTick->VAL =0X00; //��ռ�����
}

/*********************************************END OF FILE**********************/
