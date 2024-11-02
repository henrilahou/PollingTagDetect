/*------------------------------------------------------------------------------
 * Copyright (c) 2018 Arm Limited (or its affiliates).
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1.Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   2.Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   3.Neither the name of Arm nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *------------------------------------------------------------------------------
 * Name:    GUI_VNC.c
 * Purpose: 
 *----------------------------------------------------------------------------*/

#include "cmsis_os2.h"
#include "GUI.h"
#include "Dialog.h"
#include "main.h"
#include "string.h"
#include <stdio.h>
#include "Board_LED.h" 

extern WM_HWIN CreateMyDialog(void);
extern int  GUI_VNC_X_StartServer(int, int);

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
#define GUI_THREAD_STK_SZ    (4096U)

#define ID_FRAMEWIN_0            (GUI_ID_USER + 0x00)
#define ID_MULTIEDIT_0           (GUI_ID_USER + 0x01)
#define ID_MULTIEDIT_1           (GUI_ID_USER + 0x02)


extern osMessageQueueId_t mid_MsgQueue;

static void         GUIThread (void *argument);         /* thread function */
static osThreadId_t GUIThread_tid;                      /* thread id */
static uint64_t     GUIThread_stk[GUI_THREAD_STK_SZ/8]; /* thread stack */

static const osThreadAttr_t GUIThread_attr = {
  .stack_mem  = &GUIThread_stk[0],
  .stack_size = sizeof(GUIThread_stk),
  .priority   = osPriorityNormal 
};

int Init_GUIThread (void) {

  GUIThread_tid = osThreadNew(GUIThread, NULL, &GUIThread_attr);
  if (GUIThread_tid == NULL) {
    return(-1);
  }

  return(0);
}

__NO_RETURN static void GUIThread (void *argument) {
  (void)argument;

  GUI_Init();           /* Initialize the Graphics Component */

  GUI_VNC_X_StartServer(0,0);
	CreateMyDialog();
  WM_HWIN hWin = CreateMyDialog();

  WM_HWIN Usart = WM_GetDialogItem(hWin, ID_MULTIEDIT_0);
  WM_HWIN Color = WM_GetDialogItem(hWin, ID_MULTIEDIT_1);
	
	MULTIEDIT_SetFont(Usart, GUI_FONT_20_ASCII); 
	MULTIEDIT_SetFont(Color, GUI_FONT_20_ASCII);
	
	char buf[64]; 
  char ontvangenID[64]; 
  uint16_t idIndex = 0;   
  uint16_t id = 0; 
	uint32_t startTime = 0; 
	uint8_t firstScan = 0; 
	uint16_t timer = 0;

	
  const char* geldigeIDs[] = {
    "87E75239",       
    "0431516AA77680", 
    "71407FFD"        
  };
  int numIDs = sizeof(geldigeIDs) / sizeof(geldigeIDs[0]); 

  while (1) {

    while (osMessageQueueGet(mid_MsgQueue, buf, 0, 0) == osOK) {
			
			if (firstScan == 0) { 
        MULTIEDIT_SetText(Usart, "");
        firstScan = 1;
      }
			
      MULTIEDIT_AddText(Usart, buf); 

      ontvangenID[idIndex++] = buf[0]; 

      if (buf[0] == '\n' || buf[0] == '\r') {
        ontvangenID[idIndex - 1] = '\0'; 
				idIndex = 0;
				id = 0;

        for (int i = 0; i < numIDs; i++) {
          if (strcmp(ontvangenID, geldigeIDs[i]) == 0) {
            id = 1;
            break;  
          }
        }

				if (id == 1 && !timer) {
					startTime = HAL_GetTick(); 
					timer = 1;
					MULTIEDIT_SetBkColor(Color, MULTIEDIT_CI_EDIT, GUI_GREEN);
					MULTIEDIT_SetText(Color, "Geldig ID gescand");
					LED_On(0);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
					WM_Exec(); 
				}
			}
		}
		
		if (timer && (HAL_GetTick() - startTime >= 3000)) {
			MULTIEDIT_SetBkColor(Color, MULTIEDIT_CI_EDIT, GUI_WHITE);
			MULTIEDIT_SetText(Color, "unkowb ID");
			LED_Off(0);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
			timer = 0;
			WM_Exec();
		}

		/* All GUI related activities might only be called from here */
		
#ifdef RTE_Graphics_Touchscreen   /* Graphics Input Device Touchscreen enabled */
    GUI_TOUCH_Exec();             /* Execute Touchscreen support */
#endif
    GUI_Exec();                   /* Execute all GUI jobs ... Return 0 if nothing was done. */
    GUI_X_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
    osDelay(100);
  }
}
