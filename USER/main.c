#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "lcd.h"
#include "key.h"
#include "usart.h"
#include "timer.h"
u8 data[7];
u16  state=0; 
u8 wei=0;	
u16 pwmval1=749; 
u16 pwmval2=650; 
u16 pwmval3=600; 
u16 pwmval4=749; 
u8 key=0;	
struct
{
	unsigned int pwm1;
	unsigned int pwm2;
	unsigned int pwm3;
	unsigned int pwm4;
}one,two,three,four,five,six;

void Init()
{
	one.pwm1=849;
	one.pwm2=600;
	one.pwm3=360;
	one.pwm4=749;

	two.pwm1=749;
	two.pwm2=600;
	two.pwm3=360;
	two.pwm4=749;
		
	three.pwm1=649;
	three.pwm2=600;
	three.pwm3=360;
	three.pwm4=749;
	
	four.pwm1=849;
	four.pwm2=650;
	four.pwm3=600;
	four.pwm4=749;

	five.pwm1=749;
	five.pwm2=650;
	five.pwm3=600;
	five.pwm4=749;
	
	six.pwm1=649;
	six.pwm2=650;
	six.pwm3=600;
	six.pwm4=749;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	TIM3_Int_Init(9999,7199);//10Khz的计数频率，计数到5000为500ms  
	KEY_Init(); 
	delay_init();	    	 //延时函数初始化	 
  uart_init(115200);	 
	 
	LCD_Init();
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM2_PWM_Init(9999,143);//50hz 
	POINT_COLOR=RED;
	LCD_ShowString(30,40,200,24,24,"TWK STM32 ^_^"); 
	LCD_ShowString(30,290,200,24,24,"OK?"); 
//	LCD_DrawRectangle(25, 75, 85,105);
  LCD_DrawRectangle(25, 75, 65,100);
	LCD_DrawRectangle(25, 105, 65,130);
	
	LCD_ShowxNum(30,110,data[0],2,16,0x80);
	LCD_ShowxNum(30,140,data[1],2,16,0x80);
	LCD_ShowxNum(30,170,data[2],2,16,0x80);
	LCD_ShowxNum(30,200,data[3],2,16,0x80);
	LCD_ShowxNum(30,230,data[4],2,16,0x80);
	LCD_ShowxNum(30,260,data[5],2,16,0x80);
}	

void controlpwm()
{
	u8 count;
	for(count=0;count<=6;count++)
	{
					switch (data[count])
					{
						case 1:
							TIM_SetCompare1(TIM2,849);
							TIM_SetCompare2(TIM2,600);
							TIM_SetCompare3(TIM2,360);
							TIM_SetCompare4(TIM2,749);								
							break;
						
						case 2:
							TIM_SetCompare1(TIM2,749);
						  TIM_SetCompare2(TIM2,600);
						  TIM_SetCompare3(TIM2,360);
						  TIM_SetCompare4(TIM2,749);	
							break;
						
						case 3:
							TIM_SetCompare1(TIM2,649);
						  TIM_SetCompare2(TIM2,600);
						  TIM_SetCompare3(TIM2,360);
						  TIM_SetCompare4(TIM2,749);	
							break;
						
						case 4:
							TIM_SetCompare1(TIM2,849);
						  TIM_SetCompare2(TIM2,650);
						  TIM_SetCompare3(TIM2,600);
						  TIM_SetCompare4(TIM2,749);	
							break;
						
						case 5:
							TIM_SetCompare1(TIM2,749);
						  TIM_SetCompare2(TIM2,650);
						  TIM_SetCompare3(TIM2,600);
						  TIM_SetCompare4(TIM2,749);	
							break;
						
						case 6:
							TIM_SetCompare1(TIM2,649);
						  TIM_SetCompare2(TIM2,650);
						  TIM_SetCompare3(TIM2,600);
						  TIM_SetCompare4(TIM2,749);	
							break;
														
									
						default:delay_ms(500); break;	
					}
					delay_ms(700);delay_ms(700);
	}		
}
/* //0.5ms 249                   // 1ms 499 // 1.5ms 749 // 2ms 999                  // 2.5ms 1249  */

