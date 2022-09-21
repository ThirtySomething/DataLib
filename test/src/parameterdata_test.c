// *****************************************************************************
#include <float.h>
#include <stdint.h>
#include <limits.h>
// *****************************************************************************
#include "parameterdata.h"
#include "testinc.h"
// *****************************************************************************
#define DIVIDER 25
#define OFFSET_D (DBL_MAX / DIVIDER)
#define OFFSET_F (FLT_MAX / DIVIDER)
#define OFFSET_LD (LDBL_MAX / DIVIDER)
#define OFFSET_I8 (INT8_MAX / DIVIDER)
#define OFFSET_UI8 (UINT8_MAX / DIVIDER)
#define OFFSET_I16 (INT16_MAX / DIVIDER)
#define OFFSET_UI16 (UINT16_MAX / DIVIDER)
#define OFFSET_I32 (INT32_MAX / DIVIDER)
#define OFFSET_UI32 (UINT32_MAX / DIVIDER)
#define OFFSET_I64 (INT64_MAX / DIVIDER)
#define OFFSET_UI64 (UINT64_MAX / DIVIDER)
// *****************************************************************************
void t_parameterdata_i8(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE16; index++)
    {
        for (int8_t value = INT8_MIN; value < (INT8_MAX - OFFSET_I8); value += OFFSET_I8)
        {
            sut.val_i8[index] = value;
            TEST_CHECK(value == sut.val_i8[index]);
            TEST_MSG("Value is [%hd]", sut.val_i8[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_ui8(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE16; index++)
    {
        for (uint8_t value = 0; value < (UINT8_MAX - OFFSET_UI8); value += OFFSET_UI8)
        {
            sut.val_ui8[index] = value;
            TEST_CHECK(value == sut.val_ui8[index]);
            TEST_MSG("Value is [%hu]", sut.val_ui8[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_i16(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE2; index++)
    {
        for (int16_t value = INT16_MIN; value < (INT16_MAX - OFFSET_I16); value += OFFSET_I16)
        {
            sut.val_i16[index] = value;
            TEST_CHECK(value == sut.val_i16[index]);
            TEST_MSG("Value is [%d]", sut.val_i16[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_ui16(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE8; index++)
    {
        for (uint16_t value = 0; value < (UINT16_MAX - OFFSET_UI16); value += OFFSET_UI16)
        {
            sut.val_ui16[index] = value;
            TEST_CHECK(value == sut.val_ui16[index]);
            TEST_MSG("Value is [%u]", sut.val_ui16[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_i32(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE4; index++)
    {
        for (int32_t value = INT32_MIN; value < (INT32_MAX - OFFSET_I32); value += OFFSET_I32)
        {
            sut.val_i32[index] = value;
            TEST_CHECK(value == sut.val_i32[index]);
            TEST_MSG("Value is [%d]", sut.val_i32[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_ui32(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE4; index++)
    {
        for (uint32_t value = 0; value < (UINT32_MAX - OFFSET_UI32); value += OFFSET_UI32)
        {
            sut.val_ui32[index] = value;
            TEST_CHECK(value == sut.val_ui32[index]);
            TEST_MSG("Value is [%u]", sut.val_ui32[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_i64(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE2; index++)
    {
        for (int64_t value = INT64_MIN; value < (INT64_MAX - OFFSET_I64); value += OFFSET_I64)
        {
            sut.val_i64[index] = value;
            TEST_CHECK(value == sut.val_i64[index]);
            TEST_MSG("Value is [%lld]", sut.val_i64[index]);
        }
    }
}
// *****************************************************************************
void t_parameterdata_ui64(void)
{
    ParameterData sut;

    for (unsigned char index = 0; index < PT_BYTE2; index++)
    {
        for (uint64_t value = 0; value < (UINT64_MAX - OFFSET_UI64); value += OFFSET_UI64)
        {
            sut.val_ui64[index] = value;
            TEST_CHECK(value == sut.val_ui64[index]);
            TEST_MSG("Value is [%llu]", sut.val_ui64[index]);
        }
    }
}
// *****************************************************************************
