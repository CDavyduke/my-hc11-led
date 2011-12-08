/* memory.x -- Memory definition for a bootstrap program
   Copyright 2000, 2003 Free Software Foundation, Inc.
   Written by Stephane Carrez (stcarrez@nerim.fr)

This file is part of GTAM.

GTAM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GTAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GTAM; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Defines the memory layout for a bootstrap program.
   Pretend there is no data section.  Everything is for the text.
   The page0 overlaps the text and we have to take care of that
   in the program (this is volunteered).  */
MEMORY
{
  page0 (rwx) : ORIGIN = 0x0, LENGTH = 256
  text  (rx)  : ORIGIN = 0x2400, LENGTH = 512
  data        : ORIGIN = 0x2600, LENGTH = 512
  eeprom      : ORIGIN = 0xb600, LENGTH = 512
}

/* Setup the stack on the top of the data internal ram (not used).  */
PROVIDE (_stack = 0x2600-1);
PROVIDE (_io_ports = 0x1000);

/* Setup the LCD access variables.  */
PROVIDE (_gdm_lcd_cmd = 0xB5F0);
PROVIDE (_gdm_lcd_data = 0xB5F1);
