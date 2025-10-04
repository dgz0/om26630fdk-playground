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

#include "hal-pincm.h"

enum hal_gpio_port {
	HAL_GPIO_PORT_0,
	HAL_GPIO_PORT_1,
	HAL_GPIO_PORT_2,
	HAL_GPIO_PORT_3,
	HAL_GPIO_PORT_4,
	HAL_GPIO_NUM_PORT
};

enum hal_gpio_port_pin {
	HAL_GPIO_PORT_PIN_0,
	HAL_GPIO_PORT_PIN_1,
	HAL_GPIO_PORT_PIN_2,
	HAL_GPIO_PORT_PIN_3,
	HAL_GPIO_PORT_PIN_4,
	HAL_GPIO_PORT_PIN_5,
	HAL_GPIO_PORT_PIN_6,
	HAL_GPIO_PORT_PIN_7,
	HAL_GPIO_PORT_PIN_8,
	HAL_GPIO_PORT_PIN_9,
	HAL_GPIO_PORT_PIN_10,
	HAL_GPIO_PORT_PIN_11,
	HAL_GPIO_PORT_PIN_12,
	HAL_GPIO_PORT_PIN_13,
	HAL_GPIO_PORT_PIN_14,
	HAL_GPIO_PORT_PIN_15,
	HAL_GPIO_PORT_PIN_16,
	HAL_GPIO_PORT_PIN_17,
	HAL_GPIO_PORT_PIN_18,
	HAL_GPIO_PORT_PIN_19,
	HAL_GPIO_PORT_PIN_20,
	HAL_GPIO_PORT_PIN_21,
	HAL_GPIO_PORT_PIN_22,
	HAL_GPIO_PORT_PIN_23,
	HAL_GPIO_PORT_PIN_24,
	HAL_GPIO_PORT_PIN_25,
	HAL_GPIO_PORT_PIN_26,
	HAL_GPIO_PORT_PIN_27,
	HAL_GPIO_PORT_PIN_28,
	HAL_GPIO_PORT_PIN_29,
	HAL_GPIO_PORT_PIN_30,
	HAL_GPIO_PORT_PIN_31,
	HAL_GPIO_PORT_PIN_NUM
};

enum hal_gpio_pin_dir {
	HAL_GPIO_PIN_DIR_AUTO = 0,
	HAL_GPIO_PIN_DIR_OUTPUT = 1,
	HAL_GPIO_PIN_DIR_INPUT = 2
};

struct hal_gpio_pin {
	const enum hal_gpio_port port;
	const enum hal_gpio_port_pin pin;
	const enum hal_pinsel_reg pinsel_reg;
	const enum hal_pinmode_reg pinmode_reg;
	volatile u32 *const fiodir_reg;
	volatile u32 *const fioset_reg;
	volatile u32 *const fioclr_reg;
	const u32 fio_bit;
	const u32 pinsel_pinmode_mask;
};

struct hal_gpio_pin_cfg {
	enum hal_pinmode_resistor resistor;
	enum hal_pinsel_func pin_func;
	enum hal_gpio_pin_dir dir;
};

void hal_gpio_init(void);

void hal_gpio_pin_init(const struct hal_gpio_pin *pin,
		       const struct hal_gpio_pin_cfg *cfg);

ALWAYS_INLINE void hal_gpio_pin_set_low(const struct hal_gpio_pin *const pin)
{
	*pin->fioclr_reg |= pin->fio_bit;
}

ALWAYS_INLINE void hal_gpio_pin_set_high(const struct hal_gpio_pin *const pin)
{
	*pin->fioset_reg |= pin->fio_bit;
}

ALWAYS_INLINE void hal_gpio_pin_toggle(const struct hal_gpio_pin *const pin)
{
	if ((*pin->fioset_reg) & pin->fio_bit)
		*pin->fioclr_reg |= pin->fio_bit;
	else
		*pin->fioset_reg |= pin->fio_bit;
}

extern const struct hal_gpio_pin HAL_GPIO_PIN_P_0_15;
extern const struct hal_gpio_pin HAL_GPIO_PIN_P_0_16;
extern const struct hal_gpio_pin HAL_GPIO_PIN_P_0_17;
extern const struct hal_gpio_pin HAL_GPIO_PIN_P_0_18;
extern const struct hal_gpio_pin HAL_GPIO_PIN_P_1_27;
extern const struct hal_gpio_pin HAL_GPIO_PIN_P_2_5;
