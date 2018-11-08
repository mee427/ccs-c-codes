#include <16F877A.h>

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#use fast_io(B)

int8 last_read;
signed int8 quad = 0;
signed int16 change = 0;
signed int16 realPosition = 0;

#INT_RB                                      // RB port interrupt on change
void RB_IOC_ISR(void) 
{
  int8 encoderRead;
  clear_interrupt(INT_RB);
  encoderRead = input_b() & 0x30;
  if(encoderRead == last_read)
    return;
  if(bit_test(encoderRead, 4) == bit_test(last_read, 5))
    quad -= 1;
  else
    quad += 1;
  last_read = encoderRead;  
}

signed int16 EncoderGet(void) {
  signed int16 value = 0;
  while(quad >= 4){
    value += 1;
    quad -= 4;
  }
  while(quad <= -4){
    value -= 1;
    quad += 4;
  }
  return value;
}


void main()
{
   // Rotary Pot Define
   port_b_pullups(TRUE);
   enable_interrupts(GLOBAL);
   clear_interrupt(INT_RB);
   delay_ms(1000);
   last_read = input_b() & 0x30;
   enable_interrupts(INT_RB);

   while(TRUE)
   {
      change = EncoderGet();
      if(change)
      {
         realPosition += change;
      }
    }
}