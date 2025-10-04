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

#include "hal-sysctl.h"

#define PLL0_MIN_FREQ (mhz_to_hz(275))
#define PLL0_MAX_FREQ (mhz_to_hz(550))

#define PLL0CON_BIT_PLLE0 (BIT_0)
#define PLL0CON_BIT_PLLC0 (BIT_1)

#define PLL0STAT_BIT_PLOCK0 (BIT_26)
#define PLL0FEED_MASK \
	(BIT_7 | BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)

#define PLL0CFG_MASK_MSEL0                                                    \
	(BIT_14 | BIT_13 | BIT_12 | BIT_11 | BIT_10 | BIT_9 | BIT_8 | BIT_7 | \
	 BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)

#define PLL0CFG_MASK_NSEL0 \
	(BIT_23 | BIT_22 | BIT_21 | BIT_20 | BIT_19 | BIT_18 | BIT_17 | BIT_16)

#define CCLKCFG_MASK_CCLKSEL \
	(BIT_7 | BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)

#define FLASHCFG_MASK_FLASHTIM (BIT_15 | BIT_14 | BIT_13 | BIT_12)

#define CLKOUTCFG_MASK_CLKOUTSEL (BIT_3 | BIT_2 | BIT_1 | BIT_0)
#define CLKOUTCFG_MASK_CLKOUTDIV (BIT_7 | BIT_6 | BIT_5 | BIT_4)
#define CLKOUTCFG_BIT_CLKOUT_EN (BIT_8)

enum {
	CLKSRCSEL_MASK_CLKSRC = BIT_1 | BIT_0,
	CLKSRCSEL_CLKSRC_MAIN_OSC = 1,
};

enum pll0feed_data { PLL0FEED_SEQ_FIRST = 0xAA, PLL0FEED_SEQ_SECOND = 0x55 };

static void pll_feed_seq(struct hal_sysctl_pll *const pll)
{
	set_val_by_mask(pll->FEED, PLL0FEED_MASK, PLL0FEED_SEQ_FIRST);
	set_val_by_mask(pll->FEED, PLL0FEED_MASK, PLL0FEED_SEQ_SECOND);
}

void hal_sysctl_periph_pwr_en(const enum hal_sysctl_pconp_bit mask)
{
	HAL_SYSCTL->PCONP |= mask;
}

void hal_sysctl_periph_pwr_dis(const enum hal_sysctl_pconp_bit mask)
{
	HAL_SYSCTL->PCONP &= ~mask;
}

void hal_sysctl_flash_acc_time_set(const enum hal_sysctl_flash_acc_time acc_time)
{
	set_val_by_mask(HAL_SYSCTL->FLASHCFG, FLASHCFG_MASK_FLASHTIM, acc_time);
}

void hal_sysctl_main_osc_en(const enum hal_sysctl_main_osc_range osc_range)
{
	app_assert(osc_range < HAL_SYSCTL_MAIN_OSC_RANGE_VALID);

	if (likely(osc_range == HAL_SYSCTL_MAIN_OSC_RANGE_1_TO_20_MHZ))
		HAL_SYSCTL->SCS &= ~HAL_SYSCTL_SCS_BIT_OSCRANGE;
	else if (unlikely(osc_range == HAL_SYSCTL_MAIN_OSC_RANGE_15_TO_25_MHZ))
		HAL_SYSCTL->SCS |= HAL_SYSCTL_SCS_BIT_OSCRANGE;

	HAL_SYSCTL->SCS |= HAL_SYSCTL_SCS_BIT_OSCEN;

	while (!(HAL_SYSCTL->SCS & HAL_SYSCTL_SCS_BIT_OSCSTAT))
		hal_no_op();
}

