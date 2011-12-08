/*	=================================================================
	Filename:			LED.c
	Author:				Corey Davyduke
	Creation date:		2011-11-29
	Last modified date:	2011-11-30
	Description:		This file contains the source code to blink
	an LED.
	=================================================================
*/


#include <sys/ports.h>
//#include <string.h>

#define BIT_0 (1<<0)
#define BIT_1 (1<<1)
#define BIT_2 (1<<2)
#define BIT_3 (1<<3)
#define BIT_4 (1<<4)
#define BIT_5 (1<<5)
#define BIT_6 (1<<6)
#define BIT_7 (1<<7)

/* Port D */
#define BOARD_RX     (BIT_0)
#define BOARD_TX     (BIT_1)
#define BOARD_LCD_0  (BIT_2)
#define BOARD_LCD_1  (BIT_3)
#define BOARD_LCD_2  (BIT_4)
#define BOARD_LCD_3  (BIT_5)

/* Port A */
#define BOARD_KEY_0   (BIT_0)
#define BOARD_KEY_1   (BIT_1)
#define BOARD_KEY_2   (BIT_2)
#define BOARD_ROM_DIS (BIT_3)
#define BOARD_LCD_4   (BIT_4)
#define BOARD_LCD_5   (BIT_5)
#define BOARD_LCD_6   (BIT_6)
#define BOARD_KEY_3   (BIT_7)

/* Port E */
#define BOARD_PEB_0   (BIT_0)
#define BOARD_PEB_1   (BIT_1)
#define BOARD_PEB_2   (BIT_2)
#define BOARD_PEB_3   (BIT_3)
#define BOARD_PEB_4   (BIT_4)
#define BOARD_PEB_5   (BIT_5)
#define BOARD_PEB_6   (BIT_6)
#define BOARD_PEB_7   (BIT_7)

/* Control of Fan, Light and mains detection on Port A.  */
#define EBCS_CMD_FAN     (BOARD_LCD_5)
#define EBCS_CMD_LIGHT   (BOARD_LCD_6)
#define EBCS_SENSE_LIGHT (BOARD_KEY_0)
#define EBCS_SENSE_MAINS (BOARD_PE2)

/* The I/O registers are represented by a volatile array.
   Address if fixed at link time.  For this particular example,
   the _io_ports address is defined in the `memory.x' file.  */
//extern volatile unsigned char _io_ports[];

void delay_ms (unsigned ms);

#define TABLE_SIZE(X) ((sizeof X) / sizeof (X[0]))

/* Speed is defined as a delay and a repetition counter.

   SPEED(200,4) means 4 blinking at 200ms

   Delay and counter are stored using 4-bits each.
*/
#define SPEED(T,CNT) ((((T)/100) & 0x0F) | ((CNT) & 0x0F)<<4)

static const unsigned char speeds[] = {
  SPEED(200,4),
  SPEED(500,2),
  SPEED(300,1),
  SPEED(500,5),
  SPEED(800,3),
  SPEED(200,4),
  SPEED(100,6),
  SPEED(500,4),

  SPEED(200,3),
  SPEED(600,4),
  SPEED(100,2),
  SPEED(400,6),
  SPEED(800,2),
  SPEED(100,1),
  SPEED(900,1),
  SPEED(100,2),
  SPEED(900,1),
  SPEED(100,2),
  SPEED(900,1),

  SPEED(800,4),
  SPEED(100,1),
  SPEED(800,4),
  SPEED(100,2),
  SPEED(800,3),
  SPEED(100,4),
  SPEED(800,2),
  SPEED(100,8),
  SPEED(800,1),

  SPEED(1500,2)
};

/* Wait 'ms' milliseconds (not accurate (:- (:-), hand adjusted
   and based on human time accuracy (understand, SCz feeling).  */
void
delay_ms (unsigned ms)
{
  unsigned short tcnt;

  while (ms > 0)
    {
      unsigned i;
      
      for (i = 100; --i != 0;)
        tcnt = get_timer_counter ();

      ms--;
    }
}

int main ()
{
  unsigned short i;
  unsigned short dt;
  short j;
  
  i = 0;
  while (1)
    {
      dt = speeds[i];
      j = (short) (speeds[i] >> 4);
      dt = (unsigned short) ((speeds[i] & (char) 0x0F) * (char) 100);

      do {
        /* Turn on the light.  */
        _io_ports[M6811_PORTA] |= EBCS_CMD_FAN | EBCS_CMD_LIGHT;

        /* Pause the delay specified in the speeds table.  */
        delay_ms (dt);

        /* Turn off the light.  */
        _io_ports[M6811_PORTA] &= ~(EBCS_CMD_FAN | EBCS_CMD_LIGHT);

        /* Pause again and repeat according to speeds table.  */
        delay_ms (dt);
      } while (--j >= 0);

      /* Pick next blinking rate (wrap to beginning if we reach the end).  */
      i++;
      if (i > TABLE_SIZE (speeds))
        i = 0;
    }
  return 0;
}

