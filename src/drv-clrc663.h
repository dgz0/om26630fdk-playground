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

#include <stdint.h>

enum drv_clrc663_reg {
	/** Starts and stops command execution */
	DRV_CLRC663_REG_Command = 0x00,

	/** Host control register */
	DRV_CLRC663_REG_HostCtrl = 0x01,

	/** Control register of the FIFO */
	DRV_CLRC663_REG_FIFOControl = 0x02,

	/** Level of the FIFO underflow and overflow warning */
	DRV_CLRC663_REG_WaterLevel = 0x03,

	/** Length of the FIFO */
	DRV_CLRC663_REG_FIFOLength = 0x04
};

void drv_clrc663_init(void);

uint8_t drv_clrc663_reg_read(enum drv_clrc663_reg reg);

void drv_clrc663_reg_write(enum drv_clrc663_reg reg, uint8_t val);
