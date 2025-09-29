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
#include "hal-sysctl.h"

#define CR0_DSS_MASK (BIT_0 | BIT_1 | BIT_2 | BIT_3)

#define CR0_BIT_CPOL (BIT_6)
#define CR0_BIT_CPHA (BIT_7)

#define CR1_BIT_SSE (BIT_1)
#define CR1_BIT_MS (BIT_2)

enum cr0_frf {
	CR0_FRF_SPI = 0,
	CR0_FRF_TI = 1,
	CR0_FRF_MICROWIRE = 2,
	CR0_FRF_MASK = BIT_5 | BIT_4,
};

static struct {
	struct hal_spi_hw *const hw;
	const enum hal_sysctl_pconp_bit pconp_bit;
	volatile u32 *const pclksel_reg;
	const enum hal_sysctl_pclksel_mask pclksel_mask;
} spi_instances[] = {
	// clang-format off

	[HAL_SPI_INSTANCE_SPI0] = {
		.hw		= HAL_SSP0,
		.pconp_bit	= HAL_SYSCTL_PCONP_BIT_PCSSP0,
		.pclksel_reg	= &HAL_SYSCTL->PCLKSEL1,
		.pclksel_mask	= HAL_SYSCTL_PCLKSEL1_MASK_PCLK_SSP0
	},

	[HAL_SPI_INSTANCE_SPI1] = {
		.hw		= HAL_SSP1,
		.pconp_bit	= HAL_SYSCTL_PCONP_BIT_PCSSP1,
		.pclksel_reg	= &HAL_SYSCTL->PCLKSEL0,
		.pclksel_mask	= HAL_SYSCTL_PCLKSEL0_MASK_PCLK_SSP1
	}

	// clang-format on
};

static void isr_SSP0(void)
{
}

static void isr_SSP1(void)
{
}

static void moto_spi_cpol_mode_set(const enum hal_spi_instance inst,
				   const enum hal_spi_cfg_moto_spi_cpol cpol)
{
	if (cpol == HAL_SPI_CFG_MOTO_SPI_CPOL_LOW) {
		spi_instances[inst].hw->CR0 &= ~CR0_BIT_CPOL;
	} else if (cpol == HAL_SPI_CFG_MOTO_SPI_CPOL_HIGH) {
		spi_instances[inst].hw->CR0 |= CR0_BIT_CPOL;
	} else {
		UNREACHABLE;
	}
}

static void moto_spi_cpha_mode_set(const enum hal_spi_instance inst,
				   const enum hal_spi_cfg_moto_spi_cpha cpha)
{
	if (cpha == HAL_SPI_CFG_MOTO_SPI_CPHA_FIRST) {
		spi_instances[inst].hw->CR0 &= ~CR0_BIT_CPHA;
	} else if (cpha == HAL_SPI_CFG_MOTO_SPI_CPHA_SECOND) {
		spi_instances[inst].hw->CR0 |= CR0_BIT_CPHA;
	} else {
		UNREACHABLE;
	}
}

void hal_spi_init_moto_spi_master_three_wire(
	const enum hal_spi_instance inst,
	const struct hal_spi_cfg_moto_spi_master_three_wire *const cfg)
{
	// The two SSP interfaces, SSP0 and SSP1 are configured using the
	// following registers:

	// 1. Power: In the PCONP register, set bit PCSSP0 to enable SSP0 and
	//    bit PCSSP1 to enable SSP1.
	hal_sysctl_periph_pwr_en(spi_instances[inst].pconp_bit);

	// 2. Clock: In PCLKSEL0 select PCLK_SSP1; in PCLKSEL1 select PCLK_SSP0.
	//    In master mode, the clock must be scaled down.
	// XXX: Determine the correct clock configuration based on the
	;

	// 3. Pins: Select the SSP pins through the PINSEL registers and pin
	//    modes through the PINMODE registers.
	//
	// The application is responsible for this step.
	;

	// 4. Interrupts: Interrupts are enabled in the SSP0IMSC register for
	//    SSP0 and SSP1IMSC register for SSP1. Interrupts are enabled in the
	//    NVIC using the appropriate Interrupt Set Enable register
	;

	// 5. Initialization: There are two control registers for each of the
	//    SSP ports to be configured: SSP0CR0 and SSP0CR1 for SSP0, SSP1CR0
	//    and SSP1CR1 for SSP1.
	set_val_by_mask(spi_instances[inst].hw->CR0, CR0_DSS_MASK,
			cfg->data_size);

	set_val_by_mask(spi_instances[inst].hw->CR0, CR0_FRF_MASK, CR0_FRF_SPI);
	moto_spi_cpol_mode_set(inst, cfg->cpol);
	moto_spi_cpha_mode_set(inst, cfg->cpha);

	// serial clock rate

	spi_instances[inst].hw->CR1 &= ~CR1_BIT_MS;

	// 6. DMA: The Rx and Tx FIFOs of the SSP interfaces can be connected to
	//    the GPDMA controller. For GPDMA system connections
	;

	spi_instances[inst].hw->CR1 |= CR1_BIT_SSE;
}
