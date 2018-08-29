/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

// #include <ti/drivers/GPIO.h>
// #include <ti/drivers/PWM.h>
// #include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

#include "CC2640R2_RSM.h"

#define Board_initGeneral()     CC2640R2_RSM_initGeneral()

// /* These #defines allow us to reuse TI-RTOS across other device families */
// 
// #define Board_3V3_EN            CC2640R2_RSM_3V3_EN
// 
// #define Board_CRYPTO0           CC2640R2_RSM_CRYPTO0
// 
// #define Board_GPIO_BUTTON0      CC2640R2_RSM_GPIO_S1
// #define Board_GPIO_BUTTON1      CC2640R2_RSM_GPIO_S2
// #define Board_GPIO_LED0         CC2640R2_RSM_GPIO_LED3
// #define Board_GPIO_LED1         CC2640R2_RSM_GPIO_LED4
// #define Board_GPIO_LED2         Board_GPIO_LED0
// #define Board_GPIO_LED_ON       CC2640R2_RSM_GPIO_LED_ON
// #define Board_GPIO_LED_OFF      CC2640R2_RSM_GPIO_LED_OFF
// 
// #define Board_GPTIMER0A         CC2640R2_RSM_GPTIMER0A
// #define Board_GPTIMER0B         CC2640R2_RSM_GPTIMER0B
// #define Board_GPTIMER1A         CC2640R2_RSM_GPTIMER1A
// #define Board_GPTIMER1B         CC2640R2_RSM_GPTIMER1B
// #define Board_GPTIMER2A         CC2640R2_RSM_GPTIMER2A
// #define Board_GPTIMER2B         CC2640R2_RSM_GPTIMER2B
// #define Board_GPTIMER3A         CC2640R2_RSM_GPTIMER3A
// #define Board_GPTIMER3B         CC2640R2_RSM_GPTIMER3B
// 
// #define Board_KEY_DOWN          CC2640R2_RSM_KEY_DOWN
// #define Board_KEY_LEFT          CC2640R2_RSM_KEY_LEFT
// #define Board_KEY_RIGHT         CC2640R2_RSM_KEY_RIGHT
// #define Board_KEY_SELECT        CC2640R2_RSM_KEY_SELECT
// #define Board_KEY_UP            CC2640R2_RSM_KEY_UP
// 
// #define Board_LCD_CSN           CC2640R2_RSM_LCD_CSN
// #define Board_LCD_MODE          CC2640R2_RSM_LCD_MODE
// #define Board_LCD_RST           CC2640R2_RSM_LCD_RST
// 
// #define Board_PIN_BUTTON0       CC2640R2_RSM_KEY_UP
// #define Board_PIN_BUTTON1       CC2640R2_RSM_KEY_DOWN
// #define Board_PIN_LED0          CC2640R2_RSM_PIN_LED3
// #define Board_PIN_LED1          CC2640R2_RSM_PIN_LED4
// #define Board_PIN_LED2          Board_PIN_LED0
// 
// #define Board_PWM0              CC2640R2_RSM_PWM0
// #define Board_PWM1              CC2640R2_RSM_PWM1
// #define Board_PWM2              CC2640R2_RSM_PWM2
// #define Board_PWM3              CC2640R2_RSM_PWM3
// #define Board_PWM4              CC2640R2_RSM_PWM4
// #define Board_PWM5              CC2640R2_RSM_PWM5
// #define Board_PWM6              CC2640R2_RSM_PWM6
// #define Board_PWM7              CC2640R2_RSM_PWM7
// 
// #define Board_SPI0              CC2640R2_RSM_SPI0
// #define Board_SPI1              CC2640R2_RSM_SPI1
// 
#define Board_UART0             CC2640R2_RSM_UART0
// 
// #define Board_WATCHDOG0         CC2640R2_RSM_WATCHDOG0

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */