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

#pragma once

#include "types.h"
#include "util.h"

#define HAL_SYSCTL ((struct hal_sysctl *const)(0x400FC000))

#define HAL_SYSCTL_CCLK_HZ (mhz_to_hz(96))
#define HAL_SYSCTL_XTAL_HZ (mhz_to_hz(12))
#define HAL_SYSCTL_IRC_HZ (mhz_to_hz(4))
#define HAL_SYSCTL_RTC_HZ (khz_to_hz(32))

enum hal_sysctl_pconp_bit {
	// clang-format off

	HAL_SYSCTL_PCONP_BIT_PCTIM0	= BIT_1,
	HAL_SYSCTL_PCONP_BIT_PCTIM1	= BIT_2,
	HAL_SYSCTL_PCONP_BIT_PCUART0	= BIT_3,
	HAL_SYSCTL_PCONP_BIT_PCUART1	= BIT_4,
	HAL_SYSCTL_PCONP_BIT_PCPWM1	= BIT_6,
	HAL_SYSCTL_PCONP_BIT_PCI2C0	= BIT_7,
	HAL_SYSCTL_PCONP_BIT_PCSPI	= BIT_8,
	HAL_SYSCTL_PCONP_BIT_PCRTC	= BIT_9,
	HAL_SYSCTL_PCONP_BIT_PCSSP1	= BIT_10,
	HAL_SYSCTL_PCONP_BIT_PCADC	= BIT_12,
	HAL_SYSCTL_PCONP_BIT_PCCAN1	= BIT_13,
	HAL_SYSCTL_PCONP_BIT_PCCAN2	= BIT_14,
	HAL_SYSCTL_PCONP_BIT_PCGPIO	= BIT_15,
	HAL_SYSCTL_PCONP_BIT_PCRIT	= BIT_16,
	HAL_SYSCTL_PCONP_BIT_PCMCPWM	= BIT_17,
	HAL_SYSCTL_PCONP_BIT_PCQEI	= BIT_18,
	HAL_SYSCTL_PCONP_BIT_PCI2C1	= BIT_19,
	HAL_SYSCTL_PCONP_BIT_PCSSP0	= BIT_21,
	HAL_SYSCTL_PCONP_BIT_PCTIM2	= BIT_22,
	HAL_SYSCTL_PCONP_BIT_PCTIM3	= BIT_23,
	HAL_SYSCTL_PCONP_BIT_PCUART2	= BIT_24,
	HAL_SYSCTL_PCONP_BIT_PCUART3	= BIT_25,
	HAL_SYSCTL_PCONP_BIT_PCI2C2	= BIT_26,
	HAL_SYSCTL_PCONP_BIT_PCI2S	= BIT_27,
	HAL_SYSCTL_PCONP_BIT_PCGPDMA	= BIT_29,
	HAL_SYSCTL_PCONP_BIT_PCENET	= BIT_30,
	HAL_SYSCTL_PCONP_BIT_PCUSB	= BIT_31,
	HAL_SYSCTL_PCONP_BIT_ALL_MASK	= HAL_SYSCTL_PCONP_BIT_PCTIM0  |
					  HAL_SYSCTL_PCONP_BIT_PCTIM1  |
					  HAL_SYSCTL_PCONP_BIT_PCUART0 |
					  HAL_SYSCTL_PCONP_BIT_PCUART1 |
					  HAL_SYSCTL_PCONP_BIT_PCPWM1  |
					  HAL_SYSCTL_PCONP_BIT_PCI2C0  |
					  HAL_SYSCTL_PCONP_BIT_PCSPI   |
					  HAL_SYSCTL_PCONP_BIT_PCRTC   |
					  HAL_SYSCTL_PCONP_BIT_PCSSP1  |
					  HAL_SYSCTL_PCONP_BIT_PCADC   |
					  HAL_SYSCTL_PCONP_BIT_PCCAN1  |
					  HAL_SYSCTL_PCONP_BIT_PCCAN2  |
					  HAL_SYSCTL_PCONP_BIT_PCGPIO  |
					  HAL_SYSCTL_PCONP_BIT_PCRIT   |
					  HAL_SYSCTL_PCONP_BIT_PCMCPWM |
					  HAL_SYSCTL_PCONP_BIT_PCQEI   |
					  HAL_SYSCTL_PCONP_BIT_PCI2C1  |
					  HAL_SYSCTL_PCONP_BIT_PCSSP0  |
					  HAL_SYSCTL_PCONP_BIT_PCTIM2  |
					  HAL_SYSCTL_PCONP_BIT_PCTIM3  |
					  HAL_SYSCTL_PCONP_BIT_PCUART2 |
					  HAL_SYSCTL_PCONP_BIT_PCUART3 |
					  HAL_SYSCTL_PCONP_BIT_PCI2C2  |
					  HAL_SYSCTL_PCONP_BIT_PCI2S   |
					  HAL_SYSCTL_PCONP_BIT_PCGPDMA |
					  HAL_SYSCTL_PCONP_BIT_PCENET  |
					  HAL_SYSCTL_PCONP_BIT_PCUSB

	// clang-format on
};

