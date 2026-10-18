#ifndef SHARP_LCD_H
#define SHARP_LCD_H

#include <stdint.h>

#define LCD_W 128
#define LCD_H 128

void lcd_init(void);                                    /* power-up sequence from the datasheet */
void lcd_task(void);                                    /* call often from the main loop: toggles EXTCOMIN */
void lcd_clear(void);                                   /* framebuffer -> all white */
void lcd_set_pixel(int x, int y, int black);
void lcd_draw_circle(int cx, int cy, int r);            /* outline */
void lcd_fill_circle(int cx, int cy, int r);            /* filled */
void lcd_flush(void);                                   /* send framebuffer to the display */

#endif
