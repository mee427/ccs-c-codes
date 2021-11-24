#include <16F877A.h>
#device ADC=10
#FUSES NOWDT                     // No Watch Dog Timer
#FUSES NOBROWNOUT                // No brownout reset
#FUSES NOLVP                     // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)     // CONFIGURE According to your crystal frequency

// Configuration for Serial Communication
//#use rs232 (baud=9600,xmit=PIN_C6, rcv=PIN_C7, parity=N, stop=1) // UNCOMMENT If you need serial communication

#define MOTOR_DIR PIN_B1         // CONFIGURE; According to your direction pin

//custom function prototype
void pwm1_set(int16 mypwm);      // Used for changing PWM1 value

void main()
{
   // PWM CONFIGURATION
   delay_ms(10);
   set_tris_c(0x00);                      // Set all portc pins as output
   setup_ccp1(CCP_PWM);                   // PWM signal output at CCP1 pin 17
   setup_timer_2(T2_DIV_BY_16, 255, 1);   // CONFIGURE Timer Settings
   
   // ANALOG CONFIGURATION
   byte result;                           // Analog Reading Variable
   setup_adc_ports(AN0);                  // CONFIGURE Analog Pin
   setup_adc(ADC_CLOCK_DIV_32);           // Enable ADC and set clock for ADC
   

   output_high(MOTOR_DIR);                // CONFIGURE Motor Direction
   
   while(1)
   {
      pwm1_set(512);
      //pwm1_set(800);           // UNCOMMENT If you wish to have dynamic PWM duty cycle 
      //pwm1_set(1000);          // UNCOMMENT If you wish to have dynamic PWM duty cycle
      
      // ANALOG READING PART (UNCOMMENT IF YOU NEED)
      //set_adc_channel(0);          // CONFIGURE Analog Reading Channel
      //result = read_adc();         // Start and Read A/D
      //delay_us(10);                // Allow time after channel selection and reading
      //printf("Value=%u",result);   // Print ADC value
   }
}
//custom function for changing PWM1 value
void pwm1_set(int16 mypwm)
{
      set_pwm1_duty(mypwm);
      delay_ms(1000);                // Delay between PWM duty cycles
}
