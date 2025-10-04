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

#define SR_BIT_TFE (BIT_0)
#define SR_BIT_TNF (BIT_1)
#define SR_BIT_RNE (BIT_2)
#define SR_BIT_RFF (BIT_3)
#define SR_BIT_BSY (BIT_4)

#define CR0_SCR_MASK \
	(BIT_15 | BIT_14 | BIT_13 | BIT_12 | BIT_11 | BIT_10 | BIT_9 | BIT_8)

#define CPSR_CPSDVSR_MASK \
	(BIT_7 | BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)

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
	if (cpol == HAL_SPI_CFG_MOTO_SPI_CPOL_LOW)
		spi_instances[inst].hw->CR0 &= ~CR0_BIT_CPOL;
	else if (cpol == HAL_SPI_CFG_MOTO_SPI_CPOL_HIGH)
		spi_instances[inst].hw->CR0 |= CR0_BIT_CPOL;
	else
		UNREACHABLE;
}

static void moto_spi_cpha_mode_set(const enum hal_spi_instance inst,
				   const enum hal_spi_cfg_moto_spi_cpha cpha)
{
	if (cpha == HAL_SPI_CFG_MOTO_SPI_CPHA_FIRST)
		spi_instances[inst].hw->CR0 &= ~CR0_BIT_CPHA;
	else if (cpha == HAL_SPI_CFG_MOTO_SPI_CPHA_SECOND)
		spi_instances[inst].hw->CR0 |= CR0_BIT_CPHA;
	else
		UNREACHABLE;
}

void hal_spi_init_moto_master(const enum hal_spi_instance inst,
			      const struct hal_spi_cfg_moto_master *const cfg)
{
	// The two SSP interfaces, SSP0 and SSP1 are configured using the
	// following registers:

	// 1. Power: In the PCONP register, set bit PCSSP0 to enable SSP0 and
	//    bit PCSSP1 to enable SSP1.
	hal_sysctl_periph_pwr_en(spi_instances[inst].pconp_bit);

	// 2. Clock: In PCLKSEL0 select PCLK_SSP1; in PCLKSEL1 select PCLK_SSP0.
	//    In master mode, the clock must be scaled down.
	set_val_by_mask(*spi_instances[inst].pclksel_reg,
			spi_instances[inst].pclksel_mask, cfg->clk_speed);

	// 3. Pins: Select the SSP pins through the PINSEL registers and pin
	//    modes through the PINMODE registers.
	//
	// The application is responsible for this step.

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
	set_val_by_mask(spi_instances[inst].hw->CR0, CR0_SCR_MASK,
			cfg->serial_clk_rate);

	set_val_by_mask(spi_instances[inst].hw->CPSR, CPSR_CPSDVSR_MASK,
			cfg->prescaler);

	moto_spi_cpol_mode_set(inst, cfg->cpol);
	moto_spi_cpha_mode_set(inst, cfg->cpha);

	spi_instances[inst].hw->CR1 &= ~CR1_BIT_MS;

	spi_instances[inst].hw->CR1 |= CR1_BIT_SSE;
}

void hal_spi_tx_blocking(const enum hal_spi_instance inst, const u16 *const src,
			 const u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		while (!(spi_instances[inst].hw->SR & SR_BIT_TNF))
			hal_no_op();

		spi_instances[inst].hw->DR = src[i];
	}

	while (spi_instances[inst].hw->SR & SR_BIT_BSY)
		hal_no_op();

	while (spi_instances[inst].hw->SR & SR_BIT_RNE)
		spi_instances[inst].hw->DR;
}

void hal_spi_tx_rx_blocking(const enum hal_spi_instance inst, const u16 *src,
			    u16 *const dst, const u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		while (!(spi_instances[inst].hw->SR & SR_BIT_TNF))
			hal_no_op();

		spi_instances[inst].hw->DR = src[i];
	}

	while (spi_instances[inst].hw->SR & SR_BIT_BSY)
		hal_no_op();

	u32 i = 0;
	while (spi_instances[inst].hw->SR & SR_BIT_RNE)
		dst[i++] = spi_instances[inst].hw->DR;
}
