#include"Header.h"

unsigned char Light = 0;	
// ADC 0 interrupt service routine for sequencer 3
void ADC0Seq3_Handler(void){
unsigned int adc_data = 0; 
  // Read the temperature raw value from ADC FIFO	
	adc_data = (ADC_SS3_FIFO_DATA_R & 0xFFF);
	
	// Convert the raw value to Celsius scale
	Light = (unsigned char) (((adc_data *0.52)/4096) * 1220.41);
  // Clear the interrupt from ADC0 sequencer 3	
	ADC_INT_STATUS_CLR_R |= 0x08;	
	//DisableInterrupts();
}

// Intialization routine for setting up the required ports
void ADC_Init(void)
{		
  // GPIO configuration for ADC 0 analog input 1
	// as a temperature sensor is connected to GPIO pin PE2
	RCGC_GPIO_R |=  CLOCK_GPIOE;
	
  GPIO_PORTE_DEN_R &= ~(0x04);
	GPIO_PORTE_AMSEL_R |= 0x04;

	// Enable the clock for ADC0
  SYSCTL_RCGC_ADC_R |= ADC0_CLOCK_ENABLE;
	Delay(3);
	
	ADC_PERI_CONFIG_R |= 0x03;				// 250 Ksps 
	
	// Select AN1 (PE2) as the analog input 
	ADC_SS3_IN_MUX_R = 0x01;
	
	// 1st sample is end of sequence and source of interrupt
	ADC_SS3_CONTROL_R |= 0x06;		
	
	// 16x oversampling and then averaged
	ADC_SAMPLE_AVE_R |= 0x04;
	
	// Unmask ADC0 sequence 3 interrupt
	ADC_INT_MASK_R |= 0x08;
		// Enable ADC0 sequencer 3 interrupt in NVIC
	NVIC_EN0_R = NVIC_EN0_INT17;	
	
	// Configure ADC0 module for sequencer 3
	ADC_ACTIVE_SS_R = 0x00000008;	
	
}

void ADC_Start_Sampling(void)
{
	// Processor sample sequencer initiate for sequencer 3
	ADC_PROC_INIT_SS_R |= 0x08;	  
}
