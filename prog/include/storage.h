#pragma once
// *****************************************************************************
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
// *****************************************************************************
#include "endianness.h"
#include "parameterdata.h"
// *****************************************************************************
extern const uint32_t PARAMETER_END;
extern const uint32_t PARAMETER_START;
// *****************************************************************************
/**
 * @brief Get the System Endianness setting
 * @see https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 * @see endianness.h
 *
 * Get the System Endianness setting.
 *
 * @return Endianness
 */
Endianness getStorageEndianness(void);
// *****************************************************************************
/**
 * @brief Set the System Endianness type
 *
 * Try to set the endian settings. Note: This could be done only on non
 * initialize systems. On running systems this is not possible.
 *
 * @param endianness Kind of endian
 * @return true Successful set type of endian setting.
 * @return false Failed to set type of endian setting.
 */
bool setStorageEndianness(Endianness endianness);
// *****************************************************************************
/**
 * @brief Get size of used memory in bytes
 * @see storageInitialize
 *
 * Determines the total used memory in bytes. A size of 0 means, storage is
 * not initialized.
 *
 * @return size_t Allocated memory in bytes
 *
 * Note: Allocated memory is not equal to the real used memory. The maximum
 * available memory is size with 16 bytes. 8 bytes are used as memory start
 * marker, 8 bytes are used as memory end marker.
 */
size_t storageGetSize(void);
// *****************************************************************************
/**
 * @brief Initalize storage
 * @see storageIsInitialized
 * @see storageGetSize
 * @see ParameterData
 *
 * Performs memory initialization.
 *
 * @param initialSize Initial size of ParameterData elements
 * @return true Initialization successful.
 * @return false Failure in initialization.
 */
bool storageInitialize(size_t initialSize);
// *****************************************************************************
/**
 * @brief Resize storage
 *
 * @param newSize new storage size in amount of ParameterData elements
 * @return true Resize successful.
 * @return false Failure in resize.
 */
bool storageResize(size_t newSize);
// *****************************************************************************
/**
 * @brief Reset of storage, free memory
 */
void storageRelease(void);
// *****************************************************************************
/**
 * @brief Returns status of storage
 *
 * @return true Storage is initialized
 * @return false Storage not initialized
 */
bool storageIsInitialized(void);
// *****************************************************************************
/**
 * @brief Check for allowed index
 *
 * @param index Index to check
 * @return true Index is allowed
 * @return false Index is not allowed
 */
bool storageIsValidIndexPartial(size_t index);
// *****************************************************************************
/**
 * @brief Check for allowed index
 *
 * @param index Index to check
 * @return true Index is allowed
 * @return false Index is not allowed
 */
bool storageIsValidIndexFull(size_t index);
// *****************************************************************************
/**
 * @brief Check for allowed index and given parameter
 *
 * @param parameter Parameter to check
 * @param index Index to check
 * @return true Index is allowed
 * @return false Index is not allowed
 */
bool storageIsValidIndex(ParameterType parameter, size_t index);
// *****************************************************************************
/**
 * @brief Check for allowed position for given index and position
 *
 * @param index Index to check
 * @param position Position to check
 * @param full Size of one element
 * @return true Position is allowed
 * @return false Position is not allowed
 */
bool storageIsValidPositionPartial(size_t index, size_t position, ParameterType full);
// *****************************************************************************
/**
 * @brief Check for allowed position for given index and position
 *
 * @param index Index to check
 * @param position Position to check
 * @return true Position is allowed
 * @return false Position is not allowed
 */
bool storageIsValidPositionFull(size_t index, size_t position);
// *****************************************************************************
/**
 * @brief Check for allowed position for given parameter, index and position
 *
 * @param parameter Parameter to check
 * @param index Index to check
 * @param position Position to check
 * @return true Position is allowed
 * @return false Position is not allowed
 */
bool storageIsValidPosition(ParameterType parameter, size_t index, size_t position);
// *****************************************************************************
/**
 * @brief Check function to proof given index/position of passed parameter
 *
 * @param parameter Parameter to check
 * @param index Index, part of address, will be checked
 * @param position Position, part of address, will be checked
 * @return true parameter and index are valid combination
 * @return false parameter and index are invalid combination
 */
bool storageIsValidAddress(ParameterType parameter, size_t index, size_t position);
// *****************************************************************************
/**
 * @brief Get full parameter data element at given index and write to destination
 *
 * @param index Index to get element from
 * @param destination Destination, copy of element at index
 * @return true Successful copy
 * @return false Assignment failed
 */
bool storageGetElement(size_t index, ParameterData *destination);
// *****************************************************************************
/**
 * @brief Set full parameter data element at given index
 *
 * @param index Index to get element from
 * @param source Source, will be copied to element at index
 * @return true Successful copy
 * @return false Assignment failed
 */
