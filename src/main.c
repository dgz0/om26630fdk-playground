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

#include "hal-spi.h"
#include "hal.h"

int main(void)
{
	hal_init();

	static const struct hal_spi_cfg_moto_spi_master_three_wire cfg = {
		.clk_rate	= mhz_to_hz(8),
		.data_size	= HAL_SPI_DATA_SIZE_8BIT,
		.cpol		= HAL_SPI_CFG_MOTO_SPI_CPOL_LOW,
		.cpha		= HAL_SPI_CFG_MOTO_SPI_CPHA_FIRST
	};

	hal_spi_init_moto_spi_master_three_wire(HAL_SPI_INSTANCE_SPI0, &cfg);

	for (;;) {
		asm("nop");
	}
	return 0;
}
