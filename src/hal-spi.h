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
#include "hal-sysctl.h"

#define HAL_SSP0 ((struct hal_spi_hw *const)(0x40088000))
#define HAL_SSP1 ((struct hal_spi_hw *const)(0x40030000))

struct hal_spi_hw {
	/**
	 * 0x0 - Control Register 0
	 *
	 * Selects the serial clock rate, bus type, and data size.
	 */
	volatile u32 CR0;

	/**
	 * 0x4 - Control Register 1
	 *
	 * Selects master/slave and other modes.
	 */
	volatile u32 CR1;

	/**
	 * 0x8 - Data Register
	 *
	 * Writes fill the transmit FIFO, and reads empty the receive FIFO.
	 */
	volatile u32 DR;

	/** 0xC - Status Register */
	volatile const u32 SR;

	/** 0x10 - Clock Prescale Register */
	volatile u32 CPSR;

	/** 0x14 - Interrupt Mask Set and Clear Register */
	volatile u32 IMSC;

	/** 0x18 - Raw Interrupt Status Register */
	volatile u32 RIS;

	/** 0x1C - Masked Interrupt Status Register */
	volatile u32 MIS;

	/** 0x20 -  SSPICR Interrupt Clear Register */
	volatile u32 ICR;

	/** 0x24 - DMA Control Register */
	volatile u32 DMACR;
};

static_assert_offset(struct hal_spi_hw, CR0, 0x0);
static_assert_offset(struct hal_spi_hw, CR1, 0x4);
static_assert_offset(struct hal_spi_hw, DR, 0x8);
static_assert_offset(struct hal_spi_hw, SR, 0xC);
static_assert_offset(struct hal_spi_hw, CPSR, 0x10);
static_assert_offset(struct hal_spi_hw, IMSC, 0x14);
static_assert_offset(struct hal_spi_hw, RIS, 0x18);
static_assert_offset(struct hal_spi_hw, MIS, 0x1C);
static_assert_offset(struct hal_spi_hw, ICR, 0x20);
static_assert_offset(struct hal_spi_hw, DMACR, 0x24);

enum hal_spi_instance { HAL_SPI_INSTANCE_SPI0 = 0, HAL_SPI_INSTANCE_SPI1 = 1 };

enum hal_spi_cfg_moto_spi_cpol {
	/** SSP controller maintains the bus clock low between frames. */
	HAL_SPI_CFG_MOTO_SPI_CPOL_LOW = 0,

	/** SSP controller maintains the bus clock high between frames. */
	HAL_SPI_CFG_MOTO_SPI_CPOL_HIGH = 1
};

enum hal_spi_cfg_moto_spi_cpha {
	/**
	 * SSP controller captures serial data on the first clock transition of
         * the frame, that is, the transition away from the inter-frame state
         * of the clock line.
         */
	HAL_SPI_CFG_MOTO_SPI_CPHA_FIRST = 0,

	/**
	 * SSP controller captures serial data on the second clock transition of
	 * the frame, that is, the transition back to the inter-frame state of
	 * the clock line.
	 */
	HAL_SPI_CFG_MOTO_SPI_CPHA_SECOND = 1
};

enum hal_spi_data_size {
	HAL_SPI_DATA_SIZE_4BIT = 3,
	HAL_SPI_DATA_SIZE_5BIT = 4,
	HAL_SPI_DATA_SIZE_6BIT = 5,
	HAL_SPI_DATA_SIZE_7BIT = 6,
	HAL_SPI_DATA_SIZE_8BIT = 7,
	HAL_SPI_DATA_SIZE_9BIT = 8,
	HAL_SPI_DATA_SIZE_10BIT = 9,
	HAL_SPI_DATA_SIZE_11BIT = 10,
	HAL_SPI_DATA_SIZE_12BIT = 11,
	HAL_SPI_DATA_SIZE_13BIT = 12,
	HAL_SPI_DATA_SIZE_14BIT = 13,
	HAL_SPI_DATA_SIZE_15BIT = 14,
	HAL_SPI_DATA_SIZE_16BIT = 15
};

struct hal_spi_cfg_moto_master {
	enum hal_sysctl_pclksel_clk clk_speed;
	enum hal_spi_data_size data_size;
	enum hal_spi_cfg_moto_spi_cpol cpol;
	enum hal_spi_cfg_moto_spi_cpha cpha;
	u8 prescaler;
	u8 serial_clk_rate;
};

void hal_spi_init_moto_master(enum hal_spi_instance inst,
			      const struct hal_spi_cfg_moto_master *cfg);

void hal_spi_tx_blocking(enum hal_spi_instance inst, const u16 *src, u32 size);

void hal_spi_tx_rx_blocking(enum hal_spi_instance inst, const u16 *src,
			    u16 *dst, u32 size);
