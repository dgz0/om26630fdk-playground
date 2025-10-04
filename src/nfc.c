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

#include "nfc.h"
#include "hal-gpio.h"
#include "hal-spi.h"

#define PIN_SCK (&HAL_GPIO_PIN_P_0_15)
#define PIN_CS (&HAL_GPIO_PIN_P_0_16)
#define PIN_MISO (&HAL_GPIO_PIN_P_0_17)
#define PIN_MOSI (&HAL_GPIO_PIN_P_0_18)

#define PIN_CLRC_RST (&HAL_GPIO_PIN_P_2_5)

#define SPI_INST (HAL_SPI_INSTANCE_SPI0)

static void pin_init_spi_sck(void)
{
	static const struct hal_gpio_pin_cfg cfg = {
		.resistor	= HAL_PINMODE_RESISTOR_NONE,
		.pin_func	= HAL_PINSEL_FUNC_P_0_15_SCK0,
		.dir		= HAL_GPIO_PIN_DIR_AUTO
	};
	hal_gpio_pin_init(PIN_SCK, &cfg);
}

static void pin_init_spi_cs(void)
{
	static const struct hal_gpio_pin_cfg cfg = {
		.resistor	= HAL_PINMODE_RESISTOR_NONE,
		.pin_func	= HAL_PINSEL_FUNC_GPIO,
		.dir		= HAL_GPIO_PIN_DIR_OUTPUT
	};
	hal_gpio_pin_init(PIN_CS, &cfg);
}

static void pin_init_spi_miso(void)
{
	static const struct hal_gpio_pin_cfg cfg = {
		.resistor	= HAL_PINMODE_RESISTOR_NONE,
		.pin_func	= HAL_PINSEL_FUNC_P_0_17_MISO0,
		.dir		= HAL_GPIO_PIN_DIR_AUTO
	};
	hal_gpio_pin_init(PIN_MISO, &cfg);
}

static void pin_init_spi_mosi(void)
{
	static const struct hal_gpio_pin_cfg cfg = {
		.resistor	= HAL_PINMODE_RESISTOR_NONE,
		.pin_func	= HAL_PINSEL_FUNC_P_0_18_MOSI0,
		.dir		= HAL_GPIO_PIN_DIR_AUTO
	};
	hal_gpio_pin_init(PIN_MOSI, &cfg);
}

static void pin_init_clrc_rst(void)
{
	static const struct hal_gpio_pin_cfg cfg = {
		.resistor	= HAL_PINMODE_RESISTOR_NONE,
		.pin_func	= HAL_PINSEL_FUNC_GPIO,
		.dir		= HAL_GPIO_PIN_DIR_OUTPUT
	};
	hal_gpio_pin_init(PIN_CLRC_RST, &cfg);
}

static void pin_init(void)
{
	pin_init_spi_sck();
	pin_init_spi_cs();
	pin_init_spi_miso();
	pin_init_spi_mosi();
	pin_init_clrc_rst();
}

static void spi_init(void)
{
	static const struct hal_spi_cfg_moto_master cfg = {
		// clang-format off

		.clk_speed		= HAL_SYSCTL_PCLKSEL_CCLK_DIV_1,
		.data_size		= HAL_SPI_DATA_SIZE_8BIT,
		.cpol			= HAL_SPI_CFG_MOTO_SPI_CPOL_LOW,
		.cpha			= HAL_SPI_CFG_MOTO_SPI_CPHA_FIRST,
		.prescaler		= 12,
		.serial_clk_rate	= 0

		// clang-format on
	};
	hal_spi_init_moto_master(SPI_INST, &cfg);
}

void nfc_init(void)
{
	pin_init();
	spi_init();

	hal_gpio_pin_set_high(PIN_CS);
	hal_gpio_pin_set_low(PIN_CLRC_RST);

	static const uint16_t tx[2] = {
		[0] = (0x7F << 1) | 1,
		[1] = 0xDB
	};

	static u16 rx[2] = {};

	hal_gpio_pin_set_low(PIN_CS);
	hal_spi_tx_rx_blocking(SPI_INST, tx, rx, 2);
	hal_gpio_pin_set_high(PIN_CS);
}
