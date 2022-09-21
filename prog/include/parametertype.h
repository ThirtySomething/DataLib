#pragma once
// *****************************************************************************
/**
 * @enum _ParameterType
 * @typedef ParameterType
 * @brief Defines various data types.
 * @see https://www.geeksforgeeks.org/data-types-in-c/
 *
 * Defines various data types used to address data in a parameterdata union.
 */
typedef enum _ParameterType
{
    PT_BYTE1 = 1,   ///< 1 byte
    PT_BYTE2 = 2,   ///< 2 bytes
    PT_BYTE4 = 4,   ///< 4 bytes
    PT_BYTE8 = 8,   ///< 8 bytes
    PT_BYTE16 = 16, ///< 16 bytes
    PT_LAST = 32    ///< Defines the last entry, only for internal use
} ParameterType;
// *****************************************************************************
