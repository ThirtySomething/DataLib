#pragma once
// *****************************************************************************
/**
 * @brief Test settings of endianness
 *
 */
void t_storageEndianness(void);
// *****************************************************************************
/**
 * @brief Test switching of bytes based on system settings of endianness
 *
 */
void t_storageEndiannessToggle(void);
// *****************************************************************************
/**
 * @brief Test determination of memory size
 *
 * Test calculation of used memory.
 */
void t_storageGetTotalSize(void);
// *****************************************************************************
/**
 * @brief Test access to full ParameterData elements in storage
 *
 * Test of reading/writing element direct to storage
 */
void t_storageXetElement(void);
// *****************************************************************************
/**
 * @brief Test initialization, release and resize of storage
 *
 * Test initialization, release and resize of storage
 */
void t_storageSize(void);
// *****************************************************************************
