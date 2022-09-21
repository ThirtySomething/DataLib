// *****************************************************************************
#include <limits.h>
// *****************************************************************************
#include "storage_ui8_test.h"
#include "parametertype.h"
#include "storage.h"
#include "testinc.h"
// *****************************************************************************
void handleBlock_ui8_range(size_t index, bool flag, size_t start, size_t end, size_t offset)
{
    bool success = false;
    uint8_t valueWrite = UINT8_MAX;
    uint8_t valueRead = 0;

    for (size_t loop = start; loop < end; loop++)
    {
        success = storageWrite_ui8(index, loop + offset, valueWrite);
        TEST_CHECK(flag == success);
        TEST_MSG("storageWrite_ui8(%x, %x) failed", index, loop + offset);

        success = storageRead_ui8(index, loop + offset, &valueRead);
        TEST_CHECK(flag == success);
        TEST_MSG("storageRead_ui8(%x, %x) failed", index, loop + offset);
        if (flag)
        {
            TEST_CHECK(valueWrite == valueRead);
            TEST_MSG("Invalid value read(%x, %x)", index, loop + offset);
        }
    }
}
// *****************************************************************************
void handleBlock_ui8(size_t index, bool left, bool right, size_t offset, size_t limit)
{
    handleBlock_ui8_range(index, left, 0, (limit / 2), offset);
    handleBlock_ui8_range(index, right, (limit / 2), limit, offset);
}
// *****************************************************************************
void t_storage_ui8(void)
{
    Endianness eArr[] = {E_ENDIANNESS_BIG, E_ENDIANNESS_LITTLE};
    // printf("size of uint8_t is [%zu] bytes\t\t", sizeof(uint8_t));

    for (size_t endianness = 0; endianness < 2; endianness++)
    {
        // Init storage with valid size
        size_t initSize = 3;
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
            // Start block, first half blocked
            handleBlock_ui8(0, false, true, 0, PT_BYTE16);
            // Normal block, both halfs allowed
            handleBlock_ui8(1, true, true, 0, PT_BYTE16);
            // Last block, first half allowed
            handleBlock_ui8(2, true, false, 0, PT_BYTE16);
            // Invalid block, no half allowed
            handleBlock_ui8(3, false, false, 0, PT_BYTE16);
            // Valid block, invalid position, no half allowed
            handleBlock_ui8(1, false, false, PT_BYTE16, PT_BYTE16);
        }

        storageRelease();
    }
}
