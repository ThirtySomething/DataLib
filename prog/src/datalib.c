// *****************************************************************************
#include <stdio.h>
// *****************************************************************************
#include "datalib.h"
#include "storage.h"
// *****************************************************************************
bool isValidParamID(const size_t paramID)
{
    bool isValid = false;
    for (size_t loop = 0; loop < sizeParameterList; loop++)
    {
        if (paramID == parameterDefinition[loop].paramID)
        {
            isValid = true;
            break;
        }
    }

    return isValid;
}
// *****************************************************************************
bool getParameter(const size_t paramID, void *value)
{
    if (!isValidParamID(paramID))
    {
        return false;
    }

    bool result = false;
    switch (parameterDefinition[paramID].paramType)
    {
    case PT_BYTE1:
        result = storageRead_i8(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            ((int8_t *)value));
        break;
    case PT_BYTE2:
        result = storageRead_i16(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            ((int16_t *)value));
        break;
    case PT_BYTE4:
        result = storageRead_i32(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            ((int32_t *)value));
        break;
    case PT_BYTE8:
        result = storageRead_i64(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            ((int64_t *)value));
        break;
    case PT_BYTE16:
    case PT_LAST:
    default:
        break;
    }

    return result;
}
// *****************************************************************************
bool setParameter(const size_t paramID, const void *value)
{
    if (!isValidParamID(paramID))
    {
        return false;
    }

    bool result = false;
    switch (parameterDefinition[paramID].paramType)
    {
    case PT_BYTE1:
        result = storageWrite_i8(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            *((int8_t *)value));
        break;
    case PT_BYTE2:
        result = storageWrite_i16(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            *((int16_t *)value));
        break;
    case PT_BYTE4:
        result = storageWrite_i32(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            *((int32_t *)value));
        break;
    case PT_BYTE8:
        result = storageWrite_i64(
            parameterDefinition[paramID].paramIndex,
            parameterDefinition[paramID].paramPosition,
            *((int64_t *)value));
        break;
    case PT_BYTE16:
    case PT_LAST:
    default:
        break;
    }

    return result;
}
// *****************************************************************************
