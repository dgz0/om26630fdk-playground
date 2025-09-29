// SPDX-License-Identifier: MIT
//
// Copyright 2025 dgz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/** @file startup.c Provides startup code for the NXP LPC1769. */

#include "compiler.h"
#include "types.h"

enum vec_tbl_off {
	VEC_TBL_OFF_SP_main		= 0,
	VEC_TBL_OFF_Reset		= 1,
	VEC_TBL_OFF_NMI			= 2,
	VEC_TBL_OFF_HardFault		= 3,
	VEC_TBL_OFF_MemManage		= 4,
	VEC_TBL_OFF_BusFault		= 5,
	VEC_TBL_OFF_UsageFault		= 6,
	VEC_TBL_OFF_SVCall		= 11,
	VEC_TBL_OFF_DebugMonitor	= 12,
	VEC_TBL_OFF_PendSV		= 14,
	VEC_TBL_OFF_SysTick		= 15,
	VEC_TBL_OFF_WDT			= 16,
	VEC_TBL_OFF_TMR0		= 17,
	VEC_TBL_OFF_TMR1		= 18,
	VEC_TBL_OFF_TMR2		= 19,
	VEC_TBL_OFF_TMR3		= 20,
	VEC_TBL_OFF_UART0		= 21,
	VEC_TBL_OFF_UART1		= 22,
	VEC_TBL_OFF_UART2		= 23,
	VEC_TBL_OFF_UART3		= 24,
	VEC_TBL_OFF_PWM1		= 25,
	VEC_TBL_OFF_I2C0		= 26,
	VEC_TBL_OFF_I2C1		= 27,
	VEC_TBL_OFF_I2C2		= 28,
	VEC_TBL_OFF_SPI			= 29,
	VEC_TBL_OFF_SSP0		= 30,
	VEC_TBL_OFF_SSP1		= 31,
	VEC_TBL_OFF_PLL0		= 32,
	VEC_TBL_OFF_RTC			= 33,
	VEC_TBL_OFF_EINT0		= 34,
	VEC_TBL_OFF_EINT1		= 35,
	VEC_TBL_OFF_EINT2		= 36,
	VEC_TBL_OFF_EINT3		= 37,
	VEC_TBL_OFF_ADC			= 38,
	VEC_TBL_OFF_BOD			= 39,
	VEC_TBL_OFF_USB			= 40,
	VEC_TBL_OFF_CAN			= 41,
	VEC_TBL_OFF_GPDMA		= 42,
	VEC_TBL_OFF_I2S			= 43,
	VEC_TBL_OFF_ETH			= 44,
	VEC_TBL_OFF_RIT			= 45,
	VEC_TBL_OFF_MTR_CTRL_PWM	= 46,
	VEC_TBL_OFF_QE			= 47,
	VEC_TBL_OFF_PLL1		= 48,
	VEC_TBL_OFF_USBACT		= 49,
	VEC_TBL_OFF_CANACT		= 50
};

extern u32 __stack;

extern void _start(void);

#define ISR_FUNC WEAK_SYMBOL ALIAS("isr_default")

ISR_FUNC void isr_NMI(void);
ISR_FUNC void isr_HardFault(void);
ISR_FUNC void isr_MemManage(void);
ISR_FUNC void isr_BusFault(void);
ISR_FUNC void isr_UsageFault(void);
ISR_FUNC void isr_SVCall(void);
ISR_FUNC void isr_DebugMonitor(void);
ISR_FUNC void isr_PendSV(void);
ISR_FUNC void isr_SysTick(void);

ISR_FUNC void isr_WDT(void);
ISR_FUNC void isr_TMR0(void);
ISR_FUNC void isr_TMR1(void);
ISR_FUNC void isr_TMR2(void);
ISR_FUNC void isr_TMR3(void);
ISR_FUNC void isr_UART0(void);
ISR_FUNC void isr_UART1(void);
ISR_FUNC void isr_UART2(void);
ISR_FUNC void isr_UART3(void);
ISR_FUNC void isr_PWM1(void);
ISR_FUNC void isr_I2C0(void);
ISR_FUNC void isr_I2C1(void);
ISR_FUNC void isr_I2C2(void);
ISR_FUNC void isr_SPI(void);
ISR_FUNC void isr_SSP0(void);
ISR_FUNC void isr_SSP1(void);
ISR_FUNC void isr_PLL0(void);
ISR_FUNC void isr_RTC(void);
ISR_FUNC void isr_EINT0(void);
ISR_FUNC void isr_EINT1(void);
ISR_FUNC void isr_EINT2(void);
ISR_FUNC void isr_EINT3(void);
ISR_FUNC void isr_ADC(void);
ISR_FUNC void isr_BOD(void);
ISR_FUNC void isr_USB(void);
ISR_FUNC void isr_CAN(void);
ISR_FUNC void isr_GPDMA(void);
ISR_FUNC void isr_I2S(void);
ISR_FUNC void isr_ETH(void);
ISR_FUNC void isr_RIT(void);
ISR_FUNC void isr_MTR_CTRL_PWM(void);
ISR_FUNC void isr_QE(void);
ISR_FUNC void isr_PLL1(void);
ISR_FUNC void isr_USBACT(void);
ISR_FUNC void isr_CANACT(void);

