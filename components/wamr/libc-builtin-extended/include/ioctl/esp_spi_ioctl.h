// Copyright 2023 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SPICBASE               (0x8300) /*!< SPI ioctl command basic value */
#define _SPIC(nr)               (_SPICBASE | (nr)) /*!< SPI ioctl command macro */

/**
 * @brief SPI ioctl commands.
 */
#define SPIIOCSCFG              _SPIC(0x0001) /*!< Set SPI configuration */
#define SPIIOCEXCHANGE          _SPIC(0x0002) /*!< SPI master exchange data with slave */

/**
 * @brief SPI configuration flag
 */
#define SPI_MASTER              (1 << 0)  /*!< Enable master mode */
#define SPI_MODE(x)             (((x) & 0x3) << 1) /*!< SPI mode setting */
#define SPI_RX_LSB              (1 << 3)  /*!< Set RX data bit sequence least significant bit first */
#define SPI_TX_LSB              (1 << 4)  /*!< Set TX data bit sequence least significant bit first */

/**
 * @brief SPI configuration mode
 */
#define SPI_MODE_0              SPI_MODE(0) /*!< SPI mode 0 */
#define SPI_MODE_1              SPI_MODE(1) /*!< SPI mode 1 */
#define SPI_MODE_2              SPI_MODE(2) /*!< SPI mode 2 */
#define SPI_MODE_3              SPI_MODE(3) /*!< SPI mode 3 */

/**
 * @brief SPI configuration.
 */
typedef struct spi_cfg {
    uint8_t cs_pin;   /*!< SPI CS pin number */
    uint8_t sclk_pin; /*!< SPI clock pin number */
    uint8_t mosi_pin; /*!< SPI MOSI pin number */
    uint8_t miso_pin; /*!< SPI MISO pin number */

    union {
        struct {
            uint32_t master     :  1; /*!< 1: master mode, 0: slave mode */
            uint32_t mode       :  2; /*!< SPI mode setting */
            uint32_t rx_lsb     :  1; /*!< RX data bit sequence, 1: least significant bit first, 0: most significant bit first */
            uint32_t tx_lsb     :  1; /*!< TX data bit sequence, 1: least significant bit first, 0: most significant bit first */
        } flags_data;
        uint32_t flags; /*!< SPI configuration flags */
    };

    union {
        struct {
            uint32_t clock; /*!< SPI master clock frequency HZ */
        } master;
    };
} spi_cfg_t;

/**
 * @brief SPI Exchange Message.
 */
typedef struct spi_ex_msg {
    const void  *tx_buffer; /*!< SPI write data pointer */
    void    *rx_buffer;     /*!< SPI read data pointer */
    uint32_t size;          /*!< Number of SPI transfer data size by byte */
} spi_ex_msg_t;

#ifdef __cplusplus
}
#endif
