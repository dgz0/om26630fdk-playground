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

#include "hal-gpio.h"

#define FIO0DIR ((volatile u32 *const)(0x2009C000))
#define FIO1DIR ((volatile u32 *const)(0x2009C020))
#define FIO2DIR ((volatile u32 *const)(0x2009C040))
#define FIO3DIR ((volatile u32 *const)(0x2009C060))
#define FIO4DIR ((volatile u32 *const)(0x2009C080))

#define FIO0MASK ((volatile u32 *const)(0x2009C010))
#define FIO1MASK ((volatile u32 *const)(0x2009C030))
#define FIO2MASK ((volatile u32 *const)(0x2009C050))
#define FIO3MASK ((volatile u32 *const)(0x2009C070))
#define FIO4MASK ((volatile u32 *const)(0x2009C090))

#define FIO0SET ((volatile u32 *const)(0x2009C018))
#define FIO1SET ((volatile u32 *const)(0x2009C038))
#define FIO2SET ((volatile u32 *const)(0x2009C058))
#define FIO3SET ((volatile u32 *const)(0x2009C078))
#define FI04SET ((volatile u32 *const)(0x2009C098))

#define FIO0CLR ((volatile u32 *const)(0x2009C01C))
#define FIO1CLR ((volatile u32 *const)(0x2009C03C))
#define FIO2CLR ((volatile u32 *const)(0x2009C05C))
#define FIO3CLR ((volatile u32 *const)(0x2009C07C))
#define FIO4CLR ((volatile u32 *const)(0x2009C09C))

// clang-format off

const struct hal_gpio_pin HAL_GPIO_PIN_P_0_15 = {
	.port			= HAL_GPIO_PORT_0,
	.pin			= HAL_GPIO_PORT_PIN_15,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL0,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE0,
	.fiodir_reg		= FIO0DIR,
	.fioset_reg		= FIO0SET,
	.fioclr_reg		= FIO0CLR,
	.fio_bit		= BIT_15,
	.pinsel_pinmode_mask	= BIT_31 | BIT_30
};

const struct hal_gpio_pin HAL_GPIO_PIN_P_0_16 = {
	.port			= HAL_GPIO_PORT_0,
	.pin			= HAL_GPIO_PORT_PIN_16,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL1,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE1,
	.fiodir_reg		= FIO0DIR,
	.fioset_reg		= FIO0SET,
	.fioclr_reg		= FIO0CLR,
	.fio_bit		= BIT_16,
	.pinsel_pinmode_mask	= BIT_1 | BIT_0
};

const struct hal_gpio_pin HAL_GPIO_PIN_P_0_17 = {
	.port			= HAL_GPIO_PORT_0,
	.pin			= HAL_GPIO_PORT_PIN_17,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL1,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE1,
	.fiodir_reg		= FIO0DIR,
	.fioset_reg		= FIO0SET,
	.fioclr_reg		= FIO0CLR,
	.fio_bit		= BIT_17,
	.pinsel_pinmode_mask	= BIT_3 | BIT_2
};

const struct hal_gpio_pin HAL_GPIO_PIN_P_0_18 = {
	.port			= HAL_GPIO_PORT_0,
	.pin			= HAL_GPIO_PORT_PIN_18,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL1,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE1,
	.fiodir_reg		= FIO0DIR,
	.fioset_reg		= FIO0SET,
	.fioclr_reg		= FIO0CLR,
	.fio_bit		= BIT_18,
	.pinsel_pinmode_mask	= BIT_5 | BIT_4
};

const struct hal_gpio_pin HAL_GPIO_PIN_P_1_27 = {
	.port			= HAL_GPIO_PORT_1,
	.pin			= HAL_GPIO_PORT_PIN_27,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL3,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE3,
	.fiodir_reg		= FIO1DIR,
	.fioset_reg		= FIO1SET,
	.fioclr_reg		= FIO1CLR,
	.fio_bit		= BIT_27,
	.pinsel_pinmode_mask	= BIT_23 | BIT_22
};

const struct hal_gpio_pin HAL_GPIO_PIN_P_2_5 = {
	.port			= HAL_GPIO_PORT_2,
	.pin			= HAL_GPIO_PORT_PIN_5,
	.pinsel_reg		= HAL_PINSEL_REG_PINSEL4,
	.pinmode_reg		= HAL_PINMODE_REG_PINMODE4,
	.fiodir_reg		= FIO2DIR,
	.fioset_reg		= FIO2SET,
	.fioclr_reg		= FIO2CLR,
	.fio_bit		= BIT_5,
	.pinsel_pinmode_mask	= BIT_11 | BIT_10
};

// clang-format on

void hal_gpio_init(void)
{
	*FIO0MASK = 0x00000000;
	*FIO1MASK = 0x00000000;
	*FIO2MASK = 0x00000000;
	*FIO3MASK = 0x00000000;
	*FIO4MASK = 0x00000000;
}

void hal_gpio_pin_init(const struct hal_gpio_pin *const pin,
		       const struct hal_gpio_pin_cfg *const cfg)
{
	if (cfg->pin_func == HAL_PINSEL_FUNC_GPIO) {
		app_assert(cfg->dir != HAL_GPIO_PIN_DIR_AUTO);

		if (cfg->dir == HAL_GPIO_PIN_DIR_INPUT)
			*pin->fiodir_reg &= ~pin->fio_bit;
		else if (cfg->dir == HAL_GPIO_PIN_DIR_OUTPUT)
			*pin->fiodir_reg |= pin->fio_bit;
		else
			UNREACHABLE;
	}

	hal_pincm_set_func(pin->pinsel_reg, pin->pinsel_pinmode_mask,
			   cfg->pin_func);

	hal_pincm_set_resistor(pin->pinmode_reg, pin->pinsel_pinmode_mask,
			       cfg->resistor);
}
