// *****************************************************************************
#include <stdio.h>
// *****************************************************************************
#include "converter.h"
// *****************************************************************************
bool isSystemLittleEndian(void)
{
    static int16_t testVar = -1;
    static bool littleEndian = false;

    if (-1 == testVar)
    {
        testVar = 1;
        char *testEndian = (char *)&testVar;

        if (*testEndian)
        {
            littleEndian = true;
        }
    }

    return littleEndian;
}
// *****************************************************************************
int16_t swapBytes_i16(int16_t value)
{
    int16_t result = ((0x00FF & (value >> 8)) |
                      (0xFF00 & (value << 8)));
    return result;
}
// *****************************************************************************
uint16_t swapBytes_ui16(uint16_t value)
{
    return ((uint16_t)swapBytes_i16((int16_t)(value)));
}
// *****************************************************************************
int32_t swapBytes_i32(int32_t value)
{
    int32_t result = ((0x000000FF & (value >> 24)) |
                      (0x0000FF00 & (value >> 8)) |
                      (0x00FF0000 & (value << 8)) |
                      (0xFF000000 & (value << 24)));

    return result;
}
// *****************************************************************************
uint32_t swapBytes_ui32(uint32_t value)
{
    return ((uint32_t)swapBytes_i32((uint32_t)(value)));
}
// *****************************************************************************
int64_t swapBytes_i64(int64_t value)
{
    int64_t result = ((0x00000000000000FF & (value >> 56)) |
                      (0x000000000000FF00 & (value >> 40)) |
                      (0x0000000000FF0000 & (value >> 24)) |
                      (0x00000000FF000000 & (value >> 8)) |
                      (0x000000FF00000000 & (value << 8)) |
                      (0x0000FF0000000000 & (value << 24)) |
                      (0x00FF000000000000 & (value << 40)) |
                      (0xFF00000000000000 & (value << 56)));
    return result;
}
// *****************************************************************************
uint64_t swapBytes_ui64(uint64_t value)
{
    return ((uint64_t)swapBytes_i64((uint64_t)(value)));
}
// *****************************************************************************
bool changeEndianness(ParameterData *object, ParameterType type, size_t position)
{
    if (!((type == PT_BYTE2) ||
          (type == PT_BYTE4) ||
          (type == PT_BYTE8) ||
          (type == PT_BYTE16)))
    {
        return false;
    }

    for (size_t low = position, high = position + type - 1; low < high; low++, high--)
    {
        uint8_t temp = object->val_ui8[low];
        object->val_ui8[low] = object->val_ui8[high];
        object->val_ui8[high] = temp;
    }

    return true;
}
// *****************************************************************************