int main(void)
{	

  Init();//初始化
   	while(1)
		{
			key=KEY_Scan(0);
			if(key==KEY0_PRES){state+=1;if(state>6)state=0;}	
			POINT_COLOR=RED;
			LCD_ShowxNum(30,80,state,2,16,0x80);
			LCD_ShowxNum(90,80,wei,2,16,0x80);
			if(key==KEY1_PRES)
			{
				data[wei]=state;
				wei++;				
				if(wei>6)
				{
					controlpwm();
					for(wei=6;wei>0;wei--)
					{data[wei]=0;}
					 wei=0;
					 
//					TIM_SetCompare1(TIM2,pwmval1);
//					TIM_SetCompare2(TIM2,pwmval2);
//					TIM_SetCompare3(TIM2,pwmval4);
//					TIM_SetCompare4(TIM2,pwmval3);			
				}
				
				POINT_COLOR=RED;
				LCD_ShowxNum(30,110,data[0],2,16,0x80);
				LCD_ShowxNum(30,140,data[1],2,16,0x80);
				LCD_ShowxNum(30,170,data[2],2,16,0x80);
				LCD_ShowxNum(30,200,data[3],2,16,0x80);
				LCD_ShowxNum(30,230,data[4],2,16,0x80);
				LCD_ShowxNum(30,260,data[5],2,16,0x80);
				POINT_COLOR=WHITE;
						  
              LCD_DrawRectangle(25, 285, 65,310);
							switch(wei)
							{				 
									case 0:
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 105, 65,130);
										POINT_COLOR=WHITE;
										LCD_DrawRectangle(25, 135, 65,160);
										LCD_DrawRectangle(25, 165, 65,190);
										LCD_DrawRectangle(25, 195, 65,220);
										LCD_DrawRectangle(25, 225, 65,250);
										LCD_DrawRectangle(25, 255, 65,280);
										break;
									case 1:
										LCD_DrawRectangle(25, 105, 65,130);
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 135, 65,160);
										POINT_COLOR=WHITE;
										LCD_DrawRectangle(25, 165, 65,190);
										LCD_DrawRectangle(25, 195, 65,220);
										LCD_DrawRectangle(25, 225, 65,250);
										LCD_DrawRectangle(25, 255, 65,280);
										break;
									case 2:				
										LCD_DrawRectangle(25, 105, 65,130);
										LCD_DrawRectangle(25, 135, 65,160);
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 165, 65,190);
										POINT_COLOR=WHITE;
										LCD_DrawRectangle(25, 195, 65,220);
										LCD_DrawRectangle(25, 225, 65,250);
										LCD_DrawRectangle(25, 255, 65,280);
										break;
									case 3:				
										LCD_DrawRectangle(25, 105, 65,130);
										LCD_DrawRectangle(25, 135, 65,160);
										LCD_DrawRectangle(25, 165, 65,190);
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 195, 65,220);
										POINT_COLOR=WHITE;
										LCD_DrawRectangle(25, 225, 65,250);
										LCD_DrawRectangle(25, 255, 65,280);
										break;
									case 4:				
										LCD_DrawRectangle(25, 105, 65,130);
										LCD_DrawRectangle(25, 135, 65,160);
										LCD_DrawRectangle(25, 165, 65,190);
										LCD_DrawRectangle(25, 195, 65,220);
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 225, 65,250);
										POINT_COLOR=WHITE;
										LCD_DrawRectangle(25, 255, 65,280);
										break;
									case 5:				
										LCD_DrawRectangle(25, 105, 65,130);
										LCD_DrawRectangle(25, 135, 65,160);
										LCD_DrawRectangle(25, 165, 65,190);
										LCD_DrawRectangle(25, 195, 65,220);
										LCD_DrawRectangle(25, 225, 65,250);
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 255, 65,280);
										POINT_COLOR=WHITE;
										break;
									case 6:	
										LCD_DrawRectangle(25, 105, 65,130);
										LCD_DrawRectangle(25, 135, 65,160);
										LCD_DrawRectangle(25, 165, 65,190);
										LCD_DrawRectangle(25, 195, 65,220);
										LCD_DrawRectangle(25, 225, 65,250);
										LCD_DrawRectangle(25, 255, 65,280);										
										POINT_COLOR=RED;
										LCD_DrawRectangle(25, 285, 65,310);
										POINT_COLOR=WHITE;
										break;									
									default:break;	
								}
			}
		
		  			
		}

}




