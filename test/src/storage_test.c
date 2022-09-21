// *****************************************************************************
#include <float.h>
#include <stdbool.h>
#include <limits.h>
// *****************************************************************************
#include "storage_test.h"
#include "storage.h"
#include "testinc.h"
// *****************************************************************************
void t_storageEndianness(void)
{
    Endianness currentEndianness = getStorageEndianness();
    TEST_CHECK(currentEndianness == E_ENDIANNESS_LITTLE);

    bool success = setStorageEndianness(E_ENDIANNESS_BIG);
    currentEndianness = getStorageEndianness();
    TEST_CHECK(true == success);
    TEST_CHECK(currentEndianness == E_ENDIANNESS_BIG);

    success = setStorageEndianness(E_ENDIANNESS_LITTLE);
    currentEndianness = getStorageEndianness();
    TEST_CHECK(true == success);
    TEST_CHECK(currentEndianness == E_ENDIANNESS_LITTLE);

    bool storageInitOkay = storageInitialize(4);
    TEST_CHECK(true == storageInitOkay);

    success = setStorageEndianness(E_ENDIANNESS_BIG);
    currentEndianness = getStorageEndianness();
    TEST_CHECK(false == success);
    TEST_CHECK(currentEndianness == E_ENDIANNESS_LITTLE);

    storageRelease();
}
// *****************************************************************************
void t_storageEndiannessToggle(void)
{
    Endianness currentEndianness = getStorageEndianness();
    TEST_CHECK(currentEndianness == E_ENDIANNESS_LITTLE);

    bool success = setStorageEndianness(E_ENDIANNESS_BIG);
    currentEndianness = getStorageEndianness();
    TEST_CHECK(true == success);
    TEST_CHECK(currentEndianness == E_ENDIANNESS_BIG);
}
// *****************************************************************************
void t_storageGetTotalSize(void)
{
    size_t size = 0;
    size_t initSize = 0;

    // Check startup size
    size = storageGetSize();
    TEST_CHECK(initSize == size);
    TEST_MSG("Expected value [%zu], got [%zu]", initSize, size);

    // Init storage with invalid size
    bool storageInitOkay = storageInitialize(initSize);
    TEST_CHECK(false == storageInitOkay);

    // Init storage with valid size
    initSize = PT_BYTE16;
    storageInitOkay = storageInitialize(initSize);
    if (storageInitOkay)
    {
        size = storageGetSize();
        TEST_CHECK((initSize * PT_BYTE16) == size);
        TEST_MSG("Expected value [%zu], got [%zu]", (initSize * PT_BYTE16), size);

        storageRelease();
    }
}
// *****************************************************************************
void t_storageXetElement(void)
{
    size_t initSize = 3;

    bool storageInitOkay = storageInitialize(initSize);
    TEST_CHECK(true == storageInitOkay);

    if (storageInitOkay)
    {
        ParameterData sut;
        size_t size = storageGetSize();

        TEST_CHECK((initSize * PT_BYTE16) == size);
        TEST_MSG("Expected value [%zu], got [%zu]", (initSize * PT_BYTE16), size);

        bool success = storageGetElement(0, &sut);
        TEST_CHECK(true == success);
        // First part of first element is set with start marker
        TEST_CHECK(0x00000000 == sut.val_ui32[1]);
        TEST_CHECK(PARAMETER_START == sut.val_ui32[0]);
        TEST_MSG("Expected value [%llx], got [%llx]", PARAMETER_START, sut.val_ui32[0]);

        success = storageGetElement(1, &sut);
        TEST_CHECK(true == success);
        // Default value of elements is zero
        TEST_CHECK(0x00000000 == sut.val_ui32[0]);
        TEST_CHECK(0x00000000 == sut.val_ui32[1]);

        // Set values of element
        sut.val_ui32[0] = PARAMETER_END;
        sut.val_ui32[1] = PARAMETER_START;
        // Write element complete
        success = storageSetElement(1, sut);
        TEST_CHECK(true == success);

        // Re-read element
        success = storageGetElement(1, &sut);
        TEST_CHECK(true == success);
        // Expect previous set values
        TEST_CHECK(PARAMETER_END == sut.val_ui32[0]);
        TEST_CHECK(PARAMETER_START == sut.val_ui32[1]);

        success = storageGetElement(2, &sut);
        TEST_CHECK(true == success);
        // Last part of zero element is set with start marker
        TEST_CHECK(0x00000000 == sut.val_ui32[0]);
        TEST_CHECK(PARAMETER_END == sut.val_ui32[3]);
        TEST_MSG("Expected value [%llx], got [%llx]", PARAMETER_END, sut.val_ui32[3]);

        success = storageGetElement(3, &sut);
        TEST_CHECK(false == success);
    }

    storageRelease();
}
// *****************************************************************************
void t_storageSize(void)
{
    size_t storageUsed = storageGetSize();
    TEST_CHECK(0 == storageUsed);

    size_t storageSize = 3;
    bool success = storageInitialize(storageSize);
    TEST_CHECK(true == success);

    storageUsed = storageGetSize();
    TEST_CHECK((storageSize * PT_BYTE16) == storageUsed);

    ParameterData sut;
    success = storageGetElement(0, &sut);
    TEST_CHECK(true == success);
    TEST_CHECK(PARAMETER_START == sut.val_ui32[0]);

    success = storageGetElement(2, &sut);
    TEST_CHECK(true == success);
    TEST_CHECK(PARAMETER_END == sut.val_ui32[3]);

    storageSize = 2 * storageSize;
    success = storageResize(storageSize);
    TEST_CHECK(true == success);

    storageUsed = storageGetSize();
    TEST_CHECK((storageSize * PT_BYTE16) == storageUsed);

    success = storageGetElement(0, &sut);
    TEST_CHECK(true == success);
    TEST_CHECK(PARAMETER_START == sut.val_ui32[0]);

    success = storageGetElement(2, &sut);
    TEST_CHECK(true == success);
    TEST_CHECK(0x00000000 == sut.val_ui32[3]);

    success = storageGetElement(5, &sut);
    TEST_CHECK(true == success);
    TEST_CHECK(PARAMETER_END == sut.val_ui32[3]);

    storageRelease();
}
// *****************************************************************************
