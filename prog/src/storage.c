// *****************************************************************************
#include <stdio.h>
// *****************************************************************************
#include "storage.h"
#include "converter.h"
#include "parameterdefinition.h"
// *****************************************************************************
/**
 * @brief Pointer to storage
 *
 */
static ParameterData *parameterList = NULL;
// *****************************************************************************
/**
 * @brief Size of storage
 *
 */
static size_t parameterListSize = 0;
// *****************************************************************************
/**
 * @brief Flags initialization status of storage
 *
 */
static bool isInitialized = false;
// *****************************************************************************
/**
 * @brief System endianness, by default it's E_ENDIANNESS_LITTLE
 * @see endianness.h
 *
 */
static Endianness systemEndianness = E_ENDIANNESS_LITTLE;
// *****************************************************************************
/**
 * @brief Marker of memory start
 *
 * Value is FEAFDEBA, in little endian you should see BADEAFFE.
 */
const uint32_t PARAMETER_START = 0xFEAFDEBA;
// *****************************************************************************
/**
 * @brief Marker of memory end
 *
 * Value is DEC0ADDE, in little endian you should see DEADC0DE.
 */
const uint32_t PARAMETER_END = 0xDEC0ADDE;
// *****************************************************************************
Endianness getStorageEndianness(void)
{
    return systemEndianness;
}
// *****************************************************************************
bool setStorageEndianness(Endianness endianness)
{
    if (true == storageIsInitialized())
    {
        return false;
    }

    systemEndianness = endianness;

    return true;
}
// *****************************************************************************
bool storageChangeEndianess(void)
{
    if (isSystemLittleEndian())
    {
        return false;
    }
    return true;
}
// *****************************************************************************
bool storageIsInitialized(void)
{
    return isInitialized;
}
// *****************************************************************************
size_t storageGetSize(void)
{
    return (parameterListSize * sizeof(ParameterData));
}
// *****************************************************************************
bool storageInitialize(size_t initialSize)
{
    if (0 == initialSize)
    {
        return false;
    }

    if (true == isInitialized)
    {
        return false;
    }

    parameterList = (ParameterData *)calloc(initialSize, sizeof(ParameterData));
    if (NULL == parameterList)
    {
        return false;
    }

    parameterListSize = initialSize;
    parameterList[0].val_ui32[0] = PARAMETER_START;
    parameterList[parameterListSize - 1].val_ui32[3] = PARAMETER_END;
    isInitialized = true;

    return true;
}
// *****************************************************************************
bool storageResize(size_t newSize) {
    if (parameterListSize >= newSize)
    {
        return false;
    }

    if (false == isInitialized)
    {
        return false;
    }

    ParameterData *parameterListNew = (ParameterData *)calloc(newSize, sizeof(ParameterData));
    if (NULL == parameterListNew)
    {
        return false;
    }

    for (size_t loop = 0; loop < parameterListSize; loop++)
    {
        for (size_t iloop = 0; iloop < 2; iloop++)
        {
            parameterListNew[loop].val_ui64[iloop] = parameterList[loop].val_ui64[iloop];
        }
    }

    parameterListNew[parameterListSize - 1].val_ui32[3] = 0;
    parameterListSize = newSize;
    parameterListNew[parameterListSize - 1].val_ui32[3] = PARAMETER_END;
    free(parameterList);
    parameterList = parameterListNew;
    parameterListNew = NULL;

    return true;
}
// *****************************************************************************
void storageRelease(void)
{
    if (NULL != parameterList)
    {
        free(parameterList);
        parameterList = NULL;
        parameterListSize = 0;
    }
    isInitialized = false;
}
// *****************************************************************************
bool storageIsValidIndexPartial(size_t index)
{
    bool isValid = (index <= (parameterListSize - 1));
    return isValid;
}
// *****************************************************************************
bool storageIsValidIndexFull(size_t index)
{
    bool isValid = (1 <= index) && (index <= (parameterListSize - 2));
    return isValid;
}
// *****************************************************************************
bool storageIsValidIndex(ParameterType parameter, size_t index)
{
    bool isValid = false;

    // Check allowed unions
    switch (parameter)
    {
    case PT_BYTE1:
    case PT_BYTE2:
    case PT_BYTE4:
    case PT_BYTE8:
        isValid = storageIsValidIndexPartial(index);
        break;
    case PT_BYTE16:
        isValid = storageIsValidIndexFull(index);
        break;
    case PT_LAST:
    default:
        isValid = false;
        break;
    }

    return isValid;
}
// *****************************************************************************
bool storageIsValidPositionPartial(size_t index, size_t position, ParameterType full)
{
    if ((0 == index) && ((size_t)(full / 2) > position))
    {
        return false;
    }

    if (((parameterListSize - 1) == index) && (((size_t)(full / 2) <= position)))
    {
        return false;
    }

    if (!((size_t)full > position))
    {
        return false;
    }

    return true;
}
// *****************************************************************************
bool storageIsValidPositionFull(size_t index, size_t position)
{
    if (0 == index)
    {
        return false;
    }

    if ((parameterListSize - 2) < index)
    {
        return false;
    }

    if (0 != position)
    {
        return false;
    }

    // Passed all guards, is valid
    return true;
}
// *****************************************************************************
bool storageIsValidPosition(ParameterType parameter, size_t index, size_t position)
{
    bool isValid = false;

    // Check position
    switch (parameter)
    {
    case PT_BYTE1:
        isValid = storageIsValidPositionPartial(index, position, PT_BYTE16);
        break;
    case PT_BYTE2:
        isValid = storageIsValidPositionPartial(index, position, PT_BYTE8);
        break;
    case PT_BYTE4:
        isValid = storageIsValidPositionPartial(index, position, PT_BYTE4);
        break;
    case PT_BYTE8:
        isValid = storageIsValidPositionPartial(index, position, PT_BYTE2);
        break;
    case PT_BYTE16:
        isValid = storageIsValidPositionFull(index, position);
        break;
    case PT_LAST:
    default:
        isValid = false;
        break;
    }

    return isValid;
}
// *****************************************************************************
bool storageIsValidAddress(ParameterType parameter, size_t index, size_t position)
{
    // Storage not initialized
    if (false == storageIsInitialized())
    {
        return false;
    }

    if (storageIsValidIndex(parameter, index))
    {
        return storageIsValidPosition(parameter, index, position);
    }

    return false;
}
// *****************************************************************************
bool storageGetElement(size_t index, ParameterData *destination)
{
    // Storage not initialized
    if (false == storageIsInitialized())
    {
        return false;
    }

    // Check partial because of no exclusion reading full ParameterData element
    if (!storageIsValidIndexPartial(index))
    {
        return false;
    }

    *destination = parameterList[index];

    return true;
}
// *****************************************************************************
bool storageSetElement(size_t index, ParameterData source)
{
    // Storage not initialized
    if (false == storageIsInitialized())
    {
        return false;
    }

    // Check partial because of no exclusion reading full ParameterData element
    if (!storageIsValidIndexPartial(index))
    {
        return false;
    }

    parameterList[index] = source;

    return true;
}
// *****************************************************************************
bool storageRead_i64(size_t index, size_t position, int64_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE8, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_i64[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_i64(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_i64(size_t index, size_t position, int64_t value)
{
    if (false == storageIsValidAddress(PT_BYTE8, index, position))
    {
        return false;
    }

    parameterList[index].val_i64[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_i64[position] = swapBytes_i64(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_ui64(size_t index, size_t position, uint64_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE8, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_ui64[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_ui64(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_ui64(size_t index, size_t position, uint64_t value)
{
    if (false == storageIsValidAddress(PT_BYTE8, index, position))
    {
        return false;
    }

    parameterList[index].val_ui64[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_ui64[position] = swapBytes_ui64(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_i32(size_t index, size_t position, int32_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE4, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_i32[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_i32(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_i32(size_t index, size_t position, int32_t value)
{
    if (false == storageIsValidAddress(PT_BYTE4, index, position))
    {
        return false;
    }

    parameterList[index].val_i32[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_i32[position] = swapBytes_i32(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_ui32(size_t index, size_t position, uint32_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE4, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_ui32[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_i32(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_ui32(size_t index, size_t position, uint32_t value)
{
    if (false == storageIsValidAddress(PT_BYTE4, index, position))
    {
        return false;
    }

    parameterList[index].val_ui32[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_ui32[position] = swapBytes_ui32(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_i16(size_t index, size_t position, int16_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE2, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_i16[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_i16(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_i16(size_t index, size_t position, int16_t value)
{
    if (false == storageIsValidAddress(PT_BYTE2, index, position))
    {
        return false;
    }

    parameterList[index].val_i16[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_i16[position] = swapBytes_i16(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_ui16(size_t index, size_t position, uint16_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE2, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_ui16[position];
    if (storageChangeEndianess())
    {
        *value = swapBytes_ui16(*value);
    }

    return true;
}
// *****************************************************************************
bool storageWrite_ui16(size_t index, size_t position, uint16_t value)
{
    if (false == storageIsValidAddress(PT_BYTE2, index, position))
    {
        return false;
    }

    parameterList[index].val_ui16[position] = value;
    if (storageChangeEndianess())
    {
        parameterList[index].val_ui16[position] = swapBytes_ui16(value);
    }

    return true;
}
// *****************************************************************************
bool storageRead_i8(size_t index, size_t position, int8_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE1, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_i8[position];
    return true;
}
// *****************************************************************************
bool storageWrite_i8(size_t index, size_t position, int8_t value)
{
    if (false == storageIsValidAddress(PT_BYTE1, index, position))
    {
        return false;
    }

    parameterList[index].val_i8[position] = value;
    return true;
}
// *****************************************************************************
bool storageRead_ui8(size_t index, size_t position, uint8_t *value)
{
    if (false == storageIsValidAddress(PT_BYTE1, index, position))
    {
        return false;
    }

    *value = parameterList[index].val_ui8[position];
    return true;
}
// *****************************************************************************
bool storageWrite_ui8(size_t index, size_t position, uint8_t value)
{
    if (false == storageIsValidAddress(PT_BYTE1, index, position))
    {
        return false;
    }

    parameterList[index].val_ui8[position] = value;
    return true;
}
// *****************************************************************************
bool storageLoad(char *filename)
{
    if (storageIsInitialized())
    {
        return false;
    }

    FILE *ptr_fp = fopen(filename, "rb");
    if (NULL == ptr_fp)
    {
        return false;
    }

    fseek(ptr_fp, 0, SEEK_END);
    size_t bytes = ftell(ptr_fp);
    size_t dataBytes = bytes / sizeof(ParameterData);
    storageInitialize(dataBytes);

    fseek(ptr_fp, 0, SEEK_SET);
    size_t blocks = fread(parameterList, bytes, 1, ptr_fp);
    fclose(ptr_fp);

    if (1 != blocks)
    {
        return false;
    }

    return true;
}
// *****************************************************************************
bool storageSave(char *filename)
{
    if (!storageIsInitialized())
    {
        return false;
    }

    FILE *ptr_fp = fopen(filename, "wb");
    if (NULL == ptr_fp)
    {
        return false;
    }

    size_t blocks = fwrite(parameterList, storageGetSize(), 1, ptr_fp);
    fclose(ptr_fp);

    if (1 != blocks)
    {
        return false;
    }
    return true;
}
