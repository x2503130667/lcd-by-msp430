#include <msp430g2553.h>


/**
 * main.c
 */
void replay(void);

void busy(void);

void zt(unsigned char com);

void sr(unsigned char data);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//设置参数；

	P1DIR |= BIT0+BIT1+BIT2;    //控制端口
	P2DIR |= 0xff;              //数据端口
	P1SEL &= ~(BIT0+BIT1+BIT2+BIT4);
	P1SEL2 &= ~(BIT0+BIT1+BIT2+BIT4);
	P2SEL &= ~(BIT6+BIT7);
	P2SEL2 &= ~(BIT6+BIT7);
	P1OUT &= ~0xff;
	P2OUT &= ~0xff;
	replay();
	int i=0;
	unsigned char first[]={"no matter"};
	unsigned char first[]={"warning!"};
	for(;i<10;i++) sr(first[i]);



	while(1);
}




void replay(void)
{
    zt(0x38);   //设置8位数据接口(D7—D0)，两行显示，5×8点阵字符。
    zt(0x0f);   //设置显示开，显示光标，光标闪烁。
    zt(0x01);   //清屏
    zt(0x06);   //写入新数据后光标右移,显示不移动
    zt(0x80);


}







void zt(unsigned char com)
{
    P1OUT &= ~(BIT2+BIT0);  //命令
    __delay_cycles(5);  //延时
    P1OUT &= ~BIT1;  //写
    __delay_cycles(5);
    P2OUT = com;//端口赋值
    __delay_cycles(5);
    P1OUT |= BIT2;  //高脉冲
    __delay_cycles(5);
    P1OUT &= ~BIT2;
    __delay_cycles(500);
}


void sr(unsigned char data)
{
    P1OUT &= ~BIT2;
    P1OUT |= BIT0;  //数据
    P1OUT &= ~BIT1;  //写
    __delay_cycles(5);
    P2OUT = data;//端口赋值
    __delay_cycles(5);
    P1OUT |= BIT2; //高脉冲
    __delay_cycles(5);
    P1OUT &= ~BIT2;
    __delay_cycles(500);
}


