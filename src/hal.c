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

#include "hal.h"
#include "hal-gpio.h"
#include "hal-sysctl.h"

void hal_process_events(void)
{
}

void hal_init(void)
{
	// Disable all peripherals, resetting their state.
	//
	// It's generally up to the underlying application to decide what
	// peripherals to enable. This saves power and limits the chance of
	// external influences interfering with what the application decides to
	// do.
	hal_sysctl_periph_pwr_dis(HAL_SYSCTL_PCONP_BIT_ALL_MASK);

	// Enable the main oscillator.
	//
	// On the OM26630FDK, there is a 12MHz crystal connected to the XTAL1
	// and XTAL2 pins.
	hal_sysctl_main_osc_en(HAL_SYSCTL_MAIN_OSC_RANGE_1_TO_20_MHZ);

	// Configure CCLK to run at ~96MHz.
	//
	// Although we could run at 120MHz, this would mean we couldn't use CCLK
	// as the USB peripheral clock source since 120MHz is not a multiple of
	// the standard USB clock (48MHz); we would have to bring in PLL1 to
	// pull that off.
	//
	// 96MHz is the closest CCLK we can get to without going over the
	// maximum clock frequency, and without needing PLL1 for USB. This saves
	// power, configuration complexity, and is double the frequency needed
	// for USB operations; we shouldn't run at exactly 48MHz as that could
	// cause unwanted jitter.
	static const struct hal_sysctl_pll_cfg pll_cfg = {
		// clang-format off

		.pll_mul	= 12,
		.pll_div	= 1,
		.cclkcfg_div	= 3,
		.osc_src	= HAL_SYSCTL_OSC_MAIN

		// clang-format on
	};
	hal_sysctl_cclk_set(&pll_cfg);

	// We're now running at 96MHz; we need to adjust the flash access time
	// as a result.
	hal_sysctl_flash_acc_time_set(HAL_SYSCTL_FLASH_ACC_TIME_CLK_5);

	hal_sysctl_periph_pwr_en(HAL_SYSCTL_PCONP_BIT_PCGPIO);
	hal_gpio_init();
}
