#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
/* 
����Ĭ��IO���ӷ�ʽ��
sbit LCD_CS     =P0^0;     //Ƭѡ	
sbit LCD_AO     =P0^2;	  //����/�����л�
sbit LCD_SDA    =P1^5;	  //����
sbit LCD_SCK    =P1^7;	  //ʱ��
sbit LCD_REST   =P0^1;	  //��λ  
*/
main()
{ 
	Lcd_Init();   //tft��ʼ��
	LCD_Clear(WHITE); //����
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 

	while(1)
	{		 
		 Lcd_Init();   //tft��ʼ��
		 LCD_Clear(RED);
		 delayms(3000);
		 LCD_Clear(GREEN);
		 delayms(3000);
		 LCD_Clear(BLUE);
		 delayms(3000);
    }


}