void hal_sysctl_cclk_set(const struct hal_sysctl_pll_cfg *const cfg)
{
	// The following sequence must be followed step by step in order to have
	// PLL0 initialized and running:

	// 1. Disconnect PLL0 with one feed sequence if PLL0 is already
	//    connected.
	if (HAL_SYSCTL->PLL0.CON & PLL0CON_BIT_PLLC0) {
		HAL_SYSCTL->PLL0.CON &= ~PLL0CON_BIT_PLLC0;
		pll_feed_seq(&HAL_SYSCTL->PLL0);
	}

	// 2. Disable PLL0 with one feed sequence.
	HAL_SYSCTL->PLL0.CON &= ~PLL0CON_BIT_PLLE0;
	pll_feed_seq(&HAL_SYSCTL->PLL0);

	// 3. Change the CPU Clock Divider setting to speed up operation without
	//    PLL0, if desired.
	//
	//    This isn't needed at this stage.

	// 4. Write to the Clock Source Selection Control register to change the
	//    clock source if needed.
	set_val_by_mask(HAL_SYSCTL->CLKSRCSEL, CLKSRCSEL_MASK_CLKSRC,
			cfg->osc_src);

	// 5. Write to the PLL0CFG and make it effective with one feed sequence.
	//    The PLL0CFG can only be updated when PLL0 is disabled.
	set_val_by_mask(HAL_SYSCTL->PLL0.CFG, PLL0CFG_MASK_MSEL0,
			cfg->pll_mul - 1);
	set_val_by_mask(HAL_SYSCTL->PLL0.CFG, PLL0CFG_MASK_NSEL0,
			cfg->pll_div - 1);
	pll_feed_seq(&HAL_SYSCTL->PLL0);

	// 6. Enable PLL0 with one feed sequence.
	HAL_SYSCTL->PLL0.CON |= PLL0CON_BIT_PLLE0;
	pll_feed_seq(&HAL_SYSCTL->PLL0);

	// 7. Change the CPU Clock Divider setting for the operation with PLL0.
	//    It is critical to do this before connecting PLL0.
	set_val_by_mask(HAL_SYSCTL->CCLKCFG, CCLKCFG_MASK_CCLKSEL,
			cfg->cclkcfg_div - 1);

	// 8. Wait for PLL0 to achieve lock by monitoring the PLOCK0 bit in the
	//    PLL0STAT register, or using the PLOCK0 interrupt, or wait for a
	//    fixed time when the input clock to PLL0 is slow (i.e. 32 kHz).
	//    The value of PLOCK0 may not be stable when the PLL reference
	//    frequency (FREF, the frequency of REFCLK, which is equal to the
	//    PLL input frequency divided by the pre-divider value) is less than
	//    100 kHz or greater than 20 MHz. In these cases, the PLL may be
	//    assumed to be stable after a start-up time has passed. This time
	//    is 500us when FREF is greater than 400 kHz and 200 / FREF seconds
	//    when FREF is less than 400 kHz.
	while (!(HAL_SYSCTL->PLL0.STAT & PLL0STAT_BIT_PLOCK0))
		hal_no_op();

	// 9. Connect PLL0 with one feed sequence.
	HAL_SYSCTL->PLL0.CON |= PLL0CON_BIT_PLLC0;
	pll_feed_seq(&HAL_SYSCTL->PLL0);

	// It is very important not to merge any steps above. For example, do
	// not update the PLL0CFG and enable PLL0 simultaneously with the same
	// feed sequence.
}

void hal_sysctl_clkout_cfg_set(const enum hal_sysctl_clkout_clk_src clk_src,
			       const enum hal_sysctl_clkout_clk_div clk_div)
{
	set_val_by_mask(HAL_SYSCTL->CLKOUTCFG, CLKOUTCFG_MASK_CLKOUTSEL,
			clk_src);

	set_val_by_mask(HAL_SYSCTL->CLKOUTCFG, CLKOUTCFG_MASK_CLKOUTDIV,
			clk_div);

	HAL_SYSCTL->CLKOUTCFG |= CLKOUTCFG_BIT_CLKOUT_EN;
}
