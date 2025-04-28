#include "syslog.h"
#include "driver/vga_graphic_mode.h"
#include <stddef.h>

void syslog(int type, char *buf, int len){
  puts(buf);
	for (int i = 0, x = 0, y = 0; buf[i]; i++) {
    if (buf[i] == '\n') {
      y++;
      x = 0;
    } else {
      display_letter(buf[i], 0x00, 0x0a, VGA_FRONT_BUFFER, x, y);
      x++;
      if (x == 40) {
        x = 0;
        y++;
      }
    }
  }
}