enum hal_sysctl_pclksel_mask {
	// clang-format off

	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_WDT	= BIT_0  | BIT_1,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_TIMER0	= BIT_2  | BIT_3,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_TIMER1	= BIT_4  | BIT_5,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_UART0	= BIT_6  | BIT_7,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_UART1	= BIT_8  | BIT_9,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_PWM1	= BIT_12 | BIT_13,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_I2C0	= BIT_14 | BIT_15,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_SPI	= BIT_16 | BIT_17,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_SSP1	= BIT_20 | BIT_21,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_DAC	= BIT_22 | BIT_23,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_ADC	= BIT_24 | BIT_25,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_CAN1	= BIT_26 | BIT_27,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_CAN2	= BIT_28 | BIT_29,
	HAL_SYSCTL_PCLKSEL0_MASK_PCLK_ACF	= BIT_30 | BIT_31,

	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_QEI	= BIT_0  | BIT_1,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_GPIOINT	= BIT_2  | BIT_3,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_PCB	= BIT_4  | BIT_5,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_I2C1	= BIT_6  | BIT_7,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_SSP0	= BIT_10 | BIT_11,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_TIMER2	= BIT_12 | BIT_13,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_TIMER3	= BIT_14 | BIT_15,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_UART2	= BIT_16 | BIT_17,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_UART3	= BIT_18 | BIT_19,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_I2C2	= BIT_20 | BIT_21,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_I2S	= BIT_22 | BIT_23,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_RIT	= BIT_26 | BIT_27,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_SYSCON	= BIT_28 | BIT_29,
	HAL_SYSCTL_PCLKSEL1_MASK_PCLK_MC	= BIT_30 | BIT_31

	// clang-format on
};

enum hal_sysctl_pclksel_clk {
	HAL_SYSCTL_PCLKSEL_CCLK_DIV_4 = 0,
	HAL_SYSCTL_PCLKSEL_CCLK_DIV_1 = 1,
	HAL_SYSCTL_PCLKSEL_CCLK_DIV_2 = 2,
	HAL_SYSCTL_PCLKSEL_CCLK_DIV_3 = 3
};

enum hal_sysctl_scs {
	HAL_SYSCTL_SCS_BIT_OSCRANGE = BIT_4,
	HAL_SYSCTL_SCS_BIT_OSCEN = BIT_5,
	HAL_SYSCTL_SCS_BIT_OSCSTAT = BIT_6
};

enum hal_sysctl_main_osc_range {
	HAL_SYSCTL_MAIN_OSC_RANGE_1_TO_20_MHZ = 0,
	HAL_SYSCTL_MAIN_OSC_RANGE_15_TO_25_MHZ = 1,
	HAL_SYSCTL_MAIN_OSC_RANGE_VALID
};

enum hal_sysctl_flash_acc_time {
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_1 = 0,
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_2 = 1,
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_3 = 2,
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_4 = 3,
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_5 = 4,
	HAL_SYSCTL_FLASH_ACC_TIME_CLK_6 = 5
};

enum hal_sysctl_osc_src {
	HAL_SYSCTL_OSC_IRC = 0,
	HAL_SYSCTL_OSC_MAIN = 1,
	HAL_SYSCTL_OSC_RTC = 2,
	HAL_SYSCTL_OSC_NUM
};

enum hal_sysctl_clkout_clk_src {
	HAL_SYSCTL_CLKOUT_CLK_SRC_CPU = 0,
	HAL_SYSCTL_CLKOUT_CLK_SRC_MAIN = 1,
	HAL_SYSCTL_CLKOUT_CLK_SRC_IRC = 2,
	HAL_SYSCTL_CLKOUT_CLK_SRC_USB = 3,
	HAL_SYSCTL_CLKOUT_CLK_SRC_RTC = 4
};

enum hal_sysctl_clkout_clk_div {
	HAL_SYSCTL_CLKOUT_CLK_DIV_1 = 0,
	HAL_SYSCTL_CLKOUT_CLK_DIV_2 = 1,
	HAL_SYSCTL_CLKOUT_CLK_DIV_3 = 2,
	HAL_SYSCTL_CLKOUT_CLK_DIV_4 = 3,
	HAL_SYSCTL_CLKOUT_CLK_DIV_5 = 4,
	HAL_SYSCTL_CLKOUT_CLK_DIV_6 = 5,
	HAL_SYSCTL_CLKOUT_CLK_DIV_7 = 6,
	HAL_SYSCTL_CLKOUT_CLK_DIV_8 = 7,
	HAL_SYSCTL_CLKOUT_CLK_DIV_9 = 8,
	HAL_SYSCTL_CLKOUT_CLK_DIV_10 = 9,
	HAL_SYSCTL_CLKOUT_CLK_DIV_11 = 10,
	HAL_SYSCTL_CLKOUT_CLK_DIV_12 = 11,
	HAL_SYSCTL_CLKOUT_CLK_DIV_13 = 12,
	HAL_SYSCTL_CLKOUT_CLK_DIV_14 = 13,
	HAL_SYSCTL_CLKOUT_CLK_DIV_15 = 14,
	HAL_SYSCTL_CLKOUT_CLK_DIV_16 = 15
};

