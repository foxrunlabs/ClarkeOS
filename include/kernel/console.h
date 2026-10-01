/*==============================================================================
  console.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Console Procedures Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _CONSOLE_H
#define _CONSOLE_H


/*==============================================================================
  Macros
==============================================================================*/

#define TEXTMODE_VIDEO_RAM 0xb8000

#define COLUMNS	80
#define ROWS	25

#define TAB_WIDTH 8

/* Text Colors */
#define BLACK         0x00
#define BLUE          0x01
#define GREEN         0x02
#define CYAN          0x03
#define RED           0x04
#define MAGENTA       0x05
#define BROWN         0x06
#define WHITE         0x07
#define GRAY          0x08
#define LIGHT_BLUE    0x09
#define LIGHT_GREEN   0x0A
#define LIGHT_CYAN    0x0B
#define LIGHT_RED     0x0C
#define LIGHT_MAGENTA 0x0D
#define YELLOW        0x0E
#define BRIGHT_WHITE  0x0F


/*==============================================================================
  Function Prototypes
==============================================================================*/

void clear_screen();
void console_write(char);

void set_cursor(int, int);
void set_text_attribute(int, int);


#endif /* _CONSOLE_H */
