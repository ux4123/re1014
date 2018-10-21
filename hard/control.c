#include "control.h"
#include "dianji.h"

float pitch=0,roll=0,yaw=0,acroll=0;
//float kp=0.5,kd=0,ki=0;
//float temp1=0,temp2=0;
//u8 fanxiang=0;
int jifenxianfu=1000;
int pwmaddA=0,pwmaddB=0;
u8 kongzhi;



struct PIDstruct
{
		float kp;
		float ki;
		float kd;
		float angle;
		float lastError;
		float sumError;
		float setPoint;
};
//angle = 0.7
struct PIDstruct xPID={0.1,0,0,0,0,0,0};

struct PIDstruct turnPID={1,0,0,0,0,0,80};


void set_pwm(int a)
{
	
	{
    if(a<0)
    {
        AIN1(1);AIN2(0);BIN1(0);BIN2(1);a=-a;	
    }
    else if(a>0)
    {
        AIN1(0);AIN2(1);BIN1(1);BIN2(0);
				
				
    }
		a=(a>880)?880:a;
    TIM_SetCompare1(TIM3,120+a);
  	TIM_SetCompare4(TIM3,120+a);
	}


}
/*
	qianhoujiaodu roll
	zuoyou pitch

*/
int32_t pid_cal(struct PIDstruct *p)
{
		float Error=p->setPoint-p->angle;
	    float dError=Error-p->lastError;
		p->lastError=Error;
		p->sumError+=Error;
		if(p->sumError> jifenxianfu)					//»ý·ÖÏÞ·ù2300
		p->sumError = jifenxianfu;
		else if(p->sumError < -jifenxianfu)
		p->sumError = -jifenxianfu;	

		return (int32_t)(p->kp*Error+\
						         p->ki*p->sumError+\
						         p->kd*dError);
}
/*

void EXTI3_IRQHandler(void)
{
//	int cpwm=0;
//	int temp=0;
		    xPID.setPoint=0;
        if(EXTI_GetFlagStatus(EXTI_Line3)!=RESET)
        {
            while((mpu_dmp_get_data(&pitch,&roll,&yaw))!=0) 
		    {
	//		u3_printf("error is \r\n");
	//		delay_ms(500);
		    }
		    xPID.angle=roll;
		    set_pwm(pid_cal(&xPID));
//			temp=roll*100;
//			u1_printf("pitch%d\r\n",pitch*100);
//			u1_printf("%d\r\n",temp);
//			u3_printf("kp%3.3f\r\n",kp);
//			u3_printf("ki%3.3f\r\n",ki);
			u3_printf("%3.3f\r\n",pitch*100);
////			u1_printf("yaw%d\r\n",yaw*100);
////		 u3_printf("sda\r\n");
////		MPU_Get_Gyroscope(gx,gy,gz);
//			temp1=temp1+roll;
//			cpwm=kp*(roll-2.7)+ki*(temp1)+kd*(roll-temp2);
//			set_pwm(cpwm);
//			temp2=roll;

            EXTI_ClearITPendingBit(EXTI_Line3);
        }
}

void USART1_IRQHandler(void)
{
//	static u8 stateRec=0;
	u8 recData;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//??????????
	{		
		recData=USART_ReceiveData(USART1);
//		USART_SendData(USART3,recData);
//		USART_SendData(USART3,USART_ReceiveData(USART1));
	#if 0
		switch(stateRec)
		{
			case 0:if(USART_ReceiveData(USART1)==0x01) stateRec=1;break;
			case 1:{if(USART_ReceiveData(USART1)==0x0a) stateRec=2;else stateRec=0;}break;
			case 2:{kp=USART_ReceiveData(USART1)-48;stateRec=3;}break;
//			case 1:{if(recData==0x0a) stateRec+=1;else stateRec=0;}break;
			
			case 3:if(USART_ReceiveData(USART1)==0x02) stateRec=4;else stateRec=0;break;
			case 4:{if(USART_ReceiveData(USART1)==0x0a) stateRec=5;else stateRec=0;}break;
			case 5:{ki=USART_ReceiveData(USART1)-48;stateRec=6;}break;
//			case 1:{if(recData==0x0a) stateRec+=1;else stateRec=0;}break;
			
			case 6:if(USART_ReceiveData(USART1)==0x03) stateRec=7;else stateRec=0;break;
			case 7:{if(USART_ReceiveData(USART1)==0x0a) stateRec=8;else stateRec=0;}break;
			case 8:{kd=USART_ReceiveData(USART1)-48;stateRec=0;}break;
			default:break;
		}
				#endif
					#if 0
		switch(stateRec)
		{
			case 0:if(recData==0x01) stateRec=1;break;
			case 1:{if(recData==0x0a) stateRec=2;else stateRec=0;}break;
			case 2:{kp=recData-48;stateRec=3;}break;
//			case 1:{if(recData==0x0a) stateRec+=1;else stateRec=0;}break;
			
			case 3:if(recData==0x02) stateRec=4;else stateRec=0;break;
			case 4:{if(recData==0x0a) stateRec=5;else stateRec=0;}break;
			case 5:{ki=recData-48;stateRec=6;}break;
//			case 1:{if(recData==0x0a) stateRec+=1;else stateRec=0;}break;
			
			case 6:if(recData==0x03) stateRec=7;else stateRec=0;break;
			case 7:{if(recData==0x0a) stateRec=8;else stateRec=0;}break;
			case 8:{kd=recData-48;stateRec=0;}break;
			default:break;
		}
				#endif
		#if 1
		switch((recData&0xc0)>>6)
		{
			case 1:xPID.kp=(recData&0x3f)/10.0;break;
			case 2:xPID.ki=(recData&0x3f)/10.0;break;
			case 3:xPID.kd=(recData&0x3f)/10.0;break;
			case 0:fanxiang=fanxiang^0x01;break;
			default:break;
		}
		
		#endif
	}

	USART_ClearITPendingBit(USART1,USART1_IRQn);
}
*/
void ahead()
{
	AIN1(1);AIN2(0);BIN1(0);BIN2(1);
	TIM_SetCompare1(TIM3,500);
	TIM_SetCompare4(TIM3,500);
	delay_ms(500);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare4(TIM3,0);

}

