#pragma once
// *****************************************************************************
#include <stdbool.h>
#include <stddef.h>
// *****************************************************************************
#include "endianness.h"
#include "parameterdata.h"
// *****************************************************************************
/**
 * @brief Determine systems endianness
 * @see https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 *
 * @return true System uses little endian notation.
 * @return false System does not use little endian notation.
 */
bool isSystemLittleEndian(void);
// *****************************************************************************
/**
 * @brief Change endianess of 16 bits/2 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return int16_t Changed input value
 */
int16_t swapBytes_i16(int16_t value);
// *****************************************************************************
/**
 * @brief Change endianess of 16 bits/2 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return uint16_t Changed input value
 */
uint16_t swapBytes_ui16(uint16_t value);
// *****************************************************************************
/**
 * @brief Change endianess of 32 bits/4 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return int32_t Changed input value
 */
int32_t swapBytes_i32(int32_t value);
// *****************************************************************************
/**
 * @brief Change endianess of 32 bits/4 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return uint32_t Changed input value
 */
uint32_t swapBytes_ui32(uint32_t value);
// *****************************************************************************
/**
 * @brief Change endianess of 64 bits/8 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return int64_t Changed input value
 */
int64_t swapBytes_i64(int64_t value);
// *****************************************************************************
/**
 * @brief Change endianess of 64 bits/8 bytes
 * @see https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
 *
 * @param value Value to change endianness
 * @return uint64_t Changed input value
 */
uint64_t swapBytes_ui64(uint64_t value);
// *****************************************************************************
/**
 * @brief Change endianness of element in object
 * @see https://www.techiedelight.com/reverse-array-c/
 *
 * @param object Parameter union
 * @param type Parameter type
 * @param position Position of parameter
 * @return true Endianness changed
 * @return false Endianness not changed
 */
bool changeEndianness(ParameterData *object, ParameterType type, size_t position);
// *****************************************************************************
