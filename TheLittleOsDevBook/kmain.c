#include "io.h"

#define FB_GREEN     2
#define FB_DARK_GREY 8

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

char *fb = (char *) 0x000B8000;

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
         fb[i] = c;
         fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int kmain() {
  fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
  fb_move_cursor(4);
  return 0;
}
