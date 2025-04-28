#include <stddef.h>
#include "driver/vga_graphic_mode.h"
#include "driver/port.h"
#include "driver/font.h"
#include "driver/ps2.h"

unsigned char *enable_graphic_256_xmode()
{
	port_byte_out(0x3ce, 0x06);
	port_byte_out(0x3cf, 0b0011); // Miscellaneous Graphic Register, Select 256K Memory map
	port_byte_out(0x3ce, 0x05);
	port_byte_out(0x3cf, 0b01000000); // Graphics Mode Register, enable 256 colors mode 
	port_byte_out(0x3ce, 0x03);
	port_byte_out(0x3cf, 0b00000000); // Data Rotate register, Don't rotate data 
	port_byte_out(0x3c2, 0x63); // Set Miscellaneous Output Register
	port_byte_out(0x3c4, 0x01);
	port_byte_out(0x3c5, 0x1); // Switch to 8 Dot Modes (360x320 pixels)
	port_byte_out(0x3c4, 0x02);
	port_byte_out(0x3c5, 0b11111); // Map Mask Register: Enable Read from all Memory Plane
	port_byte_out(0x3c4, 0x04);
  port_byte_out(0x3c5, 0b1110); //Enable Chain 4, enable Extended Memory
  port_byte_out(0x3d4, 0x01); 
  port_byte_out(0x3d5, 0x4F);  // Horizontal Display End
	port_byte_out(0x3d4, 0x02); 
	port_byte_out(0x3d5, 0x50);  // Start Horizontal Blank
	port_byte_out(0x3d4, 0x04); 
	port_byte_out(0x3d5, 0x82);  // End Horizontal Blank
	port_byte_out(0x3d4, 0x05); 
	port_byte_out(0x3d5, 0x9C);  // Start Horizontal Retrace
	port_byte_out(0x3d4, 0x06); 
	port_byte_out(0x3d5, 0x0B);  // End Horizontal Retrace
	port_byte_out(0x3d4, 0x09);
	port_byte_out(0x3d5, 0x41); // Max Scan Line: Set Max Scan Line To 0 and Enable Scan Doubling
	port_byte_out(0x3d4, 0x0a);
	port_byte_out(0x3d5, 0x0); // Disable Cursor
	port_byte_out(0x3d4, 0x17);
	port_byte_out(0x3d5, 0xe3); // Set CRTC Mode Control
	port_byte_out(0x3ce, 0x08);
	port_byte_out(0x3cf, 0xff); // Bit Mask for Write mode, enable all bits
	port_byte_out(0x3d4, 0x14);
	port_byte_out(0x3d5, 0x0); // Disable long mod
	port_byte_out(0x3d4, 0x17);
	port_byte_out(0x3d5, 0xe3); // Enable word mode
	port_byte_out(0x3c2, 0x65);

	return ((unsigned char *) VGA_FRONT_BUFFER);
}

static inline void wait_for_vsync()
{
  while (!(port_byte_in(0x3da) & 0b00001000)) 
    __asm__ volatile("nop");

  while (port_byte_in(0x3da) & 0b00001000) 
  	__asm__ volatile("nop");
}


unsigned char *switch_buffers()
{
  static unsigned char *visible_buffer = (unsigned char *) VGA_FRONT_BUFFER;
  static unsigned char *non_visible_buffer = (unsigned char *) VGA_BACK_BUFFER;
  unsigned char *tmp = visible_buffer;
  unsigned int new_addr;

  visible_buffer = non_visible_buffer;
  non_visible_buffer = tmp;

  new_addr = (unsigned int) visible_buffer & 0x0FFFF;

  __asm__ volatile("cli");

  wait_for_vsync(); 
  port_byte_out(0x3d4, 0x0c);
  port_byte_out(0x3d5, (new_addr >> 8));
  port_byte_out(0x3d4, 0x0d);
  port_byte_out(0x3d5, (new_addr & 0xff));
  wait_for_vsync(); 

  __asm__ volatile("sti");

  return non_visible_buffer;
}

void put_a_pixel(int x, int y, int color, unsigned char *buffer)
{
	buffer[((VGA_WIDTH*y)+x)] = color;
}

void add_color_to_dac(unsigned char r, unsigned char g, unsigned char b, unsigned char index)
{
	static int previous_index = -2;

	if (previous_index + 1 != index)
		port_byte_out(0x3c8, index);
	port_byte_out(0x3c9, r);
	port_byte_out(0x3c9, g);
	port_byte_out(0x3c9, b);
	previous_index = index;
}

void display_letter(unsigned char letter, int bg_color, int fg_color, unsigned char *buffer, int screen_x, int screen_y)
{
	unsigned char pixel = 0;

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 8; x++) {
			pixel = g_8x16_font[letter * 16 + y] & bit(x);
			put_a_pixel((8 - x) + (screen_x * 8), y + (screen_y * 16), pixel == 0 ? bg_color : fg_color, buffer);
		}
	}
}