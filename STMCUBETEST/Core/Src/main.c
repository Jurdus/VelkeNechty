/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include <icon_menu_food.h>
#include <icon_menu_game.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_WIDTH       128
#define LCD_HEIGHT      128
#define LCD_ROW_BYTES   (LCD_WIDTH / 8) // 16 bytes per row



// Internal RAM buffer replacing image_data
static uint8_t lcd_buffer[LCD_HEIGHT][LCD_ROW_BYTES];

const uint8_t font5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32: Space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // 33: !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // 34: "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // 35: #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // 36: $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // 37: %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // 38: &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // 39: '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // 40: (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // 41: )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // 42: *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // 43: +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // 44: ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // 45: -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // 46: .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // 47: /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 48: 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 49: 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 50: 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 51: 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 52: 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53: 5
    {0x3C, 0x4a, 0x49, 0x49, 0x30}, // 54: 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 55: 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56: 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 57: 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // 58: :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // 59: ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // 60: <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // 61: =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // 62: >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // 63: ?
    {0x32, 0x49, 0x59, 0x51, 0x3e}, // 64: @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // 65: A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 66: B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 67: C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 68: D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 69: E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 70: F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // 71: G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 72: H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 73: I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 74: J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 75: K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 76: L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // 77: M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 78: N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 79: O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 80: P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 81: Q
    {0x7F, 0x09, 0x09, 0x19, 0x66}, // 82: R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // 83: S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 84: T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 85: U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 86: V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 87: W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88: X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 89: Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // 90: Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // 91: [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // 92: \ (escaped)
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // 93: ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // 94: ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // 95: _
    {0x00, 0x01, 0x02, 0x04, 0x00}, // 96: `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // 97: a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // 98: b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // 99: c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // 100: d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 101: e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // 102: f
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // 103: g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // 104: h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // 105: i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // 106: j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // 107: k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // 108: l
    {0x7C, 0x04, 0x78, 0x04, 0x78}, // 109: m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // 110: n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 111: o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // 112: p
    {0x08, 0x14, 0x14, 0x18, 0x7C}, // 113: q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // 114: r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // 115: s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // 116: t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 117: u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 118: v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 119: w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 120: x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // 121: y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // 122: z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // 123: {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // 124: |
    {0x41, 0x36, 0x08, 0x00, 0x00}, // 125: }
    {0x02, 0x01, 0x02, 0x04, 0x02}  // 126: ~
};

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
void enter_bootloader(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define SCK_H()  (GPIOA->BSRR = GPIO_PIN_5)
#define SCK_L()  (GPIOA->BRR  = GPIO_PIN_5)
#define SI_H()   (GPIOA->BSRR = GPIO_PIN_7)
#define SI_L()   (GPIOA->BRR  = GPIO_PIN_7)
#define CS_H()   (GPIOB->BSRR = GPIO_PIN_0)
#define CS_L()   (GPIOB->BRR  = GPIO_PIN_0)

static uint8_t vcom = 0;

static void dly_cycles(uint32_t c) {
    uint32_t s = DWT->CYCCNT;
    while ((DWT->CYCCNT - s) < c) { }
}

static void lcd_byte(uint8_t b) {            /* LSB first */
    uint32_t half = SystemCoreClock / 200000U;   /* ~0.5 us */
    for (int i = 0; i < 8; i++) {
        if (b & 1) SI_H(); else SI_L();
        b >>= 1;
        dly_cycles(half);
        SCK_H();
        dly_cycles(half);
        SCK_L();
    }
}

static void lcd_clear_cmd(void) {            /* M2 = clear all memory */
    vcom ^= 0x02;
    CS_H();
    dly_cycles(SystemCoreClock / 100000U);   /* ~10 us */
    lcd_byte(0x04 | vcom);
    lcd_byte(0x00);
    dly_cycles(SystemCoreClock / 100000U);
    CS_L();
}

static void lcd_send_frame(void) {           /* Sends the entire buffer to the LCD */
    vcom ^= 0x02;
    CS_H();
    dly_cycles(SystemCoreClock / 100000U);   /* ~10 us */
    lcd_byte(0x01 | vcom);                   /* M0 = write lines command */

    for (int y = 1; y <= 128; y++) {
        lcd_byte((uint8_t)y);                /* line address, 1-based (1 to 128) */
        for (int x = 0; x < LCD_ROW_BYTES; x++) {
            lcd_byte(lcd_buffer[y - 1][x]);  /* Send row bytes from framebuffer */
        }
        lcd_byte(0x00);                      /* line trailer */
    }

    lcd_byte(0x00);                          /* final trailer */
    dly_cycles(SystemCoreClock / 100000U);
    CS_L();
}

void lcd_set_pixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) {
        return; // Out of bounds safety check
    }

    uint16_t byte_idx = x / 8;
    uint8_t bit_idx = x % 8; // Matches your LSB-first transmission logic

    if (color) {
        lcd_buffer[y][byte_idx] |= (1 << bit_idx);   // Set pixel to white
    } else {
        lcd_buffer[y][byte_idx] &= ~(1 << bit_idx);  // Set pixel to black
    }
}

