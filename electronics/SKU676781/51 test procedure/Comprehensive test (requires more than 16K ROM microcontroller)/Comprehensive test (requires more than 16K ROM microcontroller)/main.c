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
void xianshi()//��ʾ��Ϣ
{   
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	showhanzi(10,0,0);  //��
	showhanzi(45,0,1);  //ҫ
    LCD_ShowString(10,30,"2.2 inch TFT 240*320");
}
void showimage() //��ʾ40*40ͼƬ
{
  	int i,j,k;
	xianshi(); //��ʾ��Ϣ
	for(k=2;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<1600;i++)
			 {				
			  	 LCD_WR_DATA8(image[i*2+1]);	 //������ɫ����
				 LCD_WR_DATA8(image[i*2]);					
			 }	
		 }
	}
		
}
main()
{ 
	Lcd_Init();   //tft��ʼ��
	LCD_Clear(WHITE); //����
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 
    showimage(); //��ʾ40*40ͼƬ

	while(1)
	{
	 
//	Lcd_Init();   //tft��ʼ��
//	LCD_Clear(WHITE); //����
//	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 
 //  showimage(); //��ʾ40*40ͼƬ
//	delayms(2000);
    }


}
