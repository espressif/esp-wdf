// Copyright 2022 Espressif Systems (Shanghai) PTE LTD
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

#ifndef __ESP_ATTR_H__
#define __ESP_ATTR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"

#define ROMFN_ATTR

//Normally, the linker script will put all code and rodata in flash,
//and all variables in shared RAM. These macros can be used to redirect
//particular functions/variables to other memory regions.

// Forces code into IRAM instead of flash
#define IRAM_ATTR

// Forces data into DRAM instead of flash
#define DRAM_ATTR

// IRAM can only be accessed as an 8-bit memory on ESP32, when CONFIG_ESP32_IRAM_AS_8BIT_ACCESSIBLE_MEMORY is set
#define IRAM_8BIT_ACCESSIBLE 0

#define COREDUMP_IRAM_DATA_ATTR COREDUMP_DRAM_ATTR
#define IRAM_DATA_ATTR
#define IRAM_BSS_ATTR

// Forces data to be 4 bytes aligned
#define WORD_ALIGNED_ATTR __attribute__((aligned(4)))

// Forces data to be placed to DMA-capable places
#define DMA_ATTR WORD_ALIGNED_ATTR DRAM_ATTR

// Forces a function to be inlined
#define FORCE_INLINE_ATTR static inline __attribute__((always_inline))

// Forces a string into DRAM instead of flash
// Use as esp_rom_printf(DRAM_STR("Hello world!\n"));
#define DRAM_STR(str) (__extension__({static const DRAM_ATTR char __c[] = (str); (const char *)&__c;}))

#define RTC_DATA_ATTR
#define RTC_NOINIT_ATTR
#define RTC_RODATA_ATTR
#define COREDUMP_RTC_DATA_ATTR
#define RTC_SLOW_ATTR
#define RTC_IRAM_ATTR
#define RTC_FAST_ATTR
#define COREDUMP_RTC_FAST_ATTR

#define EXT_RAM_BSS_ATTR

/**
 * Deprecated Macro for putting .bss on PSRAM
 */
#define EXT_RAM_ATTR

#define EXT_RAM_NOINIT_ATTR

// Forces code into DRAM instead of flash and map it to coredump
// Use dram2 instead of dram1 to make sure this section will not be included
// by dram1 section in the linker script
#define COREDUMP_DRAM_ATTR

// Forces to not inline function
#define NOINLINE_ATTR __attribute__((noinline))

// This allows using enum as flags in C++
// Format: FLAG_ATTR(flag_enum_t)
#ifdef __cplusplus

// Inline is required here to avoid multiple definition error in linker
#define FLAG_ATTR_IMPL(TYPE, INT_TYPE) \
FORCE_INLINE_ATTR constexpr TYPE operator~ (TYPE a) { return (TYPE)~(INT_TYPE)a; } \
FORCE_INLINE_ATTR constexpr TYPE operator| (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a | (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator& (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a & (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator^ (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a ^ (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator>> (TYPE a, int b) { return (TYPE)((INT_TYPE)a >> b); } \
FORCE_INLINE_ATTR constexpr TYPE operator<< (TYPE a, int b) { return (TYPE)((INT_TYPE)a << b); } \
FORCE_INLINE_ATTR TYPE& operator|=(TYPE& a, TYPE b) { a = a | b; return a; } \
FORCE_INLINE_ATTR TYPE& operator&=(TYPE& a, TYPE b) { a = a & b; return a; } \
FORCE_INLINE_ATTR TYPE& operator^=(TYPE& a, TYPE b) { a = a ^ b; return a; } \
FORCE_INLINE_ATTR TYPE& operator>>=(TYPE& a, int b) { a = a >> b; return a; } \
FORCE_INLINE_ATTR TYPE& operator<<=(TYPE& a, int b) { a = a << b; return a; }

#define FLAG_ATTR_U32(TYPE) FLAG_ATTR_IMPL(TYPE, uint32_t)
#define FLAG_ATTR FLAG_ATTR_U32

#else
#define FLAG_ATTR(TYPE)
#endif

/* Use IDF_DEPRECATED attribute to mark anything deprecated from use in
   ESP-IDF's own source code, but not deprecated for external users.
*/
#ifdef IDF_CI_BUILD
#define IDF_DEPRECATED(REASON) __attribute__((deprecated(REASON)))
#else
#define IDF_DEPRECATED(REASON)
#endif

#ifdef __cplusplus
}
#endif
#endif /* __ESP_ATTR_H__ */
