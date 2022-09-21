// *****************************************************************************
#include <float.h>
// *****************************************************************************
#include "datalib_test.h"
#include "datalib.h"
#include "storage.h"
#include "testinc.h"
// *****************************************************************************
void test_read(size_t index, void *valnew)
{
    bool success = getParameter(index, valnew);
    TEST_CHECK(true == success);
    TEST_MSG("Get of parameter [%d] failed", index);
}
// *****************************************************************************
void test_write(size_t index, void *val)
{
    bool success = setParameter(index, val);
    TEST_CHECK(true == success);
    TEST_MSG("Set of parameter [%d] failed", index);
}
// *****************************************************************************
void test_read_write(size_t index, void *val, void *valnew)
{
    test_write(index, val);
    test_read(index, valnew);
}
// *****************************************************************************
void t_datalib_api(void)
{
    Endianness eArr[] = {E_ENDIANNESS_BIG, E_ENDIANNESS_LITTLE};

    for (size_t endianness = 0; endianness < 2; endianness++)
    {
        // Init storage with valid size
        size_t initSize = sizeParameterList;
        bool success = setStorageEndianness(eArr[endianness]);
        TEST_CHECK(true == success);
        TEST_MSG("Cannot set endianness");

        Endianness endi = getStorageEndianness();
        TEST_CHECK(eArr[endianness] == endi);
        TEST_MSG("Invalid endianness");

        success = storageInitialize(initSize);
        TEST_CHECK(true == success);
        TEST_MSG("Initialization failed");

        size_t size = storageGetSize();
        TEST_CHECK((initSize * PT_BYTE16) == size);
        TEST_MSG("Expected value [%zu], got [%zu]", (initSize * PT_BYTE16), size);

        if (success)
        {
            int64_t val_i64_in = INT64_MAX;
            int64_t val_i64_out;
            test_read_write(0, (void *)&val_i64_in, (void *)&val_i64_out);
            TEST_CHECK(val_i64_in == val_i64_out);

            uint64_t val_ui64_in = UINT64_MAX;
            uint64_t val_ui64_out;
            test_read_write(1, (void *)&val_ui64_in, (void *)&val_ui64_out);
            TEST_CHECK(UINT64_MAX == val_ui64_out);

            int32_t val_i32_in = INT32_MAX;
            int32_t val_i32_out;
            test_read_write(2, (void *)&val_i32_in, (void *)&val_i32_out);
            TEST_CHECK(INT32_MAX == val_i32_out);

            uint32_t val_ui32_in = UINT32_MAX;
            uint32_t val_ui32_out;
            test_read_write(3, (void *)&val_ui32_in, (void *)&val_ui32_out);
            TEST_CHECK(UINT32_MAX == val_ui32_out);

            int16_t val_i16_in = INT16_MAX;
            int16_t val_i16_out;
            test_read_write(4, (void *)&val_i16_in, (void *)&val_i16_out);
            TEST_CHECK(INT16_MAX == val_i16_out);

            uint16_t val_ui16_in = UINT16_MAX;
            uint16_t val_ui16_out;
            test_read_write(5, (void *)&val_ui16_in, (void *)&val_ui16_out);
            TEST_CHECK(UINT16_MAX == val_ui16_out);

            int8_t val_i8_in = INT8_MAX;
            int8_t val_i8_out;
            test_read_write(6, (void *)&val_i8_in, (void *)&val_i8_out);
            TEST_CHECK(INT8_MAX == val_i8_out);

            uint8_t val_ui8_in = UINT8_MAX;
            uint8_t val_ui8_out;
            test_read_write(7, (void *)&val_ui8_in, (void *)&val_ui8_out);
            TEST_CHECK(UINT8_MAX == val_ui8_out);

            char fname[10] = "data_";
            fname[strlen(fname)] = (char)(48 + (int)endi);

            success = storageSave(fname);
            TEST_CHECK(true == success);

            storageRelease();

            success = setStorageEndianness(endi);
            TEST_CHECK(true == success);
            TEST_MSG("Cannot set endianness");

            success = storageLoad(fname);
            TEST_CHECK(true == success);

            test_read(0, (void *)&val_i64_out);
            TEST_CHECK(val_i64_in == val_i64_out);

            test_read(1, (void *)&val_ui64_out);
            TEST_CHECK(UINT64_MAX == val_ui64_out);

            test_read(2, (void *)&val_i32_out);
            TEST_CHECK(INT32_MAX == val_i32_out);

            test_read(3, (void *)&val_ui32_out);
            TEST_CHECK(UINT32_MAX == val_ui32_out);

            test_read(4, (void *)&val_i16_out);
            TEST_CHECK(INT16_MAX == val_i16_out);

            test_read(5, (void *)&val_ui16_out);
            TEST_CHECK(UINT16_MAX == val_ui16_out);

            test_read(6, (void *)&val_i8_out);
            TEST_CHECK(INT8_MAX == val_i8_out);

            test_read(7, (void *)&val_ui8_out);
            TEST_CHECK(UINT8_MAX == val_ui8_out);

            int result = remove(fname);
            TEST_CHECK(0 == result);
        }

        storageRelease();
    }
}
