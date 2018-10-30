#include <pid_control.h>
#include <stdlib.h>
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)

int counter = 0;
char strInput[4];
unsigned long pwm;

void main()
{
   while(TRUE)
   {
      if(kbhit())   // If data has been received
    {                             
      char i = getc();                        // UART read
      if (i == '*')
      {
         counter = 0;
         printf(strInput);
         pwm = atol(strInput);
         printf("sayi %lu",pwm);
         memset(strInput, 0, 4);
      }
      else
      {
         strInput[counter] = i;
         counter++;
      }
    }
   }
}