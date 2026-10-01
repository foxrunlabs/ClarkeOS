/*==============================================================================
  console.c -> console.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Console Procedures
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  Includes
==============================================================================*/

#include <kernel/console.h>

#include <drivers/vga.h>

#include <system/io.h>
#include <system/types.h>


/*==============================================================================
  Global Data
==============================================================================*/

void *video_ram = (void *)TEXTMODE_VIDEO_RAM;
uint8_t text_attr = (BLACK << 4) | WHITE;		// Black backgroung, white text

// Text mode cursor
struct
{
	int x, y;
} cursor;


/*==============================================================================
  clear_screen - clear the screen
--------------------------------------------------------------------------------
  Clear the screen by using a 32-bit filler, composed of two null characters
  and their associated text attribute. This takes the loop half as long, since
  we're filling two characters at a time. Reset the cursor to (0,0) at the end.
==============================================================================*/

void clear_screen()
{
	int i;
	uint32_t fill;
	
	fill = 0;		
	fill = (text_attr << 24) | (text_attr << 8);
	
	for(i = 0; i < COLUMNS * ROWS / 2; i++)
		((uint32_t *)video_ram)[i] = fill;
	
	set_cursor(0, 0);
}


/*==============================================================================
  console_write - output character to screen
--------------------------------------------------------------------------------
  Output a single character to the screen. Each character is represented by two
  bytes, the first byte being the actual printed character and the second byte
  being the text attribute. Move the cursor after outputting the character.
==============================================================================*/

void console_write(char c)
{
	int i;

	i = (cursor.x * 2) + (cursor.y * COLUMNS * 2);	// Compute offset into VRAM
	
	switch(c)
	{
		case '\b':
			((uint8_t *)video_ram)[i - 2] = 0;
			((uint8_t *)video_ram)[i - 1] = text_attr;
			
			set_cursor(cursor.x - 1, cursor.y);
			break;

		case '\n':
			set_cursor(0, cursor.y + 1);
			break;
					
		case '\t':
			set_cursor(cursor.x + (TAB_WIDTH - (cursor.x % TAB_WIDTH)), cursor.y);
			break;
		
		case '\r':
			set_cursor(0, cursor.y);
			break;			
		
		default:
			((char *)video_ram)[i] = c;
			((uint8_t *)video_ram)[i + 1] = text_attr;
			
			set_cursor(cursor.x + 1, cursor.y);
			break;
	}
}


/*==============================================================================
  set_cursor - set cursor location on the screen
--------------------------------------------------------------------------------
  Set the cursor location by using the VGA CRT Controller Registers. Write the
  Cursor Location Register (High/Low) to the CRT Controller Address Register,
  followed by the desired cursor location written to the CRT Controller Data
  Register.
==============================================================================*/

void set_cursor(int x, int y)
{
	int offset;
	
	if(x < 0)
		x = 0;
	if(x >= COLUMNS)
	{
		x = 0;
		y++;
	}
	if(y < 0)
		y = 0;
	if(y >= ROWS)
		y = ROWS - 1;
		
	offset = x + (y * COLUMNS);
	
	outb(CRT_ADDR_REG, CURSOR_LOC_LOW_REG);
	outb(CRT_DATA_REG, offset);
	outb(CRT_ADDR_REG, CURSOR_LOC_HIGH_REG);
	outb(CRT_DATA_REG, offset >> 8);
	
	cursor.x = x;
	cursor.y = y;
}


/*==============================================================================
  set_text_attribute - set foreground and background text attributes
--------------------------------------------------------------------------------
  Set the text attribute with the background being the high nibble and the
  foreground being the low nibble of the <text_attr> variable.
==============================================================================*/

void set_text_attribute(int foreground, int background)
{
	text_attr = (background << 4) | foreground;
}

