#pragma once
// *****************************************************************************
#include <stdint.h>
// *****************************************************************************
#include "parametertype.h"
// *****************************************************************************
/**
 * @union _ParameterData
 * @typedef ParameterData
 * @brief A datablock to keep various data.
 * @see https://www.geeksforgeeks.org/data-types-in-c/
 * @see https://en.wikibooks.org/wiki/C_Programming/stdint.h
 *
 * This is a datablock to keep either
 * - 2 int64_t/uint64_t
 * - 4 int32_t/uint32_t
 * - 8 int16_t/uint16_t
 * - 16 int8_t/uint8_t
 */
typedef union _ParameterData
{
    //--- 8 bytes
    int64_t val_i64[PT_BYTE2];   //!< int64_t value, array of 2 (2*8 bytes)
    uint64_t val_ui64[PT_BYTE2]; //!< uint64_t value, array of 2 (2*8 bytes)

    //--- 4 bytes
    int32_t val_i32[PT_BYTE4];   //!< int32_t value, array of 4 (4*4 bytes)
    uint32_t val_ui32[PT_BYTE4]; //!< uint32_t value, array of 4 (4*4 bytes)

    //--- 2 bytes
    int16_t val_i16[PT_BYTE8];   //!< int16_t value, array of 8 (8*2 bytes)
    uint16_t val_ui16[PT_BYTE8]; //!< uint16_t value, array of 8 (8*2 bytes)

    //--- 1 bytes
    int8_t val_i8[PT_BYTE16];   //!< int8_t value, array of 16 (16*1 bytes)
    uint8_t val_ui8[PT_BYTE16]; //!< uint8_t value, array of 16 (16*1 bytes)
} ParameterData;
// *****************************************************************************