#undef ISR_FUNC

void isr_default(void)
{
	for (;;);
}

PLACE_IN_SECTION(".init")
const void *const __interrupt_vector[] = {
	// clang-format off

	[VEC_TBL_OFF_SP_main]		= &__stack,
	[VEC_TBL_OFF_Reset]		= _start,
	[VEC_TBL_OFF_NMI]		= isr_NMI,
	[VEC_TBL_OFF_HardFault]		= isr_HardFault,
	[VEC_TBL_OFF_MemManage]		= isr_MemManage,
	[VEC_TBL_OFF_BusFault]		= isr_BusFault,
	[VEC_TBL_OFF_UsageFault]	= isr_UsageFault,
	[VEC_TBL_OFF_SVCall]		= isr_SVCall,
	[VEC_TBL_OFF_DebugMonitor]	= isr_DebugMonitor,
	[VEC_TBL_OFF_PendSV]		= isr_PendSV,
	[VEC_TBL_OFF_SysTick]		= isr_SysTick,
	[VEC_TBL_OFF_WDT]		= isr_WDT,
	[VEC_TBL_OFF_TMR0]		= isr_TMR0,
	[VEC_TBL_OFF_TMR1]		= isr_TMR1,
	[VEC_TBL_OFF_TMR2]		= isr_TMR2,
	[VEC_TBL_OFF_TMR3]		= isr_TMR3,
	[VEC_TBL_OFF_UART0]		= isr_UART0,
	[VEC_TBL_OFF_UART1]		= isr_UART1,
	[VEC_TBL_OFF_UART2]		= isr_UART2,
	[VEC_TBL_OFF_UART3]		= isr_UART3,
	[VEC_TBL_OFF_PWM1]		= isr_PWM1,
	[VEC_TBL_OFF_I2C0]		= isr_I2C0,
	[VEC_TBL_OFF_I2C1]		= isr_I2C1,
	[VEC_TBL_OFF_I2C2]		= isr_I2C2,
	[VEC_TBL_OFF_SPI]		= isr_SPI,
	[VEC_TBL_OFF_SSP0]		= isr_SSP0,
	[VEC_TBL_OFF_SSP1]		= isr_SSP1,
	[VEC_TBL_OFF_PLL0]		= isr_PLL0,
	[VEC_TBL_OFF_EINT0]		= isr_EINT0,
	[VEC_TBL_OFF_EINT1]		= isr_EINT1,
	[VEC_TBL_OFF_EINT2]		= isr_EINT2,
	[VEC_TBL_OFF_EINT3]		= isr_EINT3,
	[VEC_TBL_OFF_ADC]		= isr_ADC,
	[VEC_TBL_OFF_BOD]		= isr_BOD,
	[VEC_TBL_OFF_USB]		= isr_USB,
	[VEC_TBL_OFF_CAN]		= isr_CAN,
	[VEC_TBL_OFF_GPDMA]		= isr_GPDMA,
	[VEC_TBL_OFF_I2S]		= isr_I2S,
	[VEC_TBL_OFF_ETH]		= isr_ETH,
	[VEC_TBL_OFF_RIT]		= isr_RIT,
	[VEC_TBL_OFF_MTR_CTRL_PWM]	= isr_MTR_CTRL_PWM,
	[VEC_TBL_OFF_QE]		= isr_QE,
	[VEC_TBL_OFF_PLL1]		= isr_PLL1,
	[VEC_TBL_OFF_USBACT]		= isr_USBACT,
	[VEC_TBL_OFF_CANACT]		= isr_CANACT

	// clang-format on
};
