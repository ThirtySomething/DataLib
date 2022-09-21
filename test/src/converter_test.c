// *****************************************************************************
#include "converter_test.h"
#include "testinc.h"
#include "converter.h"
#include "endianness.h"
// *****************************************************************************
void t_converter(void)
{
    ParameterData sut;
    bool success;
    int16_t sut_i16 = 0x00FF;
    int16_t sut_i16_e = 0xFF00;
    int16_t sut_i16_s = swapBytes_i16(sut_i16);

    TEST_CHECK(sut_i16_e == sut_i16_s);
    TEST_MSG("Conversion of 16 bit failed");

    sut.val_i16[0] = sut_i16;
    success = changeEndianness(&sut, PT_BYTE2, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 16 bit failed");
    TEST_CHECK(sut_i16_e == sut.val_i16[0]);

    uint16_t sut_ui16 = 0x00FF;
    uint16_t sut_ui16_e = 0xFF00;
    uint16_t sut_ui16_s = swapBytes_ui16(sut_ui16);

    TEST_CHECK(sut_ui16_e == sut_ui16_s);
    TEST_MSG("Conversion of 16 bit failed");

    sut.val_i16[0] = sut_i16;
    success = changeEndianness(&sut, PT_BYTE2, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 16 bit failed");
    TEST_CHECK(sut_i16_e == sut.val_i16[0]);

    int32_t sut_i32 = 0x00FF00FF;
    int32_t sut_i32_e = 0xFF00FF00;
    int32_t sut_i32_s = swapBytes_i32(sut_i32);

    TEST_CHECK(sut_i32_e == sut_i32_s);
    TEST_MSG("Conversion of 32 bit failed");

    sut.val_i32[0] = sut_i32;
    success = changeEndianness(&sut, PT_BYTE4, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 32 bit failed");
    TEST_CHECK(sut_i32_e == sut.val_i32[0]);

    uint32_t sut_ui32 = 0x00FF00FF;
    uint32_t sut_ui32_e = 0xFF00FF00;
    uint32_t sut_ui32_s = swapBytes_ui32(sut_ui32);

    TEST_CHECK(sut_ui32_e == sut_ui32_s);
    TEST_MSG("Conversion of 32 bit failed");

    sut.val_ui32[0] = sut_ui32;
    success = changeEndianness(&sut, PT_BYTE4, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 32 bit failed");
    TEST_CHECK(sut_ui32_e == sut.val_ui32[0]);

    int64_t sut_i64 = 0x00FF00FF00FF00FF;
    int64_t sut_i64_e = 0xFF00FF00FF00FF00;
    int64_t sut_i64_s = swapBytes_i64(sut_i64);

    TEST_CHECK(sut_i64_e == sut_i64_s);
    TEST_MSG("Conversion of 64 bit failed");

    sut.val_i64[0] = sut_i64;
    success = changeEndianness(&sut, PT_BYTE8, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 64 bit failed");
    TEST_CHECK(sut_i64_e == sut.val_i64[0]);

    uint64_t sut_ui64 = 0x00FF00FF00FF00FF;
    uint64_t sut_ui64_e = 0xFF00FF00FF00FF00;
    uint64_t sut_ui64_s = swapBytes_ui64(sut_ui64);

    TEST_CHECK(sut_ui64_e == sut_ui64_s);
    TEST_MSG("Conversion of 64 bit failed");

    sut.val_ui64[0] = sut_ui64;
    success = changeEndianness(&sut, PT_BYTE8, 0);
    TEST_CHECK(true == success);
    TEST_MSG("Conversion of 64 bit failed");
    TEST_CHECK(sut_ui64_e == sut.val_ui64[0]);
}
