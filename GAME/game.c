#include "game.h"
#include <stdlib.h> 
#include <time.h> 

//�����
int high,width;			//��ͼ�߶�
int bird_x,bird_y; 		//������
int bar_y;		//��������
int bar_xTop,bar_xDown;		//���忪����������
int score;				//�÷�
int bird_front_x;
int bird_front_y;
int bar_front_y;

void startup(void)			//��ʼ��
{
		LCD_Clear(BLACK);
    high=480-35;			//��ʼ���߽�
    width=799;

    bird_x=high/2; 		//��ʼ��������
    bird_y=width/2;

    bar_y=width;		//��������

    bar_xTop=high/2;			//���忪��
    bar_xDown=bar_xTop+100;

    score=0;				//�÷�
	//LCD_DrawLine(799,0,799,480-35);//�ұ߽�
	LCD_DrawLine(0,480-35,800,480-35);   //�±߽�
	LCD_ShowString(0,480-30,280,24,24,"SCORE:");  //��ʾ����
}

void show()				//չʾ
{			
		//LCD_ShowChar(bird_front_y,bird_front_x,' ',24,0);
		LCD_Fill(bird_y,0,bird_y+24,480-36,BLACK);
		POINT_COLOR=RED;
    LCD_ShowChar(bird_y,bird_x,'@',24,0);
		POINT_COLOR=BLUE;
		LCD_Fill(bar_front_y,0,bar_front_y,480-35,BLACK);
    LCD_DrawLine(bar_y,0,bar_y,bar_xTop);   //�ϵ���
		LCD_DrawLine(bar_y,bar_xDown,bar_y,480-35);//�µ���
		LCD_ShowxNum(80,450,score,3,24,0);
}
 void updateWithInpute()			//��Ϊ�йص��������
{
	int t;
    tp_dev.scan(0);
		for(t=0;t<OTT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(bird_x>0&&bird_x<=high-24)
				{
					bird_front_x=bird_x;
					bird_front_y=bird_y;
					bird_x-=10;
				}
			}
		}   
}
int updateWithoutInput()		//��Ϊ�޹صĸ���
{
    if(bird_y==bar_y)
    {
        if((bird_x>bar_xTop)&&(bird_x<bar_xDown-24))		//??????????
            score++;
        else
        {
            return 1;
        }
    }

    if(bar_y>0)
		{
			bar_front_y=bar_y;
			bar_y-=10;
		}
    else
    {
        bar_y=width;
        bar_xTop=rand()%(high-100);
        bar_xDown=bar_xTop+100;
    }
    if(bird_x<high-24)
		{
		bird_front_x=bird_x;
		bird_x+=5;
		}
    else
    {
        return 1;
    }
    delay_ms(100);   
		return 0;		
}
int game(void)
{ 
	bird_front_x=bird_x;
	bird_front_y=bird_y;
	bar_front_y=bar_y;
	startup();
	while(1)
	{
		show();
		updateWithInpute();
		if(updateWithoutInput())
		{
			break;
		}
	}
	return 1;
}
