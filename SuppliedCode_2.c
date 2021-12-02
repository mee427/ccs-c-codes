#include <16F877A.h>
#device ADC=10
#FUSES NOWDT                     // No Watch Dog Timer
#FUSES NOBROWNOUT                // No brownout reset
#FUSES NOLVP                     // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)     // CONFIGURE According to your crystal frequency

// Configuration for Serial Communication
#use rs232 (baud=9600,xmit=PIN_C6, rcv=PIN_C7, parity=N, stop=1) // UNCOMMENT If you need serial communication

#define MOTOR_DIR PIN_B1         // CONFIGURE; According to your direction pin

//custom function prototype
unsigned long analogReadFunction(int8 channel);

void main()
{
   // PWM CONFIGURATION
   delay_ms(10);
   set_tris_c(0x00);                      // Set all portc pins as output
   setup_ccp1(CCP_PWM);                   // PWM signal output at CCP1 pin 17
   setup_timer_2(T2_DIV_BY_16, 255, 1);   // CONFIGURE Timer Settings
   
   // ANALOG CONFIGURATION
   unsigned long velocityFeedback;
   unsigned long currentFeedback;
   setup_adc_ports(ALL_ANALOG);           // CONFIGURE Analog Pin
   setup_adc(ADC_CLOCK_DIV_32);           // Enable ADC and set clock for ADC
   
   unsigned long rotVelocity;
   unsigned long current;
   int8 channel0 = 0;
   int8 channel1 = 1;
   
   while(1)
   {
      output_high(MOTOR_DIR);                // CONFIGURE Motor Direction
      
      set_pwm1_duty(102);
      velocityFeedback = analogReadFunction(channel0);
      // ENTER YOUR VELOCITY MODEL
      //rotVelocity = 
      currentFeedback = analogReadFunction(channel1);
      // ENTER YOUR CURRENT MODEL
      //current = 
      printf("Velocity=%lu, ",rotVelocity);   // Print ADC value
      printf("Current=%lu \n", current);
      delay_ms(2000);
      
      set_pwm1_duty(204);
      velocityFeedback = analogReadFunction(channel0);
      // ENTER YOUR VELOCITY MODEL
      //rotVelocity = 
      currentFeedback = analogReadFunction(channel1);
      // ENTER YOUR CURRENT MODEL
      //current = 
      printf("Velocity=%lu, ",rotVelocity);   // Print ADC value
      printf("Current=%lu \n", current);
      delay_ms(2000);
      
      set_pwm1_duty(306);
      velocityFeedback = analogReadFunction(channel0);
      // ENTER YOUR VELOCITY MODEL
      //rotVelocity = 
      currentFeedback = analogReadFunction(channel1);
      // ENTER YOUR CURRENT MODEL
      //current = 
      printf("Velocity=%lu, ",rotVelocity);   // Print ADC value
      printf("Current=%lu \n", current);
      delay_ms(2000);
   }
}
//custom function for changing PWM1 value
unsigned long analogReadFunction(int8 channel)
{
      // ANALOG READING PART (UNCOMMENT IF YOU NEED)
      set_adc_channel(channel);                    // CONFIGURE Analog Reading Channel
      unsigned long analogValue = read_adc();         // Start and Read A/D
      delay_us(10);                          // Allow time after channel selection and reading
      
      return analogValue;
}

