#include "timer.h"
#include "lcd.h"
extern u8 wei;
u8 qufan=0;
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//					POINT_COLOR=WHITE;
//					qufan=~qufan;
//					if(qufan=0)
//					{
//							POINT_COLOR=WHITE;
//							LCD_DrawRectangle(25, 105, 65,130);				  
//							LCD_DrawRectangle(25, 135, 65,160);
//							LCD_DrawRectangle(25, 165, 65,190);
//							LCD_DrawRectangle(25, 195, 65,220);
//							LCD_DrawRectangle(25, 225, 65,250);
//							LCD_DrawRectangle(25, 255, 65,280);
//					}
//					else
//					{
//								switch(wei)
//								{				 
//									case 0:
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 105, 65,130);
//										POINT_COLOR=WHITE;
//										LCD_DrawRectangle(25, 135, 65,160);
//										LCD_DrawRectangle(25, 165, 65,190);
//										LCD_DrawRectangle(25, 195, 65,220);
//										LCD_DrawRectangle(25, 225, 65,250);
//										LCD_DrawRectangle(25, 255, 65,280);
//										break;
//									case 1:
//										LCD_DrawRectangle(25, 105, 65,130);
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 135, 65,160);
//										POINT_COLOR=WHITE;
//										LCD_DrawRectangle(25, 165, 65,190);
//										LCD_DrawRectangle(25, 195, 65,220);
//										LCD_DrawRectangle(25, 225, 65,250);
//										LCD_DrawRectangle(25, 255, 65,280);
//										break;
//									case 2:				
//										LCD_DrawRectangle(25, 105, 65,130);
//										LCD_DrawRectangle(25, 135, 65,160);
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 165, 65,190);
//										POINT_COLOR=WHITE;
//										LCD_DrawRectangle(25, 195, 65,220);
//										LCD_DrawRectangle(25, 225, 65,250);
//										LCD_DrawRectangle(25, 255, 65,280);
//										break;
//									case 3:				
//										LCD_DrawRectangle(25, 105, 65,130);
//										LCD_DrawRectangle(25, 135, 65,160);
//										LCD_DrawRectangle(25, 165, 65,190);
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 195, 65,220);
//										POINT_COLOR=WHITE;
//										LCD_DrawRectangle(25, 225, 65,250);
//										LCD_DrawRectangle(25, 255, 65,280);
//										break;
//									case 4:				
//										LCD_DrawRectangle(25, 105, 65,130);
//										LCD_DrawRectangle(25, 135, 65,160);
//										LCD_DrawRectangle(25, 165, 65,190);
//										LCD_DrawRectangle(25, 195, 65,220);
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 225, 65,250);
//										POINT_COLOR=WHITE;
//										LCD_DrawRectangle(25, 255, 65,280);
//										break;
//									case 5:				
//										LCD_DrawRectangle(25, 105, 65,130);
//										LCD_DrawRectangle(25, 135, 65,160);
//										LCD_DrawRectangle(25, 165, 65,190);
//										LCD_DrawRectangle(25, 195, 65,220);
//										LCD_DrawRectangle(25, 225, 65,250);
//										POINT_COLOR=RED;
//										LCD_DrawRectangle(25, 255, 65,280);
//										POINT_COLOR=WHITE;
//										break;
//									
//									default:break;	
//								}
//				}			
		}
}












