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

#include "hal-pincm.h"

#define HAL_PINCM ((struct hal_pincm *const)(0x4002C000))

void hal_pincm_set_func(const enum hal_pinsel_reg reg, const u32 pinsel_mask,
			const enum hal_pinsel_func func)
{
	set_val_by_mask(HAL_PINCM->PINSEL[reg], pinsel_mask, func);
}

void hal_pincm_set_resistor(const enum hal_pinmode_reg reg,
			    const u32 pinmode_mask,
			    const enum hal_pinmode_resistor resistor)
{
	set_val_by_mask(HAL_PINCM->PINMODE[reg], pinmode_mask, resistor);
}