bool storageSetElement(size_t index, ParameterData source);
// *****************************************************************************
/**
 * @brief Read a long long value from storage
 *
 * @param index Index of long long in storage
 * @param position Position of long long in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ll(size_t index, size_t position, long long *value);
// *****************************************************************************
/**
 * @brief Write a long long value to storage
 *
 * @param index Index of long long in storage
 * @param position Position of long long in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ll(size_t index, size_t position, long long value);
// *****************************************************************************
/**
 * @brief Read a unsigned long long value from storage
 *
 * @param index Index of unsigned long long in storage
 * @param position Position of unsigned long long in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ull(size_t index, size_t position, unsigned long long *value);
// *****************************************************************************
/**
 * @brief Write a unsigned long long value to storage
 *
 * @param index Index of unsigned long long in storage
 * @param position Position of unsigned long long in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ull(size_t index, size_t position, unsigned long long value);
// *****************************************************************************
/**
 * @brief Read a int64_t value from storage
 *
 * @param index Index of int64_t in storage
 * @param position Position of int64_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_i64(size_t index, size_t position, int64_t *value);
// *****************************************************************************
/**
 * @brief Write a int64_t value to storage
 *
 * @param index Index of int64_t in storage
 * @param position Position of int64_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_i64(size_t index, size_t position, int64_t value);
// *****************************************************************************
/**
 * @brief Read a uint64_t value to storage
 *
 * @param index Index of uint64_t in storage
 * @param position Position of uint64_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ui64(size_t index, size_t position, uint64_t *value);
// *****************************************************************************
/**
 * @brief Write a uint64_t value to storage
 *
 * @param index Index of uint64_t in storage
 * @param position Position of uint64_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ui64(size_t index, size_t position, uint64_t value);
// *****************************************************************************
/**
 * @brief Read a int32_t value to storage
 *
 * @param index Index of int32_t in storage
 * @param position Position of int32_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_i32(size_t index, size_t position, int32_t *value);
// *****************************************************************************
/**
 * @brief Write a int32_t value to storage
 *
 * @param index Index of int32_t in storage
 * @param position Position of int32_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_i32(size_t index, size_t position, int32_t value);
// *****************************************************************************
/**
 * @brief Read a uint32_t value to storage
 *
 * @param index Index of uint32_t in storage
 * @param position Position of uint32_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ui32(size_t index, size_t position, uint32_t *value);
// *****************************************************************************
/**
 * @brief Write a uint32_t value to storage
 *
 * @param index Index of uint32_t in storage
 * @param position Position of uint32_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ui32(size_t index, size_t position, uint32_t value);
// *****************************************************************************
/**
 * @brief Read a short value to storage
 *
 * @param index Index of short in storage
 * @param position Position of short in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_s(size_t index, size_t position, short *value);
// *****************************************************************************
/**
 * @brief Write a short value to storage
 *
 * @param index Index of short in storage
 * @param position Position of short in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_s(size_t index, size_t position, short value);
// *****************************************************************************
/**
 * @brief Read a short unsigned value to storage
 *
 * @param index Index of unsigned short in storage
 * @param position Position of unsigned short in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_us(size_t index, size_t position, unsigned short *value);
// *****************************************************************************
/**
 * @brief Write a short unsigned value to storage
 *
 * @param index Index of unsigned short in storage
 * @param position Position of unsigned short in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_us(size_t index, size_t position, unsigned short value);
// *****************************************************************************
/**
 * @brief Read a int16_t value to storage
 *
 * @param index Index of int16_t in storage
 * @param position Position of int16_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_i16(size_t index, size_t position, int16_t *value);
// *****************************************************************************
/**
 * @brief Write a int16_t value to storage
 *
 * @param index Index of int16_t in storage
 * @param position Position of int16_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_i16(size_t index, size_t position, int16_t value);
// *****************************************************************************
/**
 * @brief Read a uint16_t value to storage
 *
 * @param index Index of uint16_t in storage
 * @param position Position of uint16_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ui16(size_t index, size_t position, uint16_t *value);
// *****************************************************************************
/**
 * @brief Write a uint16_t value to storage
 *
 * @param index Index of uint16_t in storage
 * @param position Position of uint16_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ui16(size_t index, size_t position, uint16_t value);
// *****************************************************************************
/**
 * @brief Read a char value to storage
 *
 * @param index Index of char in storage
 * @param position Position of char in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_c(size_t index, size_t position, char *value);
// *****************************************************************************
/**
 * @brief Write a char value to storage
 *
 * @param index Index of char in storage
 * @param position Position of char in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_c(size_t index, size_t position, char value);
// *****************************************************************************
/**
 * @brief Read a unsigned char value to storage
 *
 * @param index Index of unsigned char in storage
 * @param position Position of unsigned char in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_uc(size_t index, size_t position, unsigned char *value);
// *****************************************************************************
/**
 * @brief Read a int8_t value to storage
 *
 * @param index Index of int8_t in storage
 * @param position Position of int8_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_i8(size_t index, size_t position, int8_t *value);
// *****************************************************************************
/**
 * @brief Write a int8_t value to storage
 *
 * @param index Index of int8_t in storage
 * @param position Position of int8_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_i8(size_t index, size_t position, int8_t value);
// *****************************************************************************
/**
 * @brief Read a uint8_t value to storage
 *
 * @param index Index of uint8_t in storage
 * @param position Position of uint8_t in storage
 * @param value Destination of stored value
 * @return true Success reading
 * @return false Failure reading
 */
bool storageRead_ui8(size_t index, size_t position, uint8_t *value);
// *****************************************************************************
/**
 * @brief Write a uint8_t value to storage
 *
 * @param index Index of uint8_t in storage
 * @param position Position of uint8_t in storage
 * @param value Value to store
 * @return true Success writing
 * @return false Failure writing
 */
bool storageWrite_ui8(size_t index, size_t position, uint8_t value);
// *****************************************************************************
/**
 * @brief Load storage data from file
 *
 * NOTE: You cannot load storage data as long as the storage is initialized!
 *
 * @param filename Name of stored data
 * @return true Load successul
 * @return false Failure loading storage data
 */
bool storageLoad(char *filename);
// *****************************************************************************
/**
 * @brief Save storage data to file
 *
 * @param filename Name of stored data
 * @return true Save successful
 * @return false Failure saving storage data
 */
bool storageSave(char *filename);
// *****************************************************************************
