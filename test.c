
//////////////////////树莓派///////////////////////////////
///////波特率115200/////////////////////////////////

#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
int x=50;
int main(){
	int fd;
	if(wiringPiSetup()<0)
		return 1;
	if((fd=serialOpen("/dev/ttyAMA0",115200))<0)
		return 1;
	printf("serial test start ...\n");
	while(1){
	//serialPrintf(fd,"0xaa");
	//serialPrintf(fd,"0x55");
	serialPutchar(fd,0xaa);
	serialPutchar(fd,0x55);
	serialPutchar(fd,x);
	//serialPrintf(fd,"hello world!!\n");
	//serialClose(fd);
	return 0;
}
serialClose(fd);
}
/////////////////////stm32/////////////////////////////////////
////////stm32用的是串口3，根据你们的板子确定用哪一个串口，串口接收数据都放在串口中断中，直接一直就行了
u8 Tx5Buffer[256];
u8 Tx5Counter = 0;
u8 count5 = 0;
u8 MV_TRACK=0;
u8 USART_RXBUF[10];
void USART3_IRQHandler(void)
{ static u8 step=0;
	    static u8 buf[6];
	u8 Res;
	   u8 i;
		if(USART_GetITStatus(USART3, USART_IT_RXNE)!= RESET)//?????
    {
        USART_ClearITPendingBit ( USART3, USART_IT_RXNE ); 
        Res= USART_ReceiveData(USART3);
 switch(step)
        {
            case 0:
                if(Res==0xaa)
                {
                    buf[0]=Res;
                    step=1;
                }
                else
                {
                    step=0;
                }
                break;
            case 1:
                if(Res==0x55)
                {
                    buf[1]=Res;
                    step=2;
                }
                else
                {
                    step=0;
                }
                break;
            case 2:
                buf[2]=Res;
						MV_TRACK=buf[2];
                step=0;
                break;

        }							 
  } 
		
    if ( USART_GetITStatus ( USART3, USART_IT_TXE ) )
    {

        USART3->DR = Tx5Buffer[Tx5Counter++];

        if ( Tx5Counter == count5 )
        {
            USART3->CR1 &= ~USART_CR1_TXEIE;
        }


        USART_ClearITPendingBit(USART3,USART_IT_TXE);
    }
					
		
	
}


