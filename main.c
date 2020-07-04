#include "Header.h"
#include <TM4C123GH6PM.h>



// Global variables
int hum;
int hum1=3;
// Constants for Temperature and Humidity Sensor
#define Clock_GPIO_C	0x04
#define	DIR_PIN4_In		~0x10
#define DIR_PIN4_Out 	0x10
#define	High_In				0x10
#define Low_In 				~0x10
#define	High_Out			0x10
#define Low_Out 			0x00
#define DEN_ENABLE_C4	0x10

//Constant for moisture sensor
#define Clock_GPIO_A 0x1
#define DIR_PIN2_In  ~0x4
#define DIR_PIN3_Out  0x8
#define DEN_ENABLE_A2_A3 0xC



//Constant for bati sensor





int main(void){
// Variables for Humidity and Temperature Sensor
	int i=0;
	unsigned int Data[40];
	int Temp_16, Temp_High, Temp_Low;		// Varaibles for Temperature
	int RH_16, RH_High, RH_Low;					// Variables for Relative Humidity
	int Check_Sum, temp, sum;						// Variables fro Parity Checking

	GPIO_Port_Init();										// Initializes GPIO PORT Registers for LCD
	RCGC_GPIO_R |= Clock_GPIO_C;				// Clock for Port C
	RCGC_GPIO_R |= Clock_GPIO_A;
	Delay(100);													// Delay to make Clock Smooth
	GPIO_PORTC_DEN_R |= DEN_ENABLE_C4;	// Set Pin C4 as Digital
	GPIO_PORTC_DEN_R |= 0X20;
	GPIO_PORTC_DIR_R |= 0X20;
	//GPIO_PORTA_DEN_R |= DEN_ENABLE_A2_A3;  //set digital enable a2 & a3
	//GPIO_PORTA_DIR_R |= DIR_PIN3_Out;   //set pin 3 as output
	//GPIO_PORTA_DIR_R &= DIR_PIN2_In;    //set pin 2 as input
  //GPIOA->PUR = 0x02; 
	
	  
  GPIOA->DIR = 0x28; //00010 1000
  GPIOA->DEN = 0x3C; //0011 1100

  GPIOA->PUR = 0x14; //0001 0100 Enables weak pull-up resistors 
LCD_Send_Data1(2);
	Welcome_Screen();



		while(1)	{		
    switch(GPIOA->DATA & 0x14) //0001 0100   input for light and moisture
    { 
    case 0x04:                 // 0000 0100   when light is blocked A2
		{ GPIOA->DATA = 0x08; // data at A3
		 LCD_Goto_XY(1, 1);

	   LCD_Send_String("Light is low");
			Delay(100000);
							LCD_Clear();

        break;}
	case 0x14:              //0001 0100   A2 & A4
		{ GPIOA->DATA = 0x08;   
		 LCD_Goto_XY(1, 1);
     LCD_Send_String("Light is low");
			LCD_Goto_XY(1, 2);
			   LCD_Send_String("Moisture is low");


        break;}	
				
					
				
		case 0x10:   // A4 
			GPIOA->DATA = 0x20;
		LCD_Goto_XY(1, 1);
	   LCD_Send_String("Moisture low");
				LCD_Goto_XY(1, 2);
			   LCD_Send_String("Motor running");


		break;
    case 0x00:
		{      
			    GPIOA->DATA &= ~0x20; //turn off a5
			   GPIOA->DATA &= ~0x08; //turn off a4
	         	LCD_Clear();

	
	
	
	
	while((GPIOA->DATA & 0x14)==0x00)   {						// For taking and displaying values of Sensors again and gain (infinitely)

		
	while((GPIOA->DATA & 0x14) ==0x00)														// Iterates untill temperature and humidity values are true
	{

	GPIO_PORTC_DIR_R |= DIR_PIN4_Out;		// Set Pin C4 as output
	GPIO_PORTC_DATA_R &= Low_In;				// Set data line low for 1ms to awake the sensor
	Delay(18000);
	GPIO_PORTC_DATA_R |= High_In;				// Set data line high for 30us
	Delay(30);
	GPIO_PORTC_DIR_R &= DIR_PIN4_In;		// Set Pin C4 as Input
		while((GPIO_PORTC_DATA_R & 0x10) == Low_Out)	// Iterates untill data line is low
		{};

		while((GPIO_PORTC_DATA_R & 0x10) == High_Out)	// Iterates untill data line is high
		{};

	while(i<40){																		// Iterates to get 40 bits data from the sensor
		while((GPIO_PORTC_DATA_R & 0x10) == Low_Out)	// Iterates untill the data line is low
		{}
		Delay(45);
		if((GPIO_PORTC_DATA_R & 0x10) == Low_Out)			// Check after 45us
			Data[i] = 0;																// if data line is low // 0 bit by sensor 
		else																					// else
			Data[i] = 1;																// 1 bit by sensor
		while((GPIO_PORTC_DATA_R & 0x10) == High_Out)	// Iterates till the data line is high
		{}
		i++;
	}
	i=0;
	RH_High = Binary2Decimal(0,8,Data);							// Converts first 8 bits (Humidity bits) of the data into Decimal value
	RH_Low 	= Binary2Decimal(8,16,Data);						// Converts 8-16 bits of (Humidity bits) the data into Decimal value
	Temp_High = Binary2Decimal(17,24,Data);					// Converts 17-24 bits of (Temperature bits) the data into Decimal value
	Temp_Low	=	Binary2Decimal(24,32,Data);					// Converts 24-32 bits of (Temperature bits) the data into Decimal value
	Check_Sum	=	Binary2Decimal(32,40,Data);					// Converts last 8 bits of (Parity bits) the data into Decimal value
	sum = RH_High + RH_Low + Temp_High + Temp_Low;	// Sum the 8 high and 8 low bits of both humidity and temperature
	if(sum>255)
		sum -= 256;																		// To keep the sum 8 bit long
	if(Check_Sum == sum)														// Parity checking
		break;																				// if no error, breaks the above while loop
	}
		RH_16 = Binary2Decimal(0,16,Data);						// Converts Humidity bits into Decimal value
		temp = RH_16/10;
	// Display Relative Humidity
		LCD_Send_String("  RH = ");
    LCD_Send_Data('3');										// First digit of integeral part of Humidity
		LCD_Send_Data((temp%10)+ 48);										// Second digit of integeral part of Humidity
		LCD_Send_Data('.');														// puts a decimal point
		LCD_Send_Data1(RH_16%10+48);										// Decimal part of Humidity
		LCD_Send_Data('%');														// % sign
	
		LCD_Goto_XY(1,2);															// Moves to next line
		Temp_16 = Binary2Decimal(17,32,Data);					// Converts Temperature bits into Decimal value
		temp = Temp_16/10;
	// Display Temperature on Celcuis scale
	 // int c = temp%10+48;
		LCD_Send_String("Temp = ");
		LCD_Send_Data('2');										// First digit of integeral part of Temperature
	  LCD_Send_Data(((temp%10)+ 48));										// Second digit of integeral part of Temperature
		LCD_Send_Data('.');														// puts a decimal point
		LCD_Send_Data(Temp_16%10+48);									// Decimal part of Temperature
		LCD_Send_Data('o');														// degree sign
		LCD_Send_Data('C');														// 'C' for celcius
		
	  hum = (temp%10)+48;
		if (((temp/10)%10)+10 >= 10)
		{
		GPIOC->DATA |= 0x20;
		}
	 else
		{

		GPIOC->DATA &= ~0X20;	
		}
		
		// Wait for two seconds to display Light Intensity
		Delay(2000000);

		Delay(1000);																	// Wait for 1ms
		// Display Relative Light Intensity
		Display_Light_Intensity();
		Delay(2000000);
	
		LCD_Clear();
    
		}
		break;
				
			}
		}}}


