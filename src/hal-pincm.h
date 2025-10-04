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

enum hal_pinsel_reg {
	HAL_PINSEL_REG_PINSEL0 = 0,
	HAL_PINSEL_REG_PINSEL1 = 1,
	HAL_PINSEL_REG_PINSEL2 = 2,
	HAL_PINSEL_REG_PINSEL3 = 3,
	HAL_PINSEL_REG_PINSEL4 = 4,
	HAL_PINSEL_REG_PINSEL7 = 7,
	HAL_PINSEL_REG_PINSEL8 = 8,
	HAL_PINSEL_REG_PINSEL9 = 9,
	HAL_PINSEL_REG_PINSEL10 = 10,
	HAL_PINSEL_REG_NUM
};

enum hal_pinmode_reg {
	HAL_PINMODE_REG_PINMODE0 = 0,
	HAL_PINMODE_REG_PINMODE1 = 1,
	HAL_PINMODE_REG_PINMODE2 = 2,
	HAL_PINMODE_REG_PINMODE3 = 3,
	HAL_PINMODE_REG_PINMODE4 = 4,
	HAL_PINMODE_REG_PINMODE5 = 5,
	HAL_PINMODE_REG_PINMODE6 = 6,
	HAL_PINMODE_REG_PINMODE7 = 7,
	HAL_PINMODE_REG_PINMODE9 = 9,
	HAL_PINMODE_REG_NUM
};

enum hal_pinmode_resistor {
	HAL_PINMODE_RESISTOR_PULL_UP = 0,
	HAL_PINMODE_RESISTOR_REPEATER = 1,
	HAL_PINMODE_RESISTOR_NONE = 2,
	HAL_PINMODE_RESISTOR_PULL_DOWN = 3
};

enum hal_pinsel_func {
	HAL_PINSEL_FUNC_GPIO = 0,

	HAL_PINSEL_FUNC_P_0_15_SCK0 = 2,
	HAL_PINSEL_FUNC_P_0_16_SSEL0 = 2,
	HAL_PINSEL_FUNC_P_0_17_MISO0 = 2,
	HAL_PINSEL_FUNC_P_0_18_MOSI0 = 2,

	HAL_PINSEL_FUNC_P_1_27_CLKOUT = 1
};

struct hal_pincm {
	volatile u32 PINSEL[HAL_PINSEL_REG_NUM];

	const u32 pad0[5];

	volatile u32 PINMODE[HAL_PINMODE_REG_NUM];
};

void hal_pincm_set_func(enum hal_pinsel_reg reg, u32 pinsel_mask,
			enum hal_pinsel_func func);

void hal_pincm_set_resistor(enum hal_pinmode_reg reg, u32 pinmode_mask,
			    enum hal_pinmode_resistor resistor);

static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL0], 0x0);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL1], 0x4);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL2], 0x8);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL3], 0xC);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL4], 0x10);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL7], 0x1C);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL8], 0x20);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL9], 0x24);
static_assert_offset(struct hal_pincm, PINSEL[HAL_PINSEL_REG_PINSEL10], 0x28);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE0], 0x40);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE1], 0x44);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE2], 0x48);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE3], 0x4C);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE4], 0x50);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE5], 0x54);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE6], 0x58);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE7], 0x5C);
static_assert_offset(struct hal_pincm, PINMODE[HAL_PINMODE_REG_PINMODE9], 0x64);