void lcd_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {
    int16_t dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;
    int16_t e2;

    while (1) {
        lcd_set_pixel(x0, y0, color);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void lcd_clear_screen(void) {
    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_ROW_BYTES; x++) {
            lcd_buffer[y][x] = 0xFF; // 0xFF = all white pixels
        }
    }
}

void lcd_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    if (w <= 0 || h <= 0) return;

    lcd_draw_line(x, y, x + w - 1, y, color);         // Top edge
    lcd_draw_line(x, y + h - 1, x + w - 1, y + h - 1, color); // Bottom edge
    lcd_draw_line(x, y, x, y + h - 1, color);         // Left edge
    lcd_draw_line(x + w - 1, y, x + w - 1, y + h - 1, color); // Right edge
}

/**
 * @brief Draws a solid filled rectangle.
 * @param x Top-left X coordinate
 * @param y Top-left Y coordinate
 * @param w Width of the rectangle
 * @param h Height of the rectangle
 * @param color 1 = Black dot, 0 = White background
 */
void lcd_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    if (w <= 0 || h <= 0) return;

    for (int16_t i = 0; i < h; i++) {
        lcd_draw_line(x, y + i, x + w - 1, y + i, color);
    }
}

void lcd_draw_ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t color) {
    if (rx <= 0 || ry <= 0) return;

    int32_t a2 = (int32_t)rx * rx;
    int32_t b2 = (int32_t)ry * ry;
    int32_t two_a2 = 2 * a2;
    int32_t two_b2 = 2 * b2;
    int32_t x = rx;
    int32_t y = 0;
    int32_t sigma = 2 * b2 + a2 * (1 - 2 * rx);

    // Region 1
    while (b2 * x >= a2 * y) {
        lcd_set_pixel(x0 + x, y0 + y, color);
        lcd_set_pixel(x0 - x, y0 + y, color);
        lcd_set_pixel(x0 + x, y0 - y, color);
        lcd_set_pixel(x0 - x, y0 - y, color);

        if (sigma >= 0) {
            sigma -= two_a2 * x;
            x--;
        }
        sigma += two_b2 * y + b2;
        y++;
    }

    // Region 2
    x = 0;
    y = ry;
    sigma = 2 * a2 + b2 * (1 - 2 * ry);

    while (a2 * y >= b2 * x) {
        lcd_set_pixel(x0 + x, y0 + y, color);
        lcd_set_pixel(x0 - x, y0 + y, color);
        lcd_set_pixel(x0 + x, y0 - y, color);
        lcd_set_pixel(x0 - x, y0 - y, color);

        if (sigma >= 0) {
            sigma -= two_b2 * y;
            y--;
        }
        sigma += two_a2 * x + a2;
        x++;
    }
}

