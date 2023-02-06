/**
  ******************************************************************************
  * @file    bsp_GeneralTim.c
  * @author  黄佳
  * @version V1.0
  * @date    2022-08-02
  * @brief   完成定时器2的初始化，每1ms产生一次中断，中断函数在stm32f10x_it.c文件中
  *          中断组为组2，中断优先级为2,1
  *          完成delay_ms基本延时
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火STM32C8T6核心板
  *
  ******************************************************************************
  */ 
#include "bsp_GeneralTim.h" 

// 中断优先级配置
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
static void GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;
	  // 时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
		// 时钟分频因子 ，没用到不用管
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
		// 清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();
}


//仿原子延时，不进入systic中断
void delay_us(u32 nus)
{
 /* 这里一定要是32位 */
 u32 temp;  
 /* CTRL_bit2复位值为0，时钟为AHB/8，故为9M时钟；若bit设为1，时钟为AHB时钟 */ 
 SysTick->LOAD = 9*nus; 
 //清空计数器
 SysTick->VAL=0X00;
 //bit0 = 1使能，减到零是无动作，bit1未置为1故未开启中断，采用外部时钟源
 SysTick->CTRL=0X01;
 do
 {
	//读取当前CTRL寄存器值，（第16位为计数器标志位）
  temp=SysTick->CTRL;
 }
 //等待时间到达，位16为0，计时到,且bit0 为1（开启systick）
 while((temp&0x01)&&(!(temp&(1<<16))));
		//关闭计数器
    SysTick->CTRL=0x00; 
		//清空计数器
    SysTick->VAL =0X00; 
}
void delay_ms(u16 nms)
{
 u32 temp;
 SysTick->LOAD = 9000*nms;
 SysTick->VAL=0X00;//清空计数器
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 do
 {
  temp=SysTick->CTRL;//读取当前倒计数值
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
    SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}

/*********************************************END OF FILE**********************/