void back()
{
  AIN1(0);AIN2(1);BIN1(1);BIN2(0);
	TIM_SetCompare1(TIM3,500);
	TIM_SetCompare4(TIM3,500);
	delay_ms(500);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	
}

void right()
{
	AIN1(1);AIN2(0);BIN1(0);BIN2(1);
	TIM_SetCompare1(TIM3,500);
	TIM_SetCompare4(TIM3,0);
//	delay_ms(500);
//	TIM_SetCompare1(TIM3,0);
//	TIM_SetCompare4(TIM3,0);
}

void left()
{
	AIN1(1);AIN2(0);BIN1(0);BIN2(1);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare4(TIM3,500);
//	delay_ms(500);
//	TIM_SetCompare1(TIM3,0);
//	TIM_SetCompare4(TIM3,0);
}

void stop()
{
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void kong()
{
			switch(kongzhi)
		{
			case 0:ahead();break;
			case 1:back();break;
			case 2:right();break;
			case 3:left();break;
	    case 4:stop();break;
			default:break;
		}
}
		
void send_roll(USART_TypeDef* u1)
{
		int mroll=0;
		mroll=(int)(roll*100);
		if(mroll<0)
		{
			mroll=-mroll;
			USART_SendData(u1,0xff);
			USART_SendData(u1,0xff);
		}
		else
		{
			USART_SendData(u1,0xee);
			USART_SendData(u1,0xee);
		}
		USART_SendData(u1,mroll/256);
		
		USART_SendData(u1,mroll%256);	
}

//*****************************************************
int balance(float Angle,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle-15;       //===Çó³öÆ½ºâµÄ½Ç¶ÈÖÐÖµ ºÍ»úÐµÏà¹Ø
//	 if((Bias<1)&&(Bias>-1)) return 0; 
	 xPID.sumError+=Bias;
		 if((Bias>15)||(Bias<-15)) balance=xPID.kp*10*Bias+Gyro*xPID.kd+xPID.ki*xPID.sumError;
			else balance=xPID.kp*Bias+Gyro*xPID.kd+xPID.ki*xPID.sumError;
//	 if(Bias>15) balance=xPID.kp*10*Bias+Gyro*xPID.kd+xPID.ki*xPID.sumError;
//	 else	 balance=xPID.kp*Bias+Gyro*xPID.kd+xPID.ki*xPID.sumError;   //===¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊý kdÊÇDÏµÊý 
//	 if(balance<5) balance=0;
	 
	 return balance;
}


//*****************************************************

void set_pwmNow(int a,int b)
{
	
	{
    if(a<=0)
    {
        AIN1(1);AIN2(0);a=-a;	
    }
    else 
    {
        AIN1(0);AIN2(1);
				
				
    }
		if(b<=0)
		{
				BIN1(0);BIN2(1);b=-b;
		}
		else 
		{
				BIN1(1);BIN2(0);
		}
		a=(a>880)?880:a;
		b=(b>880)?880:b;
    TIM_SetCompare1(TIM3,120+a);
  	TIM_SetCompare4(TIM3,120+b);
	}


}

void EXTI3_IRQHandler(void)
{
		static int stateSend=0;
		int pwmout=0;
		int mroll=0;
		xPID.setPoint=0;
    if(EXTI_GetFlagStatus(EXTI_Line3)!=RESET)
    {
				if(mpu_dmp_get_data(&pitch,&roll,&yaw,&acroll)==0)
				{ 
						xPID.angle=roll;
						//set_pwm(pid_cal(&xPID));
						pwmout=-balance(roll,acroll);
						set_pwmNow(pwmout+pwmaddA,pwmout+pwmaddB);
						//set_pwm(-balance(roll,acroll));
						//right();
						switch(stateSend)
						{
							case 0:stateSend=1;break;
							case 1:stateSend=2;break;
							case 2:stateSend=3;break;
							case 3:{
												mroll=(int)(roll*100);
												if(mroll<0)
												{
														mroll=-mroll;
														USART_SendData(USART1,0xfe);
														while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
														USART_SendData(USART1,0xfe);
														while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
												}
												else
												{
														USART_SendData(USART1,0xff);
														while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
														USART_SendData(USART1,0xff);
														while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;														
												}
												USART_SendData(USART1,(mroll>>8)&(0xff));
												while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
												USART_SendData(USART1,mroll&(0xff));
												while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
												
											}
							default:stateSend=0;break;
						}
						//mroll=(int)(roll*100);
//						USART_SendData(USART1,0xff);
//						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
//						USART_SendData(USART1,0xee);
//						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
//						USART_SendData(USART1,(mroll>>8)&(0xff));
//						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
//						USART_SendData(USART1,mroll&(0xff));
//						while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
//			u1_printf("%3.3f\r\n",roll);
			//u1_printf("%d\n",mroll);
				}
            EXTI_ClearITPendingBit(EXTI_Line3);
     }
}





void USART1_IRQHandler(void)
{
	u8 recData;
//	static u8 recstate=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{		
		recData=USART_ReceiveData(USART1);
#if 0
		switch((recData&0xc0)>>6)
		{
			case 1:xPID.kp=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 2:xPID.ki=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 3:xPID.kd=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 0:fanxiang=fanxiang^0x01;break;
			default:break;
		}
#endif
		
#if 1
		switch((recData&0xc0)>>6)
		{
			case 1:xPID.kp=(recData&0x3f)/100.0;break;
			case 2:xPID.sumError=0;xPID.ki=(recData&0x3f)/100.0;break;
			case 3:xPID.kd=(recData&0x3f)/1000.0;break;
			case 0:
						if(recData==0x3f)
						{
								USART_Cmd(UART5,ENABLE);				
						}
						else if(recData==0x3d) 
						{
								USART_Cmd(UART5,DISABLE);
						}
						else if(recData<=0x10)
						{
									pwmaddA=-500;
									pwmaddB=0;
//								AIN1(1);AIN2(0);BIN1(1);BIN2(0);
//								TIM_SetCompare1(TIM3,800+(recData&0x3f));
//								TIM_SetCompare4(TIM3,800+(recData&0x3f));
//								AIN1(1);AIN2(0);BIN1(0);BIN2(1);
//								TIM_SetCompare1(TIM3,600);
//								TIM_SetCompare4(TIM3,600);
						}
						else if((recData>=0x21)&&(recData<=0x31))
						{
									pwmaddA=0;
									pwmaddB=-500;
//								AIN1(0);AIN2(1);BIN1(0);BIN2(1);
//								TIM_SetCompare1(TIM3,800+490-(recData&0x3f));
//								TIM_SetCompare4(TIM3,800+490-(recData&0x3f));	
//								AIN1(1);AIN2(0);BIN1(0);BIN2(1);
//								TIM_SetCompare1(TIM3,600);
//								TIM_SetCompare4(TIM3,600);
						}
						else if((recData<=0x20)&&(recData>=0x11))
						{
									pwmaddA=-200;
									pwmaddB=-200;
//								AIN1(1);AIN2(0);BIN1(0);BIN2(1);
//								TIM_SetCompare1(TIM3,600);
//								TIM_SetCompare4(TIM3,600);		
						}
						else if(recData==0x3e)
						{
									pwmaddA=0;
									pwmaddB=0;
						
						}
						break;
			default:break;
		}

#endif		
		
#if 0
		
switch(recData)
		{
			case 0:ahead();break;
			case 1:back();break;
			case 2:right();break;
			case 3:left();break;
	    case 4:stop();break;

			default:break;
		}		
		
		
	
		
#endif
	}
	USART_ClearITPendingBit(USART1,USART1_IRQn);
}