void lcd_draw_char(int16_t x, int16_t y, char c, uint8_t color, uint8_t size) {
    if (c < 32 || c > 126) {
        c = '?'; // Fallback for unsupported characters
    }

    uint8_t char_idx = c - 32;

    for (uint8_t col = 0; col < 5; col++) {
        uint8_t line = font5x7[char_idx][col];
        for (uint8_t row = 0; row < 8; row++) {
            if (line & (1 << row)) {
                if (size == 1) {
                    lcd_set_pixel(x + col, y + row, color);
                } else {
                    lcd_fill_rect(x + (col * size), y + (row * size), size, size, color);
                }
            }
        }
    }
}
void lcd_print_string(int16_t x, int16_t y, const char *str, uint8_t color, uint8_t size) {
    int16_t cursor_x = x;
    int16_t cursor_y = y;

    while (*str) {
        if (*str == '\n') {
            cursor_x = x;
            cursor_y += (8 * size) + 2; // Move down by character height + padding
        } else {
            // Wrap to next line if it exceeds screen bounds (128px wide)
            if (cursor_x + (5 * size) >= 128) {
                cursor_x = x;
                cursor_y += (8 * size) + 2;
            }

            lcd_draw_char(cursor_x, cursor_y, *str, color, size);
            cursor_x += (6 * size); // 5 columns + 1 pixel letter spacing
        }
        str++;
    }
}
static void lcd_draw_icon(const uint8_t *icon, int w, int h, int x0, int y0) {
    int row_bytes = (w + 7) / 8;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int px = x0 + x;
            int py = y0 + y;
            if (px < 0 || px >= 128 || py < 0 || py >= 128) continue;

            int white = (icon[y * row_bytes + (x >> 3)] >> (x & 7)) & 1;
            if (white) lcd_buffer[py][px >> 3] |=  (uint8_t)(1u << (px & 7));
            else       lcd_buffer[py][px >> 3] &= (uint8_t)~(1u << (px & 7));
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	SCB->VTOR = FLASH_BASE | 0x2000;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;   /* enable cycle counter */
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);  /* DISP low */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);  /* EXTMODE low: VCOM via command bit */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);  /* EXTCOMIN unused */
  HAL_Delay(50);

  lcd_clear_cmd();

  //telo
  memset(lcd_buffer, 0xFF, sizeof(lcd_buffer));   /* all white */
  lcd_draw_ellipse(64, 64, 15, 15, 0x00);

  //oci
  lcd_draw_ellipse(58, 58, 2, 2, 0x00);
  lcd_draw_ellipse(68, 58, 2, 2, 0x00);

  lcd_draw_rect(58, 57, 2, 2, 0x00);
  lcd_draw_rect(68, 57, 2, 2, 0x00);

  //usmev
  lcd_draw_line(58, 68, 68, 68, 0x00);
  lcd_draw_line(58, 68, 68, 68, 0x00);
  lcd_draw_line(54, 64, 58, 68, 0x00);
  lcd_draw_line(68, 68, 72, 64, 0x00);

  //menu
  lcd_draw_rect(106,106,18,18,0x00);
  lcd_draw_icon(icon_menu_food, 16, 16 ,107,107);
  lcd_draw_icon(icon_menu_game, 16,16,54,107);
  lcd_draw_rect(0,100,128,2,0x00);


  lcd_send_frame();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);    /* DISP high: show memory */


  uint8_t menu_pos[6];
  	  menu_pos[0] = 106;
  	  menu_pos[1] = 53;
  	  uint8_t menu = 0;
bool btn3;

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);   /* PA8  red   */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);   /* PA9  green */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);   /* PA10 blue  */

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 80);   /* 5% */
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 80);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 80);

  btn3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  btn3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET;
	  if (btn3){

		  lcd_draw_rect(menu_pos[menu],106,18,18,0xFF);
		  menu = 1;
		  lcd_draw_rect(menu_pos[menu],106,18,18,0x00);
		  lcd_send_frame();
		  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET){
			  HAL_Delay(1);
		  }


	  }

	  // LED TEST
	  /*
	  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
	  HAL_Delay(100);*/
		  if(btn3) {
			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 70);
			  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 70);
			  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 70);


		  }else{
			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
			  	  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
			  	  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		  }
		  HAL_Delay(10);
	  if (HAL_GetTick() > 10000) enter_bootloader();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 50;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DISP_EXTMODE_Pin|DISP_SCLK_Pin|DISP_SI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DISP_SCS_Pin|DISP_EXTCOMIN_Pin|DISP_DISP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);

  /*Configure GPIO pins : BUT1_Pin BUT2_Pin BUT3_Pin */
  GPIO_InitStruct.Pin = BUT1_Pin|BUT2_Pin|BUT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DISP_EXTMODE_Pin DISP_SCLK_Pin DISP_SI_Pin */
  GPIO_InitStruct.Pin = DISP_EXTMODE_Pin|DISP_SCLK_Pin|DISP_SI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DISP_SCS_Pin DISP_EXTCOMIN_Pin DISP_DISP_Pin */
  GPIO_InitStruct.Pin = DISP_SCS_Pin|DISP_EXTCOMIN_Pin|DISP_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void enter_bootloader(void) {
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    BKP->DR1 = 0x4F42;      /* dapboot's magic value */
    NVIC_SystemReset();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