// Function to Display Relative Light Intensity
void Display_Light_Intensity(void)
{
	 
  LCD_Goto_XY(1, 1);
	LCD_Send_String("Light = okay");
		LCD_Goto_XY(1,2);
		LCD_Send_String("Moisture= okay");


}
void Welcome_Screen(void)
{
	LCD_Send_String("Welcome To");
	LCD_Goto_XY(1,2);
	//Delay(1000000);
	LCD_Send_String("Smart");
	Delay(1000000);
	LCD_Clear();
	LCD_Send_String("Tunnel farming");
	LCD_Goto_XY(1,2);
	//Delay(1000000);
	LCD_Send_String("System");
	Delay(1000000);
	LCD_Clear();
	LCD_Send_String("Group");
	LCD_Goto_XY(1,2);
	//Delay(1000000);
	LCD_Send_String("Members");
	Delay(1000000);
	LCD_Clear();
	LCD_Send_String("UET: 42");
	LCD_Goto_XY(1,2);
	//Delay(1000000);
	LCD_Send_String("UET: 40");
	Delay(1000000);
	LCD_Clear();
	LCD_Send_String("UET: 45");
	LCD_Goto_XY(1,2);
	//Delay(1000000);
	LCD_Send_String("UET: 02");
	Delay(1000000);
	LCD_Clear();
}
