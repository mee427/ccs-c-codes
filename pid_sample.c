#include <16F877A.h>
#device ADC=10
#FUSES NOWDT                     // No Watch Dog Timer
#FUSES NOBROWNOUT                // No brownout reset
#FUSES NOLVP                     // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)     // CONFIGURE According to your crystal frequency

// Configuration for Serial Communication
#use rs232 (baud=9600,xmit=PIN_C6, rcv=PIN_C7, parity=N, stop=1) // UNCOMMENT If you need serial communication

#define MOTOR_DIR PIN_B1         // CONFIGURE; According to your direction pin

unsigned long int_ctr=0;    // interrupt counter
int time_step_ctr = 0;
float error = 0.0;
float integral = 0.0;
float derivative = 0.0;
float previousError = 0.0;
float dt = 0.05;

float actualDegree;
float refDegree;
float Kp = 1;
float Ki = 0;
float Kd = 0;

#int_timer0        // timer interrupt function tag (this line is critical)
void tmr_int(){    // timer interrupt function (works when timer0 overflows)
   set_timer0(156);     // setting timer0 value again
   int_ctr++;     
   time_step_ctr++;     // since interrupt func freq is too high, a led_ctr is used
   if (time_step_ctr==100)   // at each 10th interrupt (~1000ms)
   {       
      integral = integral + error*dt;
      derivative = (error - previousError)/dt;
      previousError = error;
      time_step_ctr=0;      // reset time step counter
   }
}


void main()
{
   // PWM CONFIGURATION
   delay_ms(10);
   set_tris_c(0x00);                      // Set all portc pins as output
   setup_ccp1(CCP_PWM);                   // PWM signal output at CCP1 pin 17
   setup_timer_2(T2_DIV_BY_16, 255, 1);   // CONFIGURE Timer Settings
   
   set_timer0(156);     //timer0 value set
           //internal clock        //prescaling 256
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); 
   enable_interrupts(int_timer0);
   enable_interrupts(global);  
   
   // ANALOG CONFIGURATION
   float potFeedback;
   
   setup_adc_ports(ALL_ANALOG);           // CONFIGURE Analog Pin
   setup_adc(ADC_CLOCK_DIV_32);           // Enable ADC and set clock for ADC
   
   unsigned long rotVelocity;
   unsigned long current;
   
   output_high(MOTOR_DIR);                // CONFIGURE Motor Direction
   
   set_pwm1_duty(0);
   delay_ms(5000);
   
   while(1)
   {      
   
      set_adc_channel(0);                    // CONFIGURE Analog Reading Channel
      potFeedback = read_adc();         // Start and Read A/D
      delay_us(10);                          // Allow time after channel selection and reading
      
      // Apply the Relation between potFeedback and the actualDegree
      
   
      error = refDegree - actualDegree;
      float controlSignal = Kp*error + Ki*integral + Kd*derivative;
      
      // Check Control Signal Direction (Positive or Negative)
      // Assign Direction, Apply PWM duty
      
      
      unsigned long elapsedTime = int_ctr*10;
      //printf("int_ctr: %lu",int_ctr);
      printf("t: %lu ",elapsedTime);
      printf("w=%lu, ",rotVelocity);   // Print ADC value
      printf("i=%lu\n", current);
      
   }
}