struct hal_sysctl_pll_cfg {
	u32 pll_mul;
	u32 pll_div;
	u32 osc_src;
	u32 cclkcfg_div;
};

struct hal_sysctl_pll {
	volatile u32 CON;
	volatile u32 CFG;
	volatile const u32 STAT;
	volatile u32 FEED;
};

struct hal_sysctl {
	volatile u32 FLASHCFG;

	const u32 pad0[31];

	/** Phase Locked Loop (PLL0, Main PLL) */
	struct hal_sysctl_pll PLL0;

	const u32 pad1[4];

	/** Phase Locked Loop (PLL1, USB PLL) */
	struct hal_sysctl_pll PLL1;

	const u32 pad2[4];

	/** Power Control Register */
	volatile u32 PCON;

	/** Power Control for Peripherals Register */
	volatile u32 PCONP;

	const u32 pad3[15];

	/** CPU Clock Configuration Register */
	volatile u32 CCLKCFG;

	/** USB Clock Configuration Register */
	volatile u32 USBCLKCFG;

	/** Clock Source Select Register */
	volatile u32 CLKSRCSEL;

	/** CAN Sleep Clear register */
	volatile u32 CANSLEEPCLR;

	/** CAN Wake-up Flags register */
	volatile u32 CANWAKEFLAGS;

	const u32 pad4[10];

	/** External Interrupt Flag Register */
	volatile u32 EXTINT;

	const u32 pad5;

	/** External Interrupt Mode register */
	volatile u32 EXTMODE;

	/** External Interrupt Polarity Register */
	volatile u32 EXTPOLAR;

	const u32 pad6[12];

	/** Reset Source Identification Register */
	volatile u32 RSID;

	const u32 pad7[7];

	/** System Controls and Status register */
	volatile u32 SCS;

	const u32 pad8;

	/** Peripheral Clock Selection register 0 */
	volatile u32 PCLKSEL0;

	/** Peripheral Clock Selection register 1 */
	volatile u32 PCLKSEL1;

	const u32 pad9[4];

	/** USB Interrupt status */
	volatile u32 USBIntSt;

	/** DMA Request Select register */
	volatile u32 DMAREQSEL;

	/** Clock Output Configuration Register */
	volatile u32 CLKOUTCFG;
};

static_assert_offset(struct hal_sysctl, FLASHCFG, 0x000);
static_assert_offset(struct hal_sysctl, PLL0.CON, 0x080);
static_assert_offset(struct hal_sysctl, PLL0.CFG, 0x084);
static_assert_offset(struct hal_sysctl, PLL0.STAT, 0x088);
static_assert_offset(struct hal_sysctl, PLL0.FEED, 0x08C);
static_assert_offset(struct hal_sysctl, PLL1.CON, 0x0A0);
static_assert_offset(struct hal_sysctl, PLL1.CFG, 0x0A4);
static_assert_offset(struct hal_sysctl, PLL1.STAT, 0x0A8);
static_assert_offset(struct hal_sysctl, PLL1.FEED, 0x0AC);
static_assert_offset(struct hal_sysctl, PCON, 0x0C0);
static_assert_offset(struct hal_sysctl, PCONP, 0x0C4);
static_assert_offset(struct hal_sysctl, CCLKCFG, 0x104);
static_assert_offset(struct hal_sysctl, USBCLKCFG, 0x108);
static_assert_offset(struct hal_sysctl, CLKSRCSEL, 0x10C);
static_assert_offset(struct hal_sysctl, CANSLEEPCLR, 0x110);
static_assert_offset(struct hal_sysctl, CANWAKEFLAGS, 0x114);
static_assert_offset(struct hal_sysctl, EXTINT, 0x140);
static_assert_offset(struct hal_sysctl, EXTMODE, 0x148);
static_assert_offset(struct hal_sysctl, EXTPOLAR, 0x14C);
static_assert_offset(struct hal_sysctl, RSID, 0x180);
static_assert_offset(struct hal_sysctl, SCS, 0x1A0);
static_assert_offset(struct hal_sysctl, PCLKSEL0, 0x1A8);
static_assert_offset(struct hal_sysctl, PCLKSEL1, 0x1AC);
static_assert_offset(struct hal_sysctl, USBIntSt, 0x1C0);
static_assert_offset(struct hal_sysctl, DMAREQSEL, 0x1C4);
static_assert_offset(struct hal_sysctl, CLKOUTCFG, 0x1C8);

void hal_sysctl_periph_pwr_en(enum hal_sysctl_pconp_bit mask);
void hal_sysctl_periph_pwr_dis(enum hal_sysctl_pconp_bit mask);

void hal_sysctl_flash_acc_time_set(enum hal_sysctl_flash_acc_time acc_time);

void hal_sysctl_main_osc_en(enum hal_sysctl_main_osc_range osc_range);

void hal_sysctl_cclk_set(const struct hal_sysctl_pll_cfg *cfg);

void hal_sysctl_clkout_cfg_set(enum hal_sysctl_clkout_clk_src clk_src,
			       enum hal_sysctl_clkout_clk_div clk_div);