void turn_pwm(int a)
{
	
	{
    if(a>=0)
    {
        AIN1(1);AIN2(0);BIN1(0);BIN2(1);	
				a=(a>880)?880:a;
				TIM_SetCompare1(TIM3,0);
				TIM_SetCompare4(TIM3,120+a);
    }
    else if(a<0)
    {
        AIN1(0);AIN2(1);BIN1(1);BIN2(0);
				a=(a>880)?880:a;
				TIM_SetCompare1(TIM3,120+a);
				TIM_SetCompare4(TIM3,0);
    }

	}


}

void UART5_IRQHandler(void)
{
	u8 recData;
	
	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)
	{		
		recData=USART_ReceiveData(UART5);
		#if 0
		switch((recData&0xc0)>>6)
		{
			case 1:xPID.kp=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 2:xPID.ki=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 3:xPID.kd=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
			case 0:fanxiang=fanxiang^0x01;break;
			default:break;
		}
		#endif
		#if 1
//		USART_SendData(USART3,recData);
//		turnPID.angle=recData;
//		turn_pwm(pid_cal(&turnPID));
		switch(recData)
		{
			case 0x02:pwmaddA=-200;pwmaddB=0;break;
			case 0x03:pwmaddA=0;pwmaddB=-200;break;
			case 0x00:pwmaddA=-200;pwmaddB=-200;break;
			default:break;
		}
//		switch((recData&0xc0)>>6)
//		{
//			case 1:xPID.kp=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
//			case 2:xPID.ki=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
//			case 3:xPID.kd=(recData&0x3f)/10+0.1*((recData&0x3f)%10);break;
//			case 0:kongzhi=recData;kong();break;
//			default:break;
//		}
		#endif
	//	u1_printf("%3.3f\r\n",xPID.kp);
	}
	USART_ClearITPendingBit(UART5,UART5_IRQn);
}

