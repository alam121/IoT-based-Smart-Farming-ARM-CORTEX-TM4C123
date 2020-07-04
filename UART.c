#include <stdint.h>
#include <TM4C123GH6PM.H>





void PLL_Init(void);//for smooth delay
void UART3_Init(void);//UART0 Initialization


void UartWrite(char *pstr);//to write a string with parameters of character array
unsigned char Receiver(void); //UART reciever
void Transmitter(unsigned char data);// UART Transmitter



void AT_Function (int x){
 
		PLL_Init();                                     
    UART3_Init();     

		UartWrite(" AT+RST\r\n\r\n");  
		
		UartWrite("AT+CWMODE=1\r\n\r\n");

    

UartWrite("AT+CIPSTART=TCP,184.106.153.149,80\r\n\r\n");

UartWrite("AT+CIPSEND=55\r\n\r\n");

UartWrite("GET /update?key=55FP9HPZOU22ZM2V&Tempreture=x\r\n\r\n");
   
				
}



void UART3_Init(void)
{
    SYSCTL->RCGCUART |= 0x08; //UART3=0000  1000 
    SYSCTL->RCGCGPIO |= 0x04; //PORTC CLOCK ENABLE  //0000  0100
    UART3->CTL &= ~0x02; //UART0 DISABLE
    UART3->IBRD = 43; //BAUD INTEGER
    UART3->FBRD = 26; //BAUD FLOATING
    UART3->LCRH = 0x00000070;  //ENABLE FEN & WLEN
    UART3->CTL |= 0x02; //UART ENABLE;

    GPIOC->AFSEL |= 0xC0; // OTHER ALTERNATIVE FUNCTION AT PORTC 6-7  1100 0000
    GPIOC->DEN |= 0xC0; // PORTB 6-7 OUTPUT
    GPIOC->PCTL = (GPIOC->PCTL&0x00FFFFFF)+0x11000000; //GPIO PORTC 6-7
    GPIOC->AMSEL &= ~0xC0; //ANALOG DISABLE
}


void PLL_Init(void)
{    
  SYSCTL->RCC2 |=  0x80000000;  
  SYSCTL->RCC2 |=  0x00000800;  
  SYSCTL->RCC = (SYSCTL->RCC &~0x000007C0) + 0x00000540;   
  SYSCTL->RCC2 &= ~0x00000070;  
  SYSCTL->RCC2 &= ~0x00002000;  
  SYSCTL->RCC2 |= 0x40000000; 
  SYSCTL->RCC2 = (SYSCTL->RCC2&~ 0x1FC00000) + (4<<22);   
  while((SYSCTL->RIS&0x00000040)==0){};   
  SYSCTL->RCC2 &= ~0x00000800;
}	




void UartWrite(char *pstr){
    while(*pstr != 0)    {
        Transmitter(*pstr++);        
    }
}
unsigned char Receiver(void){
    while((UART3->FR&0x10) != 0){};
    return UART3->DR&0xFF;
}
void Transmitter(unsigned char data){
    while((UART3->FR&0x20) != 0){};
    UART3->DR = data;
}



   
