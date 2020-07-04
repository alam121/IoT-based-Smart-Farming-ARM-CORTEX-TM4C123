#define RCGC_GPIO_R        *((volatile unsigned long *)0x400FE608)

// register definitions for Port B, which is used as LCD data bus
#define GPIO_PORTB_DATA_R  *((volatile unsigned long *)0x400053FC) 
#define GPIO_PORTB_DIR_R   *((volatile unsigned long *)0x40005400)
#define GPIO_PORTB_DEN_R   *((volatile unsigned long *)0x4000551C)
#define GPIO_PORTB_AFSEL_R *((volatile unsigned long *)0x40005420)

// Port C registers for Humidity and Temperature Sensors
#define GPIO_PORTC_DATA_R  *((volatile unsigned long *)0x400060E0) 
#define GPIO_PORTC_DIR_R   *((volatile unsigned long *)0x40006400)
#define GPIO_PORTC_DEN_R   *((volatile unsigned long *)0x4000651C)

/* register definitions for Port E (pins 3, 4 and 5), which is 
used as LCD control bus */
#define GPIO_PORTE_DATA_R  *((volatile unsigned long *)0x400240E0) 
#define GPIO_PORTE_DIR_R   *((volatile unsigned long *)0x40024400)
#define GPIO_PORTE_DEN_R   *((volatile unsigned long *)0x4002451C)
#define GPIO_PORTE_AFSEL_R *((volatile unsigned long *)0x40024420)

//register definitions for Port A(pins 2,3,4,5) 

#define GPIO_PORTA_DATA_R  *((volatile unsigned long *)0x400043FC) 
#define GPIO_PORTA_DIR_R   *((volatile unsigned long *)0x40004400)
#define GPIO_PORTA_DEN_R   *((volatile unsigned long *)0x4000451C)
#define GPIO_PORTA_AFSEL_R *((volatile unsigned long *)0x40004420)




#define SYSCTL_RCGC_ADC_R  *((volatile unsigned long *)0x400FE638)
#define ADC0_CLOCK_ENABLE  0x00000001 // ADC0 Clock Gating Control
#define CLOCK_GPIOE        0x00000010   //Port E clock control


// GPIO Port E analog function configuration
#define GPIO_PORTE_AMSEL_R *((volatile unsigned long *)0x40024528)
#define GPIO_PORTE_DEN_R   *((volatile unsigned long *)0x4002451C)



// Functions prototypes for LCD
void LCD_Init(void);
void LCD_Clear(void);
void LCD_Send_Command(unsigned char command);
void LCD_Send_Data(unsigned char data);
void LCD_Send_Data1(unsigned int data);

void LCD_Goto_XY(unsigned char x, unsigned char y);
void LCD_Send_String( char *ptr);
void GPIO_Port_Init(void);

// Functions prototypes for Humidity and Temperature Sensors
void Binary2Hex(unsigned char Hex[], unsigned int Binary[]);
int Binary2Decimal(int Bit_L, int Bit_H, unsigned int Binary[]);
void Delay(unsigned long int period);
void Display_Light_Intensity(void);

void Welcome_Screen(void);

void light_sensor();

void moisture_sensor();


