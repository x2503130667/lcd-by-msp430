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
	//���ò�����

	P1DIR |= BIT0+BIT1+BIT2;    //���ƶ˿�
	P2DIR |= 0xff;              //���ݶ˿�
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
    zt(0x38);   //����8λ���ݽӿ�(D7��D0)��������ʾ��5��8�����ַ���
    zt(0x0f);   //������ʾ������ʾ��꣬�����˸��
    zt(0x01);   //����
    zt(0x06);   //д�������ݺ�������,��ʾ���ƶ�
    zt(0x80);


}







void zt(unsigned char com)
{
    P1OUT &= ~(BIT2+BIT0);  //����
    __delay_cycles(5);  //��ʱ
    P1OUT &= ~BIT1;  //д
    __delay_cycles(5);
    P2OUT = com;//�˿ڸ�ֵ
    __delay_cycles(5);
    P1OUT |= BIT2;  //������
    __delay_cycles(5);
    P1OUT &= ~BIT2;
    __delay_cycles(500);
}


void sr(unsigned char data)
{
    P1OUT &= ~BIT2;
    P1OUT |= BIT0;  //����
    P1OUT &= ~BIT1;  //д
    __delay_cycles(5);
    P2OUT = data;//�˿ڸ�ֵ
    __delay_cycles(5);
    P1OUT |= BIT2; //������
    __delay_cycles(5);
    P1OUT &= ~BIT2;
    __delay_cycles(500);
}


