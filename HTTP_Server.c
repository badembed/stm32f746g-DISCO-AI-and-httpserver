/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2019 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HTTP_Server.c
 * Purpose: HTTP Server example
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "main.h"

#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE

#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "Board_GLCD.h"                 // ::Board Support:Graphic LCD
#include "GLCD_Config.h"                // Keil.STM32F746G-Discovery::Board Support:Graphic LCD

#include "app_x-cube-ai.h"

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern uint16_t AD_in          (uint32_t ch);
extern uint8_t  get_button     (void);
extern void     netDHCP_Notify (uint32_t if_num, uint8_t option, const uint8_t *val, uint32_t len);

extern bool LEDrun;
extern char lcd_text[2][20+1];

extern osThreadId_t TID_Display;
extern osThreadId_t TID_Led;

bool LEDrun;
char lcd_text[2][20+1] = { "LCD line 1",
                           "LCD line 2" };

/* Thread IDs */
osThreadId_t TID_Display;
osThreadId_t TID_Led;

/* Thread declarations */
static void BlinkLed (void *arg);
static void Display  (void *arg);

__NO_RETURN void app_main (void *arg);

/* Read analog inputs */
uint16_t AD_in (uint32_t ch) {
  /* User analog input is not available */
  (void)ch;

  return (0);
}

/* Read digital inputs */
uint8_t get_button (void) {
  return ((uint8_t)Buttons_GetState ());
}

/* IP address change notification */
void netDHCP_Notify (uint32_t if_num, uint8_t option, const uint8_t *val, uint32_t len) {

  (void)if_num;
  (void)val;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    /* IP address change, trigger LCD update */
    osThreadFlagsSet (TID_Display, 0x01);
  }
}

TS_StateTypeDef a;

extern ai_float in_data[AI_MNETWORK_IN_1_SIZE];
extern ai_float out_data[AI_MNETWORK_OUT_1_SIZE];

/*----------------------------------------------------------------------------
  Thread 'Display': LCD display handler
 *---------------------------------------------------------------------------*/
static __NO_RETURN void Display (void *arg) {
  static uint8_t ip_addr[NET_ADDR_IP6_LEN];
  static char    ip_ascii[40];
  static char    buf[24];
  uint32_t x = 5;

  (void)arg;
/*
  GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
  GLCD_DrawString         (x*16U, 1U*24U, "       MDK-MW       ");
  GLCD_DrawString         (x*16U, 2U*24U, "HTTP Server example ");

  GLCD_DrawString (x*16U, 4U*24U, "IP4:Waiting for DHCP");

  // Print Link-local IPv6 address
  netIF_GetOption (NET_IF_CLASS_ETH,
                   netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));

  netIP_ntoa(NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));

  sprintf (buf, "IP6:%.16s", ip_ascii);
  GLCD_DrawString ( x    *16U, 5U*24U, buf);
  sprintf (buf, "%s", ip_ascii+16);
  GLCD_DrawString ((x+10U)*16U, 6U*24U, buf);

  while(1) {
    // Wait for signal from DHCP
    osThreadFlagsWait (0x01U, osFlagsWaitAny, osWaitForever);

    // Retrieve and print IPv4 address
    netIF_GetOption (NET_IF_CLASS_ETH,
                     netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));

    netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));

    sprintf (buf, "IP4:%-16s",ip_ascii);
    GLCD_DrawString (x*16U, 4U*24U, buf);

    // Display user text lines
    sprintf (buf, "%-20s", lcd_text[0]);
    GLCD_DrawString (x*16U, 7U*24U, buf);
    sprintf (buf, "%-20s", lcd_text[1]);
    GLCD_DrawString (x*16U, 8U*24U, buf);
  }
	*/
	
	BSP_TS_Init(BSP_LCD_GetXSize(),BSP_LCD_GetYSize());
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font8);
	
	// Print Link-local IPv6 address
	netIF_GetOption (NET_IF_CLASS_ETH,
                   netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));
  netIP_ntoa(NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
	sprintf (buf, "IP6:%.16s%s", ip_ascii, ip_ascii+16);
	BSP_LCD_DisplayStringAtLine(0, buf);
	
	// Wait for signal from DHCP
	//osThreadFlagsWait (0x01U, osFlagsWaitAny, osWaitForever);

	// Retrieve and print IPv4 address
	netIF_GetOption (NET_IF_CLASS_ETH,
									 netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));

  netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));

	sprintf (buf, "IP4:%-16s",ip_ascii);
  BSP_LCD_DisplayStringAtLine(1, buf);

  // Display user text lines
  sprintf (buf, "%-20s", lcd_text[0]);
	BSP_LCD_DisplayStringAtLine(2, buf);
	
	uint8_t flag = 1;
	
	while (1)
  {
    /* USER CODE END WHILE */		
		BSP_LCD_DrawRect(8,24,224,224);
		BSP_LCD_DrawRect(248,24,224,224);			
		BSP_TS_GetState(&a);		
		while (a.touchDetected>0) {
			BSP_TS_GetState(&a);
			if (a.touchX[0]>8 && a.touchX[0] < 232 && a.touchY[0] > 24 && a.touchY[0] < 248) {
				((ai_float *)in_data)[(a.touchY[0]-24)/8*28+(a.touchX[0]-8)/8]=(ai_float)1.0f;
				BSP_LCD_FillCircle(a.touchX[0],a.touchY[0],4);
			}
			
			if (a.touchX[0] > 248 && a.touchX[0] < 472 && a.touchY[0] > 24 && a.touchY[0] < 248) {
				if (flag == 1) {
					aiRun(in_data, out_data);
					
					int num = 0;
					ai_float max = 0;
					for (int i=0; i < 10; i++) {
						if(out_data[i]>max) {							
							max = out_data[i];
							num = i;
						}
					}
					
					sprintf(buf, "%d", num);
					BSP_LCD_SetFont(&Font57);
					BSP_LCD_DisplayStringAt(340, 100, (uint8_t*)buf, LEFT_MODE);
					
					flag *= -1;
					while (a.touchDetected>0) {
						BSP_TS_GetState(&a);
					}
				} else {
					flag *= -1;
					BSP_LCD_Clear(LCD_COLOR_BLACK);
					for(int i=0;i<784;i++) {
						in_data[i]=0;
					}
					while (a.touchDetected > 0) {
						BSP_TS_GetState(&a);
					}
					break;
				}
			}
		}
	}		
}

/*----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *---------------------------------------------------------------------------*/
static __NO_RETURN void BlinkLed (void *arg) {
  const uint8_t led_val[16] = { 0x48,0x88,0x84,0x44,0x42,0x22,0x21,0x11,
                                0x12,0x0A,0x0C,0x14,0x18,0x28,0x30,0x50 };
  uint32_t cnt = 0U;

  (void)arg;

  LEDrun = true;
  while(1) {
    /* Every 100 ms */
    if (LEDrun == true) {
      LED_SetOut (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0U;
      }
    }
    osDelay (100);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'main': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  (void)arg;

  LED_Initialize();
  Buttons_Initialize();

  netInitialize ();

  TID_Led     = osThreadNew (BlinkLed, NULL, NULL);
  TID_Display = osThreadNew (Display,  NULL, NULL);

  osThreadExit();
}